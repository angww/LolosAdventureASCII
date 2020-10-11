#include "janela_tamanho.h"

#ifdef DEBUG
#include "debug.h"
#endif

void espera_tamanho_valido(void)
{
    int ch;
    int valido = 0;

    do {
        clear();
        move(0, 0);

        attron(COLOR_PAIR(1));
        printw("Tamanho inferior ao desejado(%d %d).\n", JANELA_MAX_Y, JANELA_MAX_X);
        attroff(COLOR_PAIR(1));

        ch = getch();
        if ( ch == KEY_RESIZE ) {
            valido = tamanho_valido();
        }
    } while ( !valido );

    clear();
}

void desenha_borda(WINDOW *win) {
    attron(COLOR_PAIR(1));
    wborder(win, 0,0,0,0,0,0,0,0);
    attroff(COLOR_PAIR(1));
}

int tamanho_valido(void)
{
    int valido;
    int max_y, max_x;

    getmaxyx(stdscr, max_y, max_x);
    valido = (max_y >= JANELA_MAX_Y ? (max_x >= JANELA_MAX_X ? 1 : 0 ) : 0);

    resize_term(JANELA_MAX_Y, JANELA_MAX_X);

    #ifdef DEBUG
        char message[DEBUG_MESSAGE_SIZE];
        snprintf(message, DEBUG_MESSAGE_SIZE, "Janela com tamanho alterado: (%d, %d), valido: %d", max_y, max_x, valido);
        write_debug_message(message);
    #endif

    return valido;
}
