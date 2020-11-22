#include "selecionar_opcoes_posicao.h"
#include <stdlib.h>

/*
 * ./seleciona X1 X2 Y1 Y2 str1 str2 ...
 *
 * ./seleciona 2 78 7 23 "Novo Jogo" "Carregar Jogo" "Recordes" "Como Jogar" "Creditos" "Sair do Jogo"
 *
 * Dado os argumentos que foram passados ao executar, exibe uma lista com
 * a linha atual destacada.
 */

int main(int argc, char **argv) {
    /* Não há itens a serem exibidos. */
    if ( argc < 6 ) {
        printf("Voce deve fornecer o tamanho e os argumentos.\n");
        printf("\t./%s X1 X2 Y1 Y2 ARGS...\n", argv[0]);
        return 1;
    }

    int opcao = 0;
    int c;

    initscr();

    /* Inicia o método de entrada. */
    curs_set(0);
    noecho();
    raw();
    keypad(stdscr, true);
    halfdelay(2);

    /*
     * Se não há suporte para cores, retorna código de erro, qualquer valor
     * diferente de 0 indica uma má execução.
     */
    if ( !(has_colors()) ) {
        return 2;
    }

    /* Armazena o endereço do primeiro argumento */
    char **str;
    str = &argv[5];

    /* Inicializa a cor que será usada para o highlight. */
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    struct tamanho_grid grid;
    grid.x[GRID_COMECO] = atoi(argv[1]);
    grid.x[GRID_FINAL] = atoi(argv[2]);
    grid.y[GRID_COMECO] = atoi(argv[3]);
    grid.y[GRID_FINAL] = atoi(argv[4]);

    opcao = seleciona_opcao(str, argc-5, grid);

    move(0,0);
    clear();

    printw("A opcao selecionada foi: %s\n", argv[opcao+5]);
    printw("Pressione ENTER para sair.\n");

    refresh();

    /*
     * Aguarda qe seja apertado ENTER.
     */
    do {
        c = wgetch(stdscr);
    } while ( c != '\n' );

    endwin();

    return 0;
}
