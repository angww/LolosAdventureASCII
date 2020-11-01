#include "cores.h"

void inicializa_cores(void)
{
    /* Inicializa as cores usadas pelo jogo */
    start_color();

    init_pair(HIGHLIGHT,   COLOR_BLACK,   COLOR_WHITE);
    init_pair(LOLO_COR,    COLOR_GREEN,   COLOR_BLACK);
    init_pair(INIMIGO_COR, COLOR_RED,     COLOR_BLACK);
    init_pair(AGUA_COR,    COLOR_BLUE,    COLOR_BLACK);
    init_pair(BAU_COR,     COLOR_MAGENTA, COLOR_BLACK);
    init_pair(FIXO_COR,    COLOR_WHITE,   COLOR_BLACK);
    init_pair(MOVEL_COR,   COLOR_CYAN,    COLOR_BLACK);
    init_pair(CORACAO_COR, COLOR_YELLOW,  COLOR_BLACK);
}

void exibe_caractere_jogo(char ch, int y, int x)
{
    move(y, x);

    switch ( ch ) {
        case LOLO:
            exibe_caractere_colorido(LOLO, LOLO_COR);
            break;
        case INIMIGO:
            exibe_caractere_colorido(INIMIGO, INIMIGO_COR);
            break;
        case AGUA:
            exibe_caractere_colorido(AGUA, AGUA_COR);
            break;
        case BLOCO_MOVEL:
            exibe_caractere_colorido(BLOCO_MOVEL, MOVEL_COR);
            break;
        case BLOCO_FIXO:
            exibe_caractere_colorido(BLOCO_FIXO, FIXO_COR);
            break;
        case BAU:
            exibe_caractere_colorido(BAU, BAU_COR);
            break;
        case CORACAO:
            exibe_caractere_colorido(CORACAO, CORACAO_COR);
            break;
        case LIVRE:
            addch(LIVRE);
            break;
    }
}

void exibe_caractere_colorido(char ch, short cor)
{
    attron(COLOR_PAIR(cor));
    addch(ch);
    attron(COLOR_PAIR(cor));
}

void desenha_borda(WINDOW *win)
{
    /* Inicializa highlight e desenha a borda padrão */
    attron(COLOR_PAIR(HIGHLIGHT));
    wborder(win, 0,0,0,0,0,0,0,0);
    attroff(COLOR_PAIR(HIGHLIGHT));
}