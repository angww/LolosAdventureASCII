#include "defines_lolo.h"
#include <stdlib.h>
#include <ncurses.h>

/* Movimenta o inimigo na tela, retorna 0 se não se moveu */
int movimenta_inimigo(inimigo_st *inimigo);
/* Abre um novo jogo */
int novojogo(void);
/* Carrega um save e continuar a jogar nele */
int carregarjogo(void);
/* Loop principal do jogo */
int loop_jogo(mapa_st mapa);
/* Retorna ponto_st com a posição alterada conforme key */
ponto_st muda_pos(ponto_st pos, int key);
/*
 * Movimenta Lolo pelo tela e retorna um código específico:
 * 0 -> Movimentação normal
 * 1 -> Não se moveu
 * 2 -> Lolo perdeu uma vida, verificar se era inimigo ou água
 * 3 -> Lolo pegou um coração
 * 4 -> Lolo está em um baú
 */
int movimenta_lolo(lolo_st *lolo, int key);
/* Retorna mov em um posição adjacente válida */
int mov_valida(char adjacentes[4], int mov);
