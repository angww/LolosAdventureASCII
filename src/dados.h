#pragma once

#include "defines_lolo.h"
#include "selecionar_opcoes_posicao.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

/* Prepara o mapa uso */
int processa_mapa(mapa_st *mapa);

/* Remove qualquer lixo que possa ter */
void limpa_save(gravacao_st *gravacao);
void limpa_record(recorde_st *recorde);

/* Exibe todos os dados */
void exibe_dados_inicial(gravacao_st *gravacao, mapa_st *mapa, lolo_st *lolo,
    int *y_delta, int *y_inicio);
/* Formata time em relação ao tempo 0, formatação limitada a 00:00:00 */
void formata_delta_tempo(char *buf, int size, int time);
