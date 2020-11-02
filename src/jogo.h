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
int movimenta_inimigo(inimigo_st *inimigo);
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
int mov_valida(char adjacentes[4], int mov);
