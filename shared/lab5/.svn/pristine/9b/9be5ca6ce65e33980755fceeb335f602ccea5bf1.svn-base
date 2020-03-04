#ifndef _LCOM_VIDEO_H_
#define _LCOM_VIDEO_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <machine/int86.h> // /usr/src/include/arch/i386
#include "vbe.h"


typedef struct {
    char VBESignature[4];   
    BCD VBEVersion[2];          
    uint32_t OEMStringPtr;               
    uint8_t Capabilities[4];                
    uint32_t VideoModeList;      
    uint16_t TotalMemory;            

    uint16_t OemSoftwareRev;                 
    uint32_t OemVendorNamePtr;
    uint32_t OemProductNamePtr;
    uint32_t OemProductRevPtr;  
    uint8_t Reserved[222];            
    uint8_t OemData[256];

}vbe_info_t;


uint32_t get_lsb(uint32_t value, uint32_t num_bits);

int set_graphics_mode(uint16_t mode);
int get_vram_info(uint16_t mode);
int mapping_VRAM();
void* (vg_init)(uint16_t mode);

uint8_t return_color_comp(unsigned field_position, unsigned mask_size, uint32_t color);
int color_pixel(uint16_t x, uint16_t y, uint32_t color);
uint32_t change_color(uint16_t row, uint16_t col, uint8_t no_rectangles, uint32_t first, uint8_t step);

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
int draw_pattern(uint32_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step);

int draw_pix_map(xpm_image_t img, uint16_t x, uint16_t y);
int clear_pix_map(xpm_image_t img, uint16_t x, uint16_t y);

//int vbe_get_contr_info(vg_vbe_contr_info_t *contr_info, vbe_info_t* info);

#endif /* _LCOM_VIDEO_H */
