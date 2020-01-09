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

//void double_buffering();
///@brief Esta função retorna o bit menos significativo de um número de 32 bits.
///@param value O número cujo LSB será retornado.
///@param num_bits Número de bits de value.
///@return LSB de value.
uint32_t get_lsb(uint32_t value, uint32_t num_bits);
///@brief Essa função atualiza as informações da VRAM de acordo com o modo.
///@param mode Modo de visualização.
///@return 0 se houver sucesso, 1 se insucesso.
int get_vram_info(uint16_t mode);
///@brief Esta função mapeia a memória VRAM ao video_mem.
///@return 0 se houver sucesso, 1 se insucesso.
int mapping_VRAM();
///@brief Esta função muda o console do MINIX do modo de texto para o modo gráfico.
///@param mode Modo de visualização.
///@return 0 se houver sucesso, 1 se insucesso.
int set_graphics_mode(uint16_t mode);
///@brief Esta função inicializa o modo gráfico no MINIX.
///@param mode Modo de visualização.
///@return Ponteiro com video_mem ou NULL em caso de insucesso.
void* (vg_init)(uint16_t mode);
///@brief Esta função colore um pixel.
///@param x Coordenada x do pixel.
///@param y Coordenada y do pixel.
///@param color Cor a colorir.
///@return 0
int color_pixel(uint16_t x, uint16_t y, uint8_t *color);
///@brief Esta função retorna uma composição de cores.
///@param field_position Indica o número de shifts.
///@param mask_size Tamanho da máscara da cor.
///@param color Cor.
///@return Nova cor.
uint8_t return_color_comp(unsigned field_position, unsigned mask_size, uint32_t color);
/*
uint32_t change_color(uint16_t row, uint16_t col, uint8_t no_rectangles, uint32_t first, uint8_t step);
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
int draw_pattern(uint32_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step);
*/

///@brief Esta função desenha uma imagem xpm no ecrã.
///@param img Imagem a ser desenhada.
///@param x Coordenada x onde a imagem será desenhada.
///@param y Coordenada y onde a imagem será desenhada.
///@return 0 se houver sucesso, 1 se insucesso.
int draw_pix_map(xpm_image_t img, uint16_t x, uint16_t y);
///@brief Esta função apaga uma imagem xpm do ecrã.
///@param img Imagem a ser apagada.
///@param x Coordenada x onde a imagem será apagada.
///@param y Coordenada y onde a imagem será apagada.
///@return 0 se houver sucesso, 1 se insucesso.
int clear_pix_map(xpm_image_t img, uint16_t x, uint16_t y);

#endif
