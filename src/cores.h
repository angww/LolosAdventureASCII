#pragma once

#include <ncurses.h>
#include "defines_lolo.h"

/* Cores */
#define HIGHLIGHT    1
#define LOLO_COR     2
#define INIMIGO_COR  3
#define AGUA_COR     4
#define BAU_COR      5
#define MOVEL_COR    6
#define FIXO_COR     7
#define CORACAO_COR  8

void inicializa_cores(void);
void desenha_borda(WINDOW *win);
void exibe_caractere_jogo(char ch, int y, int x);
void exibe_caractere_colorido(char ch, short cor);
