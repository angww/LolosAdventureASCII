#include "jogo.h"

int movimenta_inimigo(inimigo_st inimigo)
{
    int mov = 0;
    int _mov;
    char adjacentes[4];
    int possibilidades = 0;

    adjacentes[0] = mvinch(inimigo.pos.y + 1, inimigo.pos.x);
    adjacentes[1] = mvinch(inimigo.pos.y - 1, inimigo.pos.x);
    adjacentes[2] = mvinch(inimigo.pos.y, inimigo.pos.x + 1);
    adjacentes[3] = mvinch(inimigo.pos.y, inimigo.pos.x - 1);

    for ( int i = 0; i < 4; i++ ) {
        if ( !(adjacentes[i] & MASCARA_INIMIGO) ) {
            possibilidades++;
        }
    }

    if ( possibilidades == 0 ) {
        return 0;
    }

    while ( !(adjacentes[mov] & MASCARA_INIMIGO) ) {
        if ( mov == 3 ) {
            mov = 0;
        } else {
            mov++;
        }
    }

    _mov = (rand() % possibilidades);

    for ( int i = 0; i < _mov; i++ ) {
        mov++;

        while ( !(adjacentes[mov] & MASCARA_INIMIGO) ) {
            if ( mov == 3 ) {
                mov = 0;
            } else {
                mov++;
            }
        }
    }

    return ++mov;
}
