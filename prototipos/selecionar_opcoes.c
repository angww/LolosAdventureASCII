#include <ncurses.h>
#include <stdio.h>

#define MUDANCA_NENHUMA     0
#define MUDANCA_INICIO      1
#define MUDANCA_BAIXO       2
#define MUDANCA_CIMA        3
#define MUDANCA_CICLO_BAIXO 4
#define MUDANCA_CICLO_CIMA  5

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

int seleciona_opcao(char **opcoes, int num_opcoes);
void exibe_opcoes(char **opcoes, int num_opcoes, int opcao_atual, int mudanca);

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

int seleciona_opcao(char **opcoes, int num_opcoes) {
    /* Primeira opção é selecionada por padrão */
    int opcao = 0;
    /* Indica que é a primeira vez a ser exibido */
    int mudanca = MUDANCA_INICIO;
    int ch = 0;

    do {
        /* Se a opção não mudou, podemos continuar exibindo o mesmo menu */
        if ( mudanca != MUDANCA_NENHUMA ) {
            exibe_opcoes(opcoes, num_opcoes, opcao, mudanca);
        }

        ch = wgetch(stdscr);

        /*
         * Percorre as opção como uma lista infinita, se for muito para
         * cima volta para e baixo e vice-versa.
         */
        switch ( ch ) {
            case KEY_UP:
                if ( opcao == 0 ) {
                    opcao = num_opcoes - 1;
                    mudanca = MUDANCA_CICLO_CIMA;
                } else {
                    opcao--;
                    mudanca = MUDANCA_CIMA;
                }

                break;
            case KEY_DOWN:
                if ( opcao == num_opcoes - 1 ) {
                    opcao = 0;
                    mudanca = MUDANCA_CICLO_BAIXO;
                } else {
                    opcao++;
                    mudanca = MUDANCA_BAIXO;
                }

                break;
            default:
                /* Indica que a opção não mudou */
                mudanca = MUDANCA_NENHUMA;
                break;
        }
    /* Para de executar se for apertado ENTER ou a seta da direita. */
    } while ( ch != '\n' && ch != KEY_RIGHT );


    /* Limpa a tela e volta para o início. */
    clear();
    move(0, 0);

    return opcao;
}

void exibe_opcoes(char **opcoes, int num_opcoes, int opcao_atual, int mudanca) {
    switch ( mudanca ) {
        /* 
         * Se for a primeira vez a ser exibido, imprime todos os itens
         * menos o incial, que está selecionado.
         */
        case MUDANCA_INICIO:
            for ( int i = 1; i < num_opcoes; i++ ) {
                /* Move o cursor para a próxima linha */
                move(i, 0);
                printw("%s", opcoes[i]);
            }
            break;
        /* Cada case vai para onde a opção anterior estava */
        case MUDANCA_CICLO_CIMA:
            /* Move para o primeiro item */
            move(0, 0);
            printw("%s", opcoes[0]);
            break;
        case MUDANCA_CICLO_BAIXO:
            /* Move para o último item */
            move(num_opcoes - 1, 0);
            printw("%s", opcoes[num_opcoes - 1]);
            break;
        case MUDANCA_CIMA:
            /* Move para o item abaixo da opção */
            move(opcao_atual + 1, 0);
            printw("%s", opcoes[opcao_atual + 1]);
            break;
        case MUDANCA_BAIXO:
            /* Move para o item acima da opção */
            move(opcao_atual - 1, 0);
            printw("%s", opcoes[opcao_atual - 1]);
            break;
        case MUDANCA_NENHUMA:
        default:
            break;
    }

    /* Move o cursor a opção que está selecionada */
    move(opcao_atual, 0);
    /* Inicia a cor do highlight */
    attron(COLOR_PAIR(1));
    /* Exibe a opção com o highlight */
    printw("%s", opcoes[opcao_atual]);
    /* Volta a cor normal */
    attroff(COLOR_PAIR(1));

    /* Imprime as alterações na tela */
    refresh();
}
