#include "video.h"

static void *video_mem;		/* Process (virtual) address to which VRAM is mapped */

static unsigned h_res;	        /* Horizontal resolution in pixels */
static unsigned v_res;	        /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */
static unsigned color_mode;     /* Value of the color mode */
static unsigned bytes_per_pixel; /* Number of bytes a pixel ocuppies, in a certain video mode */

int r;
struct minix_mem_range mr;
static unsigned int vram_base;  /* VRAM's physical addresss */
static unsigned int vram_size;  /* VRAM's size, but you can use the frame-buffer size, instead */

static unsigned RedMaskSize;
static unsigned RedFieldPosition;
static unsigned GreenMaskSize;
static unsigned GreenFieldPosition;
static unsigned BlueMaskSize;
static unsigned BlueFieldPosition;

/*
void double_buffering()
{
  memcpy(video_mem, copy, h_res*v_res*bits_per_pixel/8);
}
*/

uint32_t get_lsb(uint32_t value, uint32_t num_bits)
{

  value <<= (32 - num_bits);
  value >>= (32 - num_bits);

  return value;
}

int get_vram_info(uint16_t mode)
{
	vbe_mode_info_t vmi_p;

	if(vbe_get_mode_info(mode, &vmi_p) != 0)
    	return 1;

  h_res = vmi_p.XResolution; //updates hor resolution
  v_res = vmi_p.YResolution;  //updates vert resolution
  bits_per_pixel = vmi_p.BitsPerPixel; //updates the bits per pixel
  vram_base = vmi_p.PhysBasePtr;  //updates the vram physical address
  color_mode = vmi_p.MemoryModel; //updates the color mode
  
  RedMaskSize = vmi_p.RedMaskSize;
  RedFieldPosition = vmi_p.RedFieldPosition;
  GreenMaskSize = vmi_p.GreenMaskSize;
  GreenFieldPosition = vmi_p.GreenFieldPosition;
  BlueMaskSize = vmi_p.BlueMaskSize;
  BlueFieldPosition = vmi_p.BlueFieldPosition;

  bytes_per_pixel = bits_per_pixel;

  if((bytes_per_pixel % 2) != 0)
   	bytes_per_pixel++;

  bytes_per_pixel /= 8;

  vram_size = h_res * v_res * bytes_per_pixel;

  return 0;
}

int mapping_VRAM()
{
  /* Allow memory mapping */

  mr.mr_base = (phys_bytes) vram_base;	
  mr.mr_limit = mr.mr_base + vram_size;  

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    return 1;

  /* Map memory */

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if(video_mem == MAP_FAILED)
    return 1;

  return 0;
}

int set_graphics_mode(uint16_t mode)
{
	reg86_t reg86;

	memset(&reg86, 0, sizeof(reg86));

	reg86.intno = VIDEOCARD_SERVICE;
	reg86.ax = SET_VBE_MODE;
	reg86.bx = SET_LINEAR_MODE | mode;

	if(sys_int86(&reg86) != OK) {
		printf("vg_exit(): sys_int86() failed \n");
		return 1;
	}

	if(reg86.ah != 0)
		return 1;

	return 0;
}

void* (vg_init)(uint16_t mode)
{
	if (get_vram_info(mode) != 0)
		return NULL;

	if (mapping_VRAM() != 0)
		return NULL;

	if (set_graphics_mode(mode) != 0)
		return NULL;

	return video_mem;
}

int color_pixel(uint16_t x, uint16_t y, uint8_t *color)
{

    uint8_t* ptr = video_mem;
    ptr += (h_res * y * bytes_per_pixel);
    ptr += (x * bytes_per_pixel);

    for(unsigned int j = 0; j < bytes_per_pixel; j++, ptr++)
      *ptr = color[j];

    return 0;
}

uint8_t return_color_comp(unsigned field_position, unsigned mask_size, uint32_t color)
{

  uint32_t newComp = color >> field_position;
  uint8_t return_color = get_lsb(newComp, mask_size);

  return return_color;
}

/*
uint32_t change_color(uint16_t row, uint16_t col, uint8_t no_rectangles, uint32_t first, uint8_t step)
{
	if (color_mode == INDEXED_COLOR)
	{
		uint32_t color = (first + (row * no_rectangles + col) * step) % (1 << bits_per_pixel);
		return color;
	}

	else if (color_mode == DIRECT_COLOR)
	{
		int8_t redComp = return_color_comp(RedFieldPosition, RedMaskSize, first);
    	uint8_t greenComp = return_color_comp(GreenFieldPosition, GreenMaskSize, first);
    	uint8_t blueComp = return_color_comp(BlueFieldPosition, BlueMaskSize, first);

    	uint8_t redPart = (redComp + col * step) % (1 << RedMaskSize);
    	uint8_t greenPart = (greenComp + row * step) % (1 << GreenMaskSize);
    	uint8_t bluePart = (blueComp + (col + row) * step) % (1 << BlueMaskSize);

    	uint32_t color = (redPart << RedFieldPosition) | (greenPart << GreenFieldPosition) | (bluePart << BlueFieldPosition);

    	return color;
	}
	else return 1;
}


int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color)
{
	for(unsigned i = 0; i < len; i++)
	{
      if ((x + i) >= h_res) break;
      color_pixel(x + i, y, color);
  	}
    return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color)
{
	color = get_lsb(color, bits_per_pixel);

  	for (unsigned i = 0; i < height; i++)
  	{
   	  if((y + i) >= v_res) break;
	    vg_draw_hline(x, y + i, width, color);
    }
  	return 0;
}

int draw_pattern(uint32_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step)
{
	uint16_t rec_width = h_res / no_rectangles;
  	uint16_t rec_height = v_res / no_rectangles;
  	uint32_t current_color = first;

  	for (unsigned int line = 0; line < no_rectangles; line++)
  	{
    	for (unsigned int rec = 0; rec < no_rectangles; rec++)
    	{
      		current_color = change_color(line, rec, no_rectangles, first, step);
			  vg_draw_rectangle(rec_width*rec, rec_height*line, rec_width, rec_height, current_color);
    	}
  	}
  	return 0;
}
*/

int draw_pix_map(xpm_image_t img, uint16_t x, uint16_t y)
{
	for (int i = 0; i < img.height; i++)
	{
		if ((unsigned) (y+i) >= v_res) break;

		for (int j = 0; j < img.width; j++)
		{
			if ((unsigned) (x+j) >= h_res) break;

			color_pixel(x+j, y+i, img.bytes + (j+i*img.width)*bytes_per_pixel);
		}
	}
	return 0;
}

int clear_pix_map(xpm_image_t img, uint16_t x, uint16_t y)
{
  for (int i = 0; i < img.height; i++)
  {
    if ((unsigned) (y+i) >= v_res) break;

    for (int j = 0; j < img.width; j++)
    {
      if ((unsigned) (x+j) >= h_res) break;

      color_pixel(x+j, y+i, 0);
    }
  }
  return 0;
}
