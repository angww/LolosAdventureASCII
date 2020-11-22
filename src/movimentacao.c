#include "movimentacao.h"

int movimenta_inimigos(mapa_st *mapa, lolo_st *lolo, int y_inicio_info,
    int y_delta_info)
{
    for ( int i = 0; i < mapa->inimigos_num; i++ ) {
        /*
         * Se o inimigo pegou Lolo, diminui a vida de Lolo e remove o
         * inimigo
         */
        if ( movimenta_inimigo((mapa->inimigos)[i]) ) {
            #if DEBUG
                debug_message("Inimigo pegou Lolo");
            #endif

            if ( !(limpa_inimigo_pos(&(mapa->inimigos), &(mapa->inimigos_num),
                lolo->pos.y, lolo->pos.x)) ) {
                lolo->vidas--;
                lolo->pontos += 30;
                atualiza_info(lolo, mapa, y_delta_info, y_inicio_info,
                    ATUALIZA_VIDA|ATUALIZA_INIMIGO|ATUALIZA_PONTOS);
            } else {
                #if DEBUG
                    debug_message("Erro ao limpar inimigo, encerrando");
                #endif

                return 1;
            }
        }
    }

    return 0;
}

ponto_st muda_pos(ponto_st pos, int key)
{
    switch ( key ) {
        /* Lolo e inimigo */
        case 0:
        case KEY_UP:
            pos.y--;
            break;
        case 1:
        case KEY_DOWN:
            pos.y++;
            break;
        case 2:
        case KEY_RIGHT:
            pos.x++;
            break;
        case 3:
        case KEY_LEFT:
            pos.x--;
            break;
        default:
            break;
    }

    return pos;
}

int movimenta_lolo(lolo_st *lolo, mapa_st *mapa, int key)
{
    /* Próxima posição de Lolo */
    ponto_st new_pos = muda_pos(lolo->pos, key);
    /* Usado no caso de new_pos ser a posição de um bloco móvel */
    ponto_st bloco_pos;

    /* ch -> próxima localicazão, _ch usado caso seja BLOCO_MOVEL */
    chtype ch = mvinch(new_pos.y, new_pos.x) & A_CHARTEXT; /* Extrai o texto */
    chtype _ch;
    /* Indica se precisamos mudar a posição de lolo em sua estrutura */
    int movimenta = 1;
    /* Valor a ser retornado, indica se devemos atualizar alguma informação */
    int atualiza = 0;

    switch ( ch ) {
        case BLOCO_FIXO:
            movimenta = 0;
            break;
        case BLOCO_MOVEL:
            bloco_pos = muda_pos(new_pos, key);
            _ch = mvinch(bloco_pos.y, bloco_pos.x) & A_CHARTEXT;

            /*
             * Se a próxima posição do bloco móvel estiver livre então é válido,
             * imprime o caractere na tela e atualiza o elementos de mapa
             */
            if ( _ch == LIVRE ) {
                exibe_caractere_jogo(BLOCO_MOVEL, bloco_pos.y, bloco_pos.x);
                atualiza_grid_mapa(mapa, new_pos, LIVRE);
                atualiza_grid_mapa(mapa, bloco_pos, BLOCO_MOVEL);

                #if DEBUG
                    debug_message("Lolo moveu um bloco");
                #endif
            } else {
                movimenta = 0;
            }
            break;
        case INIMIGO:
            if ( limpa_inimigo_pos(&(mapa->inimigos), &(mapa->inimigos_num),
                new_pos.y, new_pos.x) ) {
                atualiza = ATUALIZA_ERRO;
                movimenta = 0;
            } else {
                lolo->vidas--;
                lolo->pontos += 30;
                atualiza = ATUALIZA_INIMIGO|ATUALIZA_VIDA|ATUALIZA_PONTOS;

                #if DEBUG
                    debug_message("Lolo pegou um inimigo");
                #endif
            }
            break;
        case AGUA:
            lolo->vidas--;
            atualiza = ATUALIZA_AGUA|ATUALIZA_VIDA;

            #if DEBUG
                debug_message("Lolo se afogou");
            #endif

            break;
        case CORACAO:
            /* Remove o coração dos elementos do mapa */
            atualiza_grid_mapa(mapa, new_pos, LIVRE);
            mapa->coracoes_num--;
            lolo->vidas++;
            atualiza = ATUALIZA_CORACAO|ATUALIZA_VIDA;

            #if DEBUG
                debug_message("Lolo pegou um coracao");
            #endif

            break;
        case BAU:
            /* Se o baú não estiver aberto lolo não pode passar por ele */
            if ( !(mapa->inimigos_num == 0 && mapa->coracoes_num == 0) ) {
                movimenta = 0;
            } else {
                atualiza = ATUALIZA_GANHOU;
            }
            break;
        /* Bloco Livre */
        default:
            break;
    }

    /* Atualiza a posição de Lolo em sua estrtura */
    if ( movimenta ) {
        /* Exibe o caractere que estava abaixo de lolo */
        exibe_caractere_jogo((mapa->elementos)[(lolo->pos.y)-1][(lolo->pos.x)-1],
            lolo->pos.y, lolo->pos.x);
        exibe_caractere_jogo(LOLO, new_pos.y, new_pos.x);
        lolo->pos = new_pos;
    }

    /* retorno o código específico */
    return atualiza;
}

int movimenta_inimigo(inimigo_st *inimigo)
{
    int mov = 0;
    int _mov;
    char adjacentes[4];
    int possibilidades = 0;

    /* Salva as posições adjacentes ao inimigo */
    adjacentes[0] = mvinch(inimigo->pos.y - 1, inimigo->pos.x) & A_CHARTEXT;
    adjacentes[1] = mvinch(inimigo->pos.y + 1, inimigo->pos.x) & A_CHARTEXT;
    adjacentes[2] = mvinch(inimigo->pos.y, inimigo->pos.x + 1) & A_CHARTEXT;
    adjacentes[3] = mvinch(inimigo->pos.y, inimigo->pos.x - 1) & A_CHARTEXT;

    /* Verifica quantas posições válidas existem */
    for ( int i = 0; i < 4; i++ ) {
        if ( !(adjacentes[i] & MASCARA_INIMIGO) ) {
            possibilidades++;
        }
    }

    /* Se não tiver nenhuma posição válida, não se move */
    if ( possibilidades == 0 ) {
        return 0;
    }

    /* Gera 0 até posibilidades -1 */
    _mov = (rand() % possibilidades);

    /* Vai pelas posições válidas */
    for ( int i = 0; i < _mov + 1; i++ ) {
        mov = prox_mov(adjacentes, mov);
    }

    /* Desenha espaço livre onde o inimigo estava */
    exibe_caractere_jogo(LIVRE, inimigo->pos.y, inimigo->pos.x);

    /* Atualiza a posição do inimigo */
    inimigo->pos = muda_pos(inimigo->pos, mov);

    if ( adjacentes[mov] == LOLO ) {
        /* Inimigo pegou Lolo */
        return 1;
    }

    /* Desenha o inimigo na nova posição */
    exibe_caractere_jogo(INIMIGO, inimigo->pos.y, inimigo->pos.x);

    return 0;
}

int prox_mov(char adjacentes[4], int mov) {
    /* Soma mov até que adjacentes[mov] seja uma posição válida para o inimigo */
    do {
        if ( mov == 3 ) {
            mov = 0;
        } else {
            mov++;
        }
    } while ( adjacentes[mov] & MASCARA_INIMIGO );

    return mov;
}
