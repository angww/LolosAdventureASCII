#include "../includes/selecionar_opcoes.h"

/*
 * Funcionamento:
 *      ./selecionar_opcoes 1 2 3 ...
 *
 * Dado os argumentos que foram passados ao executar, exibe uma lista com
 * a linha atual destacada.
 *
 * TODO:
 * Transformar em função, com o protótipo:
 *      int func(char **opções, int num_opções,
 *              int coord_x_min, int coord_x_max, 
 *              int coord_y_min, int coord_y_max);
 *
 * Com o objetivo de exbir n opções de forma centralizada, tanto
 * verticalmente e horizontalmente, em qualquer parte da tela.
 */

int main(int argc, char **argv) {
    /* Não há itens a serem exibidos. */
    if ( argc == 1 ) {
        printf("Voce deve fornecer argumentos.\n");
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
    str = &argv[1];

    /* Inicializa a cor que será usada para o highlight. */
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    opcao = seleciona_opcao(str, argc-1);

    printw("A opcao selecionada foi: %s\n", argv[opcao+1]);
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
