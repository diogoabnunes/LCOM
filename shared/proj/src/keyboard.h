#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "i8042.h"

///@brief Esta função subscreve as interrupções do teclado.
///@param bit_no Número a ser subscrito.
///@return Retorna 0 se sucesso, ou 1 se insucesso.
int keyboard_subscribe_int(uint8_t *bit_no);

///@brief Esta função cancela as interrupções do teclado.
///@return Retorna 0 se sucesso, ou 1 se insucesso.
int keyboard_unsubscribe_int();

///@brief Esta função chama sys_inb e incrementa um contador de chamadas de sys_inb.
///@param port Port a ser lido.
///@param byte Byte retornado.
///@return Retorna 0 se sucesso, ou 1 se insucesso.
int sys_inb_count(port_t port, uint32_t *byte);

///@brief Esta função chama sys_inb_count e faz o cast necessário.
///@param port Port a ser lido.
///@param byte Byte retornado.
///@return Retorna 0 se sucesso, ou 1 se insucesso.
int util_sys_inb_keyboard(port_t port, uint8_t *byte);

///@brief Esta função é o interrupt handler do teclado.
void (kbc_ih)();

#endif 
