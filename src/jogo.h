#pragma once

#include "defines_lolo.h"
#include "arquivos.h"
#include "cores.h"
#include "menus.h"
#include "dados.h"
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "selecionar_opcoes_posicao.h"

/* Definições do sub-menu de pausa */
#define OPCAO_CONTINUAR_JOGANDO 0
#define OPCAO_SALVAR            1
#define OPCAO_SAIR              2

/* Tecla 254 escolhida arbitrariamente para GAME_OVER */
#define GAME_OVER      254

/* Executa os mapa apartir do definido em gravacao */
int joga_mapas(gravacao_st *gravacao);
/*
 * Loop principal, retorna:
 * 0 -> Ganhou o nível
 * 1 -> Perdeu o nível
 * TODO: retorno para salvar e/ou voltar menu
 */
int loop_jogo(mapa_st *mapa, gravacao_st *gravacao);
/* Primeira exibição completa do mapa */
void exibe_grid(char grid[JOGO_JANELA_Y][JOGO_JANELA_X]);
/* Movimenta o inimigo na tela, retorna 0 se não se moveu */
int movimenta_inimigo(inimigo_st *inimigo, mapa_st *mapa);
/* Abre um novo jogo */
int novojogo(void);
/* Carrega um save e continuar a jogar nele */
int carregarjogo(void);
/* Retorna ponto_st com a posição alterada conforme key */
ponto_st muda_pos(ponto_st pos, int key);
/*
 * Movimenta Lolo pelo tela e retorna um código específico:
 * 0 -> Movimentação normal
 * 1 -> Não se moveu
 * 2 -> Lolo perdeu uma vida para um inimigo
 * 3 -> Lolo perdeu uma vida para água
 * 4 -> Lolo pegou um coração
 * 5 -> Lolo está em um baú
 */
int movimenta_lolo(lolo_st *lolo, int key);
/* Retorna mov em um posição adjacente válida */
int prox_mov(char adjacentes[4], int mov);

/* Exibe o menu enquanto o jogo está parado. */
int exibe_menu_pause(void);

/* Processa os retornos (Voltar, Salvar e Sair) do menu de pause do jogo. */
int processa_menu_pause(void);

/* Atuliza o mapa no determinado ponto 'pos' colocando o item_grid */
int atualiza_grid_mapa(mapa_st *mapa, ponto_st pos, int item_grid);

