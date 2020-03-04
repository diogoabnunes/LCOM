#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

#include "i8042.h"
#include "ps2.h"

typedef enum state_t //Enumeration with all states of state machine
{
  INITIAL_STATE,        //Initial state
  LEFT_LINE,       //Left line of inverted V
  VERTEX,      //Vertex of inverted V
  RIGHT_LINE,       //Right line of inverted V
  FINAL_STATE        //Final state
} state_t;

typedef struct state_machine_t //Struct that works as a state machine
{
  state_t currentState; //Current state of the state machine
  int x_displacement; //Current displacement in the x direction
  int y_displacement; //Current displacement in the y direction
} state_machine_t;

///@brief Esta função subscreve as interrupções do rato.
///@param bit_no Número a ser subscrito.
///@return Retorna 0 se sucesso, ou 1 se insucesso.
int mouse_subscribe_int(uint8_t *bit_no);

///@brief Esta função cancela as interrupções do rato.
///@return Retorna 0 se sucesso, ou 1 se insucesso.
int mouse_unsubscribe_int();

///@brief Manipula as interrupções do rato.
void (mouse_ih)();

///@brief Tal como o nome indica, escreve um argumento command numa entrada port.
///@param port Porta a receber um comando.
///@param command Comando a ser mandado para a entrada.
///@return Retorna 0 se sucesso, ou 1 se insucesso.
int write_keyboard(uint32_t port, uint32_t command);

///@brief Tal como o nome indica, lê o conteúdo do buffer para um argumento data.
///@param data Variável que vai receber o conteúdo da leitura.
///@return Retorna 0 se sucesso, ou 1 se insucesso.
int read_keyboard(uint32_t *data);

///@brief Tal como o nome indica, escreve um argumento command no command byte.
///@param command Comando a ser mandado para o command byte.
///@return Retorna 0 se sucesso, ou 1 se insucesso.
int write_command_byte(uint32_t command);

///@brief Tal como o nome indica, escreve um argumento command na entrada do rato.
///@param command Comando a ser mandado para a entrada do rato.
///@return Retorna 0 se sucesso, ou 1 se insucesso.
int write_mouse(uint32_t command);

///brief Decompõe o conteúdo dos pacotes recebidos do rato nas variáveis da estrutura do rato.
void packet_create();

///@brief Tal como o nome indica, deteta o evento do rato.
///@param pp Estrutura do pacote do rato.
///@param st_machine Máquina de estados do rato.
//@param m_ev Eventos do rato.
void detect_mouse_event(struct packet *pp, state_machine_t *st_machine, struct mouse_ev *m_ev);

///@brief Reconhece o evento do rato e atualiza a máquina de estados do rato.
///@param st_machine Máquina de estados do rato.
///@param event Eventos do rato.
///@param x_len Valor mínimo do deslocamento de cada linha ao longo da direção x.
///@param tolerance Tolerância dada para reconhecer ratos menos precisos.
void handle_mouse_event(state_machine_t *st_machine, struct mouse_ev event, uint8_t x_len, uint8_t tolerance);

///@brief Esta função deteta o evento do rato e atualiza a máquina de estados do rato.
///@param x_len Valor mínimo do deslocamento de cada linha ao longo da direção x.
///@param tolerance Tolerância dada para reconhecer ratos menos precisos.
///@param st_machine Máquina de estados do rato.
///@param event Eventos do rato.
///@return Retorna 0 se sucesso, ou 1 se insucesso.
int check_gesture(uint8_t x_len, uint8_t tolerance, state_machine_t *st_machine, struct mouse_ev event);

#endif
