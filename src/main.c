#include <stdlib.h>
#include <ncurses.h>
#include <strings.h>
#include <unistd.h> /* usleep() */

#include "defines_lolo.h"
#include "janelas.h"
#include "utils.h"

void play() {

    #ifdef DEBUG
        //printf("DEBUG ON"); // TODO: Criar um lugar na janela que mostre que o debug está ativado
    #endif

        desenha_janela_titulo(STR_MENU_PRINCIPAL);
        getchar();

}

int main() {

    /* Começa o curses mode */
    initscr();

    /* Esconde o cursor piscante do prompt */
    curs_set(0);

    /* */ 
    play();
        
    /* Encerra o curses mode */
    endwin();

    return 0;
}