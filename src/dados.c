#include "dados.h"

void limpa_save(gravacao_st *gravacao)
{
    gravacao->identificador = 0;
    gravacao->totalpts = 0;
    gravacao->ultimafase = 0;
    gravacao->vidas = 0;
    gravacao->nome_jogador[0] = '\0';
    gravacao->tempo_total_segundos = 0;
    gravacao->tempo_fase_segundos = 0;
}

void limpa_record(recorde_st *recorde)
{
    recorde->nome_jogador[0] = '\0';
    recorde->totalpts = 0;
    recorde->tempo_total_segundos = 0;
}
