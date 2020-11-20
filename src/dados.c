#include "dados.h"

void limpa_save(gravacao_st *gravacao)
{
    gravacao->identificador = 0;
    gravacao->totalpts = 0;
    gravacao->ultimafase = 0;
    gravacao->vidas = 0;

    for ( int i = 0; i < 8; i++ )
        gravacao->nome_jogador[i] = '=';
    gravacao->nome_jogador[8] = '\0';

    gravacao->inicio = 0;
    gravacao->final = 0;
}

void limpa_record(recorde_st *recorde)
{
    recorde->nome_jogador[0] = '\0';
    recorde->totalpts = 0;
    recorde->tempo_total = 0;
}

void grava_inicial_fake_record(recorde_st *recorde)
{
    int pts[] = { 30, 29, 28, 20, 10 };
    int tmp[] = { 110, 120, 130, 140, 150 };
    char *nomes[] = { "John Doe", "DerikOwn", "MikaShaw", "Ross Ste", "SteveWoz" };

    for ( int i = 0; i < 5; i++ ) {
        recorde[i].totalpts = pts[i];
        recorde[i].tempo_total = tmp[i];
        strncpy(recorde[i].nome_jogador, nomes[i], 9);
    }
}

int maior_id(gravacao_st gravacao[5])
{
    int id = -1;
    int id_tmp;

    for ( int i = 0; i < 5; i++ ) {
        id_tmp = gravacao[i].identificador;
        if ( id_tmp > id ) {
            id = id_tmp;
        }
    }

    return id;
}

int id_disponivel(gravacao_st gravacao[5], int id)
{
    for ( int i = 0; i < 5; i++ ) {
        if ( gravacao[i].identificador == id ) {
            return 0;
        }
    }

    return 1;
}

int num_gravacoes(gravacao_st gravacao[5])
{
    int ngravacoes = 0;

    for ( int i = 0; i < 5; i++ ) {
        if ( gravacao[i].identificador ) {
            ngravacoes++;
        }
    }

    return ngravacoes;
}

void exibe_todos_dados(gravacao_st *gravacao, mapa_st *mapa, lolo_st *lolo,
    int y_delta, int y_inicio)
{
    char infos[9][20];

    /* Formata as informações a serem exibidas */
    snprintf(infos[0], 19, "Jogador: %s", gravacao->nome_jogador);
    snprintf(infos[1], 19, "Vidas: %d", lolo->vidas);
    snprintf(infos[2], 19, "Inimigos: %d", mapa->inimigos_num);
    snprintf(infos[3], 19, "Coracoes: %d", mapa->coracoes_num);
    snprintf(infos[4], 19, "Fase atual: %d", gravacao->ultimafase+1);
    snprintf(infos[5], 19, "Pontucao: %d", lolo->pontos);

    strncpy(infos[6], "Tempo:", 19);
    formata_delta_tempo(infos[7], 19,
        (int)difftime(time(NULL), gravacao->final));
    formata_delta_tempo(infos[8], 19,
        (int)difftime(gravacao->final, gravacao->inicio));

    /* exibe_itens gera core dump */
    for ( int i = 0; i < 9; i++ ) {
        exibe_item(infos[i], i, y_inicio, y_delta, 55+2+11);
    }
}

void atualiza_info(lolo_st *lolo, mapa_st *mapa, int y_delta_info,
    int y_inicio_info, int atualiza)
{
    char buf[19];

    if ( atualiza & ATUALIZA_VIDA ) {
          snprintf(buf, 19, "Vidas: %d", lolo->vidas);
          exibe_item(buf, 1, y_inicio_info, y_delta_info, 55+2+11);
    }
    if ( atualiza & ATUALIZA_INIMIGO ) {
        snprintf(buf, 19, "inimigos: %d", mapa->inimigos_num);
        exibe_item(buf, 2, y_inicio_info, y_delta_info, 55+2+11);
    }
    if ( atualiza & ATUALIZA_CORACAO ) {
        snprintf(buf, 19, "Coracoes: %d", mapa->coracoes_num);
        exibe_item(buf, 3, y_inicio_info, y_delta_info, 55+2+11);
    }
    if ( atualiza & ATUALIZA_PONTOS ) {
        snprintf(buf, 19, "Pontucao: %d", lolo->pontos);
        exibe_item(buf, 5, y_inicio_info, y_delta_info, 55+2+11);
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
    #ifdef DEBUG
        debug_message("Processando nivel");
    #endif

    int ret = 0;

    /* Percorre o mapa */
    for ( int l = 0; l < JOGO_JANELA_Y; l++ ) {
        for ( int c = 0; c < JOGO_JANELA_X; c++ ) {
            /* l+1 e c+1 serão as posições na tela */
            switch ( mapa->elementos[l][c] ) {
                case CORACAO:
                    mapa->coracoes_num++;
                    break;
                case INIMIGO:
                    mapa->elementos[l][c] = LIVRE;
                    mapa->inimigos_num++;
                    ret = adiciona_inimigo(&(mapa->inimigos), l+1, c+1,
                        mapa->inimigos_num);
                    break;
                case LOLO:
                    mapa->elementos[l][c] = LIVRE;
                    mapa->lolo.y = l+1;
                    mapa->lolo.x = c+1;
                    break;
                case BAU:
                    mapa->bau.y = l+1;
                    mapa->bau.x = c+1;
                    break;
                default:
                    break;
            }
        }

        /* Não foi possível alocar espaço para os inimigos */
        if ( ret ) {
            #ifdef DEBUG
                debug_message("Nao foi possivel alocar espaco para os inimigos");
            #endif

            return 1;
        }
    }

    #ifdef DEBUG
        debug_message("Nivel processado");
    #endif

    return 0;
}

int adiciona_inimigo(inimigo_st ***inimigos, int linha, int coluna, int inimigos_num)
{
    /* Tenta realocar, se tmp_list for NULL não conseguiu */
    inimigo_st **tmp_list;
    tmp_list = realloc(*inimigos, sizeof (inimigo_st *) * inimigos_num);

    inimigo_st *tmp_inimigo;
    tmp_inimigo = malloc(sizeof (inimigo_st));

    /* Limpa a memória que estava sendo usada e retorna 1 */
    if ( tmp_list == NULL || tmp_inimigo == NULL ) {
        #ifdef DEBUG
            debug_message("Nao foi possivel alocar memoria para os inimigos");
        #endif

        if ( tmp_inimigo != NULL ) {
            free(tmp_inimigo);
        }

        limpa_inimigos(inimigos, inimigos_num - 1);

        return 1;
    } else {
        /* Ponteiro para inimigo já foi limpo pelo realloc */
        *inimigos = (inimigo_st **)tmp_list;
    }

    /* Adiciona o inimigo ao final da lista */
    tmp_inimigo->pos.y = linha;
    tmp_inimigo->pos.x = coluna;
    (*inimigos)[inimigos_num-1] = tmp_inimigo;

    return 0;
}

int limpa_inimigos(inimigo_st ***inimigos, int inimigos_num)
{
    /* Se o ponteiro for NULL ou não tiver inimigos, não precisa ser limpo */
    if ( *inimigos == NULL || inimigos_num == 0 ) {
        return 0;
    }

    /* Limpa cada inimigo alocado */
    for ( int i = 0; i < inimigos_num; i++ ) {
        free((*inimigos)[i]);
    }

    /* Limpa o ponteiro */
    free(*inimigos);

    return 0;
}

int limpa_inimigo_pos(inimigo_st ***inimigos, int *inimigos_num, int y, int x)
{
    inimigo_st *inimigo_tmp;
    inimigo_st ***inimigos_tmp;

    /* Procura pelo inimigo */
    for ( int i = 0; i < *inimigos_num; i++ ) {
        inimigo_tmp = (*inimigos)[i];

        /* Se encontrou o inimigo, faz p receber o valor de p+1 */
        if ( inimigo_tmp->pos.y == y && inimigo_tmp->pos.x == x ) {
            /* Altera o valor dos ponteiros */
            for ( int j = i; j < (*inimigos_num) - 1; j++ ) {
                *((*inimigos)[j]) = *((*inimigos)[j+1]);
            }

            (*inimigos_num)--;
            free((*inimigos)[*inimigos_num]);

            /* Diminui a memória alocada */
            inimigos_tmp = realloc(*inimigos,
                sizeof (inimigo_st *) * (*inimigos_num));

            /* Verifica se conseguiu diminuir a memória alocada */
            if ( inimigos_tmp == NULL && (*inimigos_num) > 0 ) {
                #ifdef DEBUG
                    debug_message("Nao foi possivel diminuir o numero de "
                        "inimigos");
                #endif

                return 1;
            } else {
                *inimigos = (inimigo_st **)inimigos_tmp;
            }

            return 0;
        }
    }

    #ifdef DEBUG
        debug_message("Alerta: Nao foi encontrado inimigo em: (%d, %d)", y, x);
    #endif

    /* Não encontrou o inimigo */
    return 1;
}

int formata_gravacao(gravacao_st gravacao[5], char opcoes[5][60])
{
    int num_gravacoes = 0;
    char tempo_formatado[10];

    for ( int i = 0; i < 5; i++ ) {
        if ( gravacao[i].identificador != 0 ) {
            formata_delta_tempo(tempo_formatado, 10, (int)difftime(
                gravacao[i].final, gravacao[i].inicio));
            snprintf(opcoes[num_gravacoes], 59,
                "#%d   %d   %05d   %d   %9s   %6s", gravacao[i].identificador,
                gravacao[i].ultimafase+1, gravacao[i].totalpts,
                gravacao[i].vidas, gravacao[i].nome_jogador, tempo_formatado);
            num_gravacoes++;
        } else {
            strncpy(opcoes[i], "Espaco livre", 60);
        }
    }

    return num_gravacoes;
}
