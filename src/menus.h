#pragma once

#include "selecionar_opcoes_posicao.h"
#include "defines_lolo.h"

#ifdef DEBUG
#include "debug.h"
#endif

/* Códigos de retorno do menu principal */
#define MENU_PRINCIPAL_JOGAR 0
#define MENU_PRINCIPAL_SAIR  5
#define NUM_OPCOES_MENU_PRINCIPAL 6

/* Tamanho do menu principal */
#define INICIO_GRIDX_MENU_PRINCIPAL  2
#define FINAL_GRIDX_MENU_PRINCIPAL   78
#define TAMANHO_GRIDX_MENU_PRINCIPAL FINAL_GRIDX_MENU_PRINCIPAL - INICIO_GRIDX_MENU_PRINCIPAL
#define MEIO_GRIDX_MENU_PRINCIPAL INICIO_GRIDX_MENU_PRINCIPAL + ((TAMANHO_GRIDX_MENU_PRINCIPAL) / 2)
#define INICIO_GRIDY_MENU_PRINCIPAL 9
#define FINAL_GRIDY_MENU_PRINCIPAL 23
#define TAMANHO_GRIDY_MENU_PRINCIPAL FINAL_GRIDY_MENU_PRINCIPAL - INICIO_GRIDY_MENU_PRINCIPAL

/* Strings do menu principal */
#define MENU_PRINCIPAL_OPCOES "Novo Jogo", "Carregar Jogo", "Recordes", "Como Jogar", "Creditos", "Sair do Jogo"

/* Exibe o menu principal */
int menu_principal(void);

/* Calcula a distância entre um item e outro */
int distancia_itens(int num_opcoes, int final_y, int inicial_y);
