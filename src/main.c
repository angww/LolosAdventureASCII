#include <ncurses.h>
#include <signal.h>
#include "defines_lolo.h"

const void handler_segfault(int code);

int main(int argc, char **argv) {
    /* Abre o arquivo de debug e escreve uma mensagem */
    #ifdef DEBUG
        FILE *fp;
        fp = fopen(DEBUG_FILENAME, "a");
        fprintf(fp, "Debug ativado.\n");
        fclose(fp);
    #endif

    /* Caso ocorra Segmentation Fault, é chamado handler. */
    signal(SIGSEGV, handler_segfault);

    /* Inicializa a janela */
    initscr();

    /* Configura a entrada */
    noecho();
    curs_set(0);
    keypad(stdscr, true);

    /* Encerra a janela */
    endwin();

    return 0;
}

const void handler_segfault(int code) {
    #ifdef DEBUG
        FILE *fp;
        fp = fopen(DEBUG_FILENAME, "a");
        fprintf(fp, "Segmentation Fault.\n");
        fclose(fp);
    #endif

    /* Usar futuramente para limpar memória alocada */
    endwin();

    printf("Segmentation Fault\n");
}
