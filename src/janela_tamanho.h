#pragma once

#include "defines_lolo.h"
#include "cores.h"
#include <ncurses.h>

/* Espera que a janela seja no mínimo a definida em defines_lolo */
void espera_tamanho_valido(void);

/* verifica se o tamanho da janela é válido */
int tamanho_valido(void);
