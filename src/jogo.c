#include "jogo.h"

int novojogo(void)
{
    return 0;
}

int carregarjogo(void)
{
    return 0;
}

int loop_jogo(mapa_st mapa)
{
    return 0;
}

ponto_st muda_pos(ponto_st pos, int key)
{
    /* Dependendo da tecla muda a posição */
    switch ( key ) {
        case KEY_UP:
            pos.y++;
            break;
        case KEY_DOWN:
            pos.y--;
            break;
        case KEY_RIGHT:
            pos.x++;
            break;
        case KEY_LEFT:
            pos.x--;
            break;
        default:
            break;
    }

    return pos;
}

int movimenta_lolo(lolo_st *lolo, int key)
{
    /* Próxima posição de Lolo */
    ponto_st new_pos = muda_pos(lolo->pos, key);
    /* Usado no caso de new_pos ser a posição de um bloco móvel */
    ponto_st bloco_pos;

    /* ch -> próxima localicazão, _ch usado caso seja BLOCO_MOVEL */
    int ch = mvinch(new_pos.y, new_pos.x);
    int _ch;
    /* Indica se precisamos mudar a posição de lolo em sua estrutura */
    int movimenta = 0;
    /* Valor a ser retornado */
    int ret = 0;

    switch ( ch ) {
        /* Não se mexe */
        case BLOCO_FIXO:
            ret = 1;
            break;
        /* Verifica se é válido */
        case BLOCO_MOVEL:
            bloco_pos = muda_pos(new_pos, key);
            _ch = mvinch(bloco_pos.y, bloco_pos.x);

            /* Se a próxima posição for um bloco móvel então é válido */
            if ( _ch == LIVRE ) {
                mvaddch(bloco_pos.y, bloco_pos.x, BLOCO_MOVEL);
                movimenta = 1;
            /* Se não for não fazemos nada */
            } else {
                /* Indica que não houve nenhuma mudança na posição */
                ret = 1;
            }
            break;
        case INIMIGO:
        case AGUA:
            /* Se tiver vidas o suficente, move-se e perde uma vida */
            if ( lolo->vidas > 0 ) {
                lolo->vidas--;
                movimenta = 1;
                ret = 2;
            /* Se não perdeu */
            } else {
                movimenta = 1;
                ret =  255;
            }
            break;
        /* Se foi uma coração devemos aumentar a vida */
        case CORACAO:
            lolo->vidas++;
            movimenta = 1;
            ret = 3;
            break;
        /*
        * Se foi o baú nos movemos para ele e verificamos no loop principal se está
        * aberto
        */
        case BAU:
            movimenta = 1;
            ret = 4;
            break;
        /* Bloco Livre */
        default:
            movimenta = 1;
            break;
    }

    /* Atualiza a posição de Lolo em sua estrtura */
    if ( movimenta ) {
        /* O loop deve ver se antigamente era um baú */
        mvaddch(lolo->pos.y, lolo->pos.x, LIVRE);
        mvaddch(new_pos.y, new_pos.x, LOLO);
        lolo->pos = new_pos;
    }

    /* retorno o código específico */
    return ret;
}

int movimenta_inimigo(inimigo_st *inimigo)
{
    int mov = 0;
    int _mov;
    char adjacentes[4];
    int possibilidades = 0;

    /* Salva as posições adjacentes ao inimigo */
    adjacentes[0] = mvinch(inimigo->pos.y + 1, inimigo->pos.x);
    adjacentes[1] = mvinch(inimigo->pos.y - 1, inimigo->pos.x);
    adjacentes[2] = mvinch(inimigo->pos.y, inimigo->pos.x + 1);
    adjacentes[3] = mvinch(inimigo->pos.y, inimigo->pos.x - 1);

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

    /* Posição da primeira posição válida */
    mov = mov_valida(adjacentes, mov);

    /* Gera 0 até posibilidades -1 */
    _mov = (rand() % possibilidades);

    /* Vai pelas posições válidas */
    for ( int i = 0; i < _mov; i++, mov++ ) {
        mov = mov_valida(adjacentes, mov);
    }

    /* Desenha espaço livre onde o inimigo estava */
    mvaddch(inimigo->pos.y, inimigo->pos.x, LIVRE);

    /*
     * Atualiza a posição do inimigo:
     *   KEY_UP    -> 259
     *   KEY_DOWN  -> 258
     *   KEY_RIGHT -> 261
     *   KEY_LEFT  -> 260
     */
    inimigo->pos = muda_pos(inimigo->pos, mov + KEY_UP);

    /* Desenha o inimigo na nova posição */
    mvaddch(inimigo->pos.y, inimigo->pos.x, INIMIGO);

    /* Indica que a posição do inimigo mudou */
    return 1;
}

int mov_valida(char adjacentes[4], int mov) {
    /* Soma mov até que adjacentes[mov] seja uma posição válida para o inimigo */
    while ( !(adjacentes[mov] & MASCARA_INIMIGO) ) {
        if ( mov == 3 ) {
            mov = 0;
        } else {
            mov++;
        }
    }

    return mov;
}
