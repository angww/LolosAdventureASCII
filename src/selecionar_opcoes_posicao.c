#include "selecionar_opcoes_posicao.h"
#include "defines_lolo.h"
#include "janela_tamanho.h"

int seleciona_opcoes(char **opcoes, int num_opcoes, int y_inicio, int y_delta,
    int x_meio, int modo)
{
    /* Primeira opção é selecionada por padrão */
    int opcao = 0;
    int ch = 0;
    int mudanca = MUDANCA_OPCAO;

    /* Exibe todos os itens */
    if ( modo < 0 ) {
        return -1;
    } else if ( modo ) {
        for ( int i = 0; i < num_opcoes; i++ ) {
            exibe_item((((char *) (opcoes)) + (i * modo)), i, y_inicio, y_delta,
                x_meio);
        }
    } else {
        exibe_itens(opcoes, num_opcoes, y_inicio, y_delta, x_meio);
    }

    /* Execta o loop até que uma opção seja selecionada */
    do {
        /*
         * Se a opção não mudou, não precisamos exibir novamente o item com
         * highlight
         */
        if ( mudanca == MUDANCA_OPCAO ) {
            /* Imprime apenas o item com hightlight */
            if ( modo ) {
                exibe_opcao(((char *) opcoes) + (opcao * modo), opcao, y_inicio,
                    y_delta, x_meio);
            } else {
                exibe_opcao(opcoes[opcao], opcao, y_inicio, y_delta, x_meio);
            }
        }

        /* Aplica as mudanças à stdscr */
        refresh();

        /* Recebe a entrada do teclado */
        ch = wgetch(stdscr);

        /*
         * Percorre as opção como uma lista infinita, se for muito para
         * cima volta para e baixo e vice-versa.
         */
        switch ( ch ) {
            case KEY_UP:
                /* Remove highlight que estava no item anterior */
                if ( modo ) {
                    exibe_item(((char *) opcoes) + (opcao * modo), opcao,
                        y_inicio, y_delta, x_meio);
                } else {
                    exibe_item(opcoes[opcao], opcao, y_inicio, y_delta, x_meio);
                }
                /*
                 * Indica que houve mudança na seleção, quando o loop for
                 * executado novamente irá imprimir o item selecionado com o
                 * highlight
                 */
                mudanca = MUDANCA_OPCAO;

                /* Se a última opção era a primeira, seleciona a última */
                if ( opcao == 0 ) {
                    opcao = num_opcoes - 1;
                /* Se não seleciona a que está acima */
                } else {
                    opcao--;
                }

                break;
            case KEY_DOWN:
                if ( modo ) {
                    exibe_item(((char *) opcoes) + (opcao * modo), opcao,
                        y_inicio, y_delta, x_meio);
                } else {
                    exibe_item(opcoes[opcao], opcao, y_inicio, y_delta, x_meio);
                }
                mudanca = MUDANCA_OPCAO;

                /* Se a última opção era a última, seleciona a primeira */
                if ( opcao == num_opcoes - 1 ) {
                    opcao = 0;
                /* Se não seleciona a que está abaixo */
                } else {
                    opcao++;
                }
                break;
            case KEY_LEFT:
            case ESC:
            case KEY_RESIZE:
                /*
                 * A função que chamou seleciona_opcao é quem deve lidar com o
                 * ESC e com KEY_RESIZE.
                */
                opcao = ch;
                break;
            default:
                /* Indica que a opção não mudou */
                mudanca = 0;
                break;
        }
    /*
     * Para de executar se for apertado ENTER, seta da direita, ESC ou tenha
     * mudado o tamanho da tela
     */
   } while ( ch != '\n' && ch != KEY_RIGHT && ch != KEY_LEFT &&
             ch != KEY_RESIZE && ch != ESC);

    /*
     * Retorna a opção, a função que chamou o seleciona_opcao deve lidar
     * com cada  caso
     */
    return opcao;
}

int seleciona_opcao(char *opcao, int y_pos, int x_meio)
{
    int ch = 0;

    /* Exibe a opção com highlight */
    exibe_opcao_pos(opcao, y_pos, x_meio);

    /* Aplica as mudanças à stdscr */
    refresh();

    /* Execta o loop até que uma opção seja selecionada */
    do {
        /* Recebe a entrada do teclado */
        ch = wgetch(stdscr);

        /* Não é necessário tratar a opção */
    /*
     * Para de executar se for apertado ENTER, seta da direita, ESC ou tenha
     * mudado o tamanho da tela
     */
   } while ( ch != '\n' && ch != KEY_RIGHT && ch != KEY_LEFT &&
             ch != KEY_RESIZE && ch != ESC);

    /*
     * Retorna a opção, a função que chamou o seleciona_opcao deve lidar
     * com cada  caso
     */
    return ch;
}

void exibe_itens(char *opcoes[], int num_opcoes, int y_inicio, int y_delta,
    int x_meio)
{
    /* Variável auxiliar */
    int x_atual;

    /* Exibe da primeira até a última opção */
    for ( int i = 0, y = y_inicio; i < num_opcoes; i++, y += y_delta ) {
          /* Calcula o ponto X onde deverá escrever */
          x_atual = x_meio - (int)(strlen(opcoes[i]) / 2);
          mvprintw(y, x_atual, "%s", opcoes[i]);
    }
}

void exibe_item(char *opcao, int num, int y_inicio, int y_delta, int x_meio)
{
    /* Variáveis auxiliares para mover o cursor */
    int y_opcao;
    int x_opcao;

    /* Atribui a posição a ser movido o cursor */
    y_opcao  = y_inicio + (y_delta * num);
    x_opcao = x_meio - (int)(strlen(opcao) / 2);

    /* Move o cursor a opção que será imprimida */
    move(y_opcao, x_opcao);

    /* Exibe a opção */
    printw("%s", opcao);
}

void exibe_opcao(char *opcao, int opcao_num, int y_inicio, int y_delta,
    int x_meio)
{
    int y_opcao;
    int x_opcao;

    y_opcao  = y_inicio + (y_delta * opcao_num);
    x_opcao = x_meio - (int)(strlen(opcao) / 2);

    /* Move o cursor a opção que está selecionada */
    move(y_opcao, x_opcao);
    /* Inicia a cor do highlight */
    attron(COLOR_PAIR(HIGHLIGHT));
    /* Exibe a opção com o highlight */
    printw("%s", opcao);
    /* Volta a cor normal */
    attroff(COLOR_PAIR(HIGHLIGHT));
}

void exibe_opcao_pos(char *opcao, int y_pos, int x_meio)
{
    int x_opcao = x_meio - (int)(strlen(opcao) / 2);

    /* Move o cursor a opção que está selecionada */
    move(y_pos, x_opcao);
    /* Inicia a cor do highlight */
    attron(COLOR_PAIR(HIGHLIGHT));
    /* Exibe a opção com o highlight */
    printw("%s", opcao);
    /* Volta a cor normal */
    attroff(COLOR_PAIR(HIGHLIGHT));
}
