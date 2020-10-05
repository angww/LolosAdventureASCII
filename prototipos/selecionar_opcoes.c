#include <ncurses.h>

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

    /*
     * Inicializa a cor que será usada para o highlight.
     */
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    do {
        for ( int i = 1; i < argc; i++ ) {
            /* Move o cursor para a próxima linha */
            move((i - 1), 0);

            /*
             * Se for o item que está atualmente selecionado exibe ele com
             * o padrão de cores definido e volta ao normal.
             */
            if ( (i-1) == opcao ) {
                attron(COLOR_PAIR(1));
                printw("%s", argv[i]);
                attroff(COLOR_PAIR(1));
            } else {
                printw("%s", argv[i]);
            }
        }

        refresh();
        c = wgetch(stdscr);

        /*
         * Percorre as opção como uma lista infinita, se for muito para
         * cima volta para e baixo e vice-versa.
         */
        switch ( c ) {
            case KEY_UP:
                if ( opcao == 0 ) {
                    opcao = argc - 2;
                } else {
                    opcao--;
                }

                break;
            case KEY_DOWN:
                if ( opcao == argc - 2 ) {
                    opcao = 0;
                } else {
                    opcao++;
                }

                break;
            default:
                break;
        }
    /*
     * Para de executar se for apertado ENTER ou a seta da direita.
     */
    } while ( c != '\n' && c != KEY_RIGHT );

    /*
     * Limpa a tela e volta para o início.
     */
    clear();
    move(0, 0);

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
