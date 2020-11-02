#include "dados.h"

void limpa_save(gravacao_st *gravacao)
{
    gravacao->identificador = 0;
    gravacao->totalpts = 0;
    gravacao->ultimafase = 0;
    gravacao->vidas = 0;
    gravacao->nome_jogador[0] = '\0';
    gravacao->inicio = 0;
    gravacao->final = 0;
}

void limpa_record(recorde_st *recorde)
{
    recorde->nome_jogador[0] = '\0';
    recorde->totalpts = 0;
    recorde->tempo_total = 0;
}

void exibe_dados_inicial(gravacao_st *gravacao, mapa_st *mapa, lolo_st *lolo,
    int *y_delta, int *y_inicio)
{
    /* A distãncia dos itens será usada posteriormente no jogo */
    *y_delta = distancia_itens(9, 22, 3);
    *y_inicio = 3 + (*y_delta / 2);

    char infos[9][20];

    /* Formata as informações a serem exibidas */
    snprintf(infos[0], 19, "Jogador: %s", gravacao->nome_jogador);
    snprintf(infos[1], 19, "Vidas: %d", lolo->vidas);
    snprintf(infos[2], 19, "Inimigos: %d", mapa->inimigos_num);
    snprintf(infos[3], 19, "Coracoes: %d", mapa->coracoes_num);
    snprintf(infos[4], 19, "Fase atual: %d", gravacao->ultimafase+1);
    snprintf(infos[5], 19, "Pontucao: %d", lolo->pontos);

    /* Tempo sempre inicia com 00:00:00 */
    strncpy(infos[6], "Tempo:", 19);
    strncpy(infos[7], "00:00:00", 19);

    formata_delta_tempo(infos[8], 19,
        (int)difftime(gravacao->final, gravacao->inicio));

    /* exibe_itens gera core dump */
    for ( int i = 0; i < 9; i++ ) {
        exibe_item(infos[i], i, *y_inicio, *y_delta, 55+2+11);
    }
}

void formata_delta_tempo(char *buf, int size, int time)
{
    int horas = time / 3600;
    int minutos = (time % 3600) / 60;
    int segundos = time % 60;

    snprintf(buf, size, "%02d:%02d:%02d", horas, minutos, segundos);
}

int processa_mapa(mapa_st *mapa)
{
    /* O grid já deve estar no mapa, apenas exemplo */
    char tmp[JOGO_JANELA_Y][JOGO_JANELA_X] = {
        "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
        "P            PP                                       P",
        "P            PP   PPPPPPPPPPPPPPP  PPPPPP             P",
        "P     @      PP   PPPPPPPPPPPPPPP  PPPPPP             P",
        "P            PP         E                    C        P",
        "P            PP                                       P",
        "P   PPPPPPPPPPP   PPPPPPPPPPPPPPP  PPPPPP             P",
        "P   PPPPPPPPPPP   PPPPPPPPPPPPPPP  PPPPPP             P",
        "P                          PP          PP             P",
        "P                          PP          PP             P",
        "P                      E   PP        C PP             P",
        "P       C                  PP  E       PP             P",
        "P                          PP          PP             P",
        "P                          PP          PP             P",
        "PPPPPPPPPPPPPPPP           PP  C       PP             P",
        "PPPPPPPPPPPPPPPP           PP          PPPPPPPMMMPPPPPP",
        "PAA        E  PP           PP          PPPPPPP   PPPPPP",
        "PAAA          PP           PP      E   PP             P",
        "PAAAA                      PP          PP      E      P",
        "PAAA                       PP          PP             P",
        "PAA           PP           PP          PP             P",
        "PA       C    PP           PP   C      PP      T      P",
        "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP"};

    for ( int l = 0; l < JOGO_JANELA_Y; l++ ) {
        for ( int c = 0; c < JOGO_JANELA_X; c++ ) {
            mapa->elementos[l][c] = tmp[l][c];
        }
    }

    /* Limpa o lixo */
    mapa->inimigos = NULL;
    mapa->coracoes_num = 0;
    mapa->inimigos_num = 0;

    /* Percorre o mapa */
    for ( int l = 0; l < JOGO_JANELA_Y; l++ ) {
        for ( int c = 0; c < JOGO_JANELA_X; c++ ) {
            switch ( tmp[l][c] ) {
                case CORACAO:
                    mapa->coracoes_num++;
                    break;
                case INIMIGO:
                    mapa->inimigos_num++;
                    /* TODO: Adicionar inimigo */
                    break;
                case LOLO:
                    mapa->lolo.y = l;
                    mapa->lolo.x = c;
                    break;
                case BAU:
                    mapa->bau.y = l;
                    mapa->bau.x = c;
                    break;
                default:
                    break;
            }
        }
    }

    return 0;
}
