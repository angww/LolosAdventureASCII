#pragma once
#include "defines_lolo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * Para que o arquivo do mapa seja válido, deve
 * ter a constante VERIFICADOR no seu começo.
 */
#define VERIFICADOR "1234567890"

/* Extensão do mapa processado */
#define EXTENSAO ".bin"

int adiciona_coracao(struct mapa *mp, int linha, int coluna);
int adiciona_bau(struct mapa *mp, int linha, int coluna);
int adiciona_inimigo(struct mapa *mp, int linha, int coluna);
int adiciona_bloco_movel(struct mapa *mp, int linha, int coluna);
int limpa_memoria(struct mapa *mp);
int processa_mapa(struct mapa *mp, char grid[21][53]);
int escreve_arquivo(char *filename, struct mapa *mp);
int carrega_arquivo(char *filename, struct mapa *mp);
int inicializa_mapa(struct mapa *mp);
