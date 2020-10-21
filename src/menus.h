#pragma once

#include "selecionar_opcoes_posicao.h"
#include "defines_lolo.h"

#ifdef DEBUG
#include "debug.h"
#endif

/* Códigos de retorno do menu principal */
#define NOVOJOGO                  0
#define CARREGARJOGO              1
#define RECORDES                  2
#define COMOJOGAR                 3
#define CREDITOS                  4
#define MENU_PRINCIPAL_SAIR       5

/* Informações sobre a tela */
#define MEIO_X 40

/* Tamanho do menu principal */
#define MEIO_GRIDX_MENU_PRINCIPAL INICIO_GRIDX_MENU_PRINCIPAL + ((TAMANHO_GRIDX_MENU_PRINCIPAL) / 2)
#define INICIO_GRIDY_MENU_PRINCIPAL 10
#define FINAL_GRIDY_MENU_PRINCIPAL 23
#define TAMANHO_GRIDY_MENU_PRINCIPAL FINAL_GRIDY_MENU_PRINCIPAL - INICIO_GRIDY_MENU_PRINCIPAL

/* Exibe o menu principal */
int menu_principal(void);
/* Exibe os Créditos */
int creditos(void);
/* Exibe os recordes */
int recordes(void);
/* Calcula a distância entre um item e outro */
int distancia_itens(int num_opcoes, int final_y, int inicial_y);
