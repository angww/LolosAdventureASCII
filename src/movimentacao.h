#pragma once

#include <stdlib.h>
#include <ncurses.h>
#include "defines_lolo.h"
#include "cores.h"
#include "dados.h"
#include "jogo.h"

int movimenta_inimigos(mapa_st *mapa, lolo_st *lolo, int y_inicio_info,
    int y_delta_info);
/* Movimenta o inimigo na tela, retorna 0 se não se moveu */
int movimenta_inimigo(inimigo_st *inimigo);
/* Retorna ponto_st com a posição alterada conforme key */
ponto_st muda_pos(ponto_st pos, int key);
/* Movimenta Lolo, valor retorna definido por ATUALIZA_* */
int movimenta_lolo(lolo_st *lolo, mapa_st *mapa, int key);
/* Retorna mov em um posição adjacente válida */
int prox_mov(char adjacentes[4], int mov);
