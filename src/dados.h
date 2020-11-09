#pragma once

#include "defines_lolo.h"
#include "selecionar_opcoes_posicao.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "menus.h"

#define ATUALIZA_VIDA    1
#define ATUALIZA_CORACAO 2
#define ATUALIZA_INIMIGO 4
#define ATUALIZA_BAU     8
#define ATUALIZA_ERRO    16

/*
 * Adiciona um inimigo, alocado dinamicamente, para uma lista alocada
 * dinamicamente de inimigos
 */
int adiciona_inimigo(inimigo_st ***inimigos, int linha, int coluna, int inimigos_num);
/* Remove todos os inimigos e a lista de inimigos do heap */
int limpa_inimigos(inimigo_st ***inimigos, int inimigos_num);
/* Remove um inimigo da lista baseado em sua localização na tela */
int limpa_inimigo_pos(inimigo_st ***inimigos, int *inimigos_num, int y, int x);

/* Prepara o mapa para uso */
int processa_mapa(mapa_st *mapa);

/* Remove qualquer lixo que possa ter */
void limpa_save(gravacao_st *gravacao);
void limpa_record(recorde_st *recorde);

/* Exibe todos os dados */
void exibe_todos_dados(gravacao_st *gravacao, mapa_st *mapa, lolo_st *lolo,
    int y_delta, int y_inicio);
/* Formata time em relação ao tempo 0, formatação limitada a 00:00:00 */
void formata_delta_tempo(char *buf, int size, int time);
