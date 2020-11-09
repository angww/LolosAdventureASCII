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
#define CREDITOS                  3
#define MENU_PRINCIPAL_SAIR       4

/* Códigos de retorno dos sub-menus de pausa e game-over */
#define OPCAO_CONTINUAR_JOGANDO 0
#define OPCAO_SALVAR            1
#define OPCAO_SAIR              2
#define OPCAO_NOVO_JOGO         11

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


/* Exibe o menu enquanto o jogo está parado. */
int exibe_menu_pause(void);

/* Processa os retornos (Voltar, Salvar ou Sair) do menu de pause do jogo. */
int processa_menu_pause(void);

/* Exibe o menu quando acaba o jogo por falta de vidas. */
int exibe_game_over(void);

/* Processa os retornos (Novo, Carregar ou Sair) do menu game over. */
int processa_menu_game_over(void);