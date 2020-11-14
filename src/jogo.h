#pragma once

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "defines_lolo.h"
#include "arquivos.h"
#include "cores.h"
#include "menus.h"
#include "dados.h"
#include "janela_tamanho.h"
#include "selecionar_opcoes_posicao.h"
#include "movimentacao.h"

/* Tecla 254 escolhida arbitrariamente para GAME_OVER */
#define GAME_OVER      254

/* Atualiza determinada informação, dada por ATUALIZA_* */
void atualiza_info(lolo_st *lolo, mapa_st *mapa, int y_delta_info,
    int y_inicio_info, int atualiza);
/* Exibe toda a janela do jogo */
void exibe_jogo(lolo_st *lolo, gravacao_st *gravacao, mapa_st *mapa,
    int y_delta_info, int y_inicio_info);
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
/* Abre um novo jogo */
int novojogo(void);
/* Carrega um save e continuar a jogar nele */
int carregarjogo(void);
/* Diminui inicio dos tempos usados em gravação */
void altera_inicio(gravacao_st *gravacao, time_t inicio);
/* Atualiza o mapa no determinado ponto 'pos' colocando o item_grid */
void atualiza_grid_mapa(mapa_st *mapa, ponto_st pos, int item_grid);
