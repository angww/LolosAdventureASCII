#include "selecionar_opcoes_posicao.h"

int seleciona_opcao(char **opcoes, int num_opcoes, struct tamanho_grid grid) {
    /* Primeira opção é selecionada por padrão */
    int opcao = 0;
    /* Indica que é a primeira vez a ser exibido */
    int mudanca = MUDANCA_INICIO;
    int ch = 0;

    /* Processa o grid para obter as posições desejadas */
    struct grid_processado grid_proc;
    grid_proc = processa_grid(grid, num_opcoes);

    do {
        /* Se a opção não mudou, não precisamos exibir novamente o menu */
        if ( mudanca != MUDANCA_NENHUMA ) {
            exibe_opcoes(opcoes, num_opcoes, opcao, mudanca, grid_proc);
        }

        ch = wgetch(stdscr);

        /*
         * Percorre as opção como uma lista infinita, se for muito para
         * cima volta para e baixo e vice-versa.
         */
        switch ( ch ) {
            case KEY_UP:
                /* Se a última opção era a primeira, seleciona a última */
                if ( opcao == 0 ) {
                    opcao = num_opcoes - 1;
                    mudanca = MUDANCA_CICLO_CIMA;
                /* Se não seleciona a que está acima */
                } else {
                    opcao--;
                    mudanca = MUDANCA_CIMA;
                }

                break;
            case KEY_DOWN:
                /* Se a última opção era a última, seleciona a primeira */
                if ( opcao == num_opcoes - 1 ) {
                    opcao = 0;
                    mudanca = MUDANCA_CICLO_BAIXO;
                /* Se não seleciona a que está abaixo */
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

    return opcao;
}

void exibe_opcoes(char **opcoes, int num_opcoes, int opcao_atual,
        int mudanca, struct grid_processado grid) {
    /* Calcula a linha em que a opção selecionada está */
    int y_atual = grid.y_inicial + (grid.y_delta * opcao_atual);
    /* 
     * Será usada para obter o valor X onde deverá começar a ser impresso
     * a mensagem
     */
    int x_atual;

    switch ( mudanca ) {
        case MUDANCA_INICIO:
            /* Exibe da segunda até a última opção */
            for ( int i = 1, y = (grid.y_inicial + grid.y_delta);
                    i < num_opcoes; i++, y += grid.y_delta ) {
                /* Calcula o ponto X onde deverá escreva e move o cursor */
                x_atual = grid.x_meio - (int)(strlen(opcoes[i]) / 2);
                move(y, x_atual);

                printw("%s", opcoes[i]);
            }
            break;
        /* Cada case vai para onde a opção anterior estava */
        case MUDANCA_CICLO_CIMA:
            /* Move para o primeiro item */
            x_atual = grid.x_meio - (int)(strlen(opcoes[0]) / 2);
            move(grid.y_inicial, x_atual);

            printw("%s", opcoes[0]);
            break;
        case MUDANCA_CICLO_BAIXO:
            /* Move para o último item */
            x_atual = grid.x_meio - 
                (int)(strlen(opcoes[num_opcoes - 1]) / 2);
            move(grid.y_final, x_atual);

            printw("%s", opcoes[num_opcoes - 1]);
            break;
        case MUDANCA_CIMA:
            /* Move para o item abaixo da opção */
            x_atual = grid.x_meio - 
                (int)(strlen(opcoes[opcao_atual + 1]) / 2);
            move(y_atual + grid.y_delta, x_atual);

            printw("%s", opcoes[opcao_atual + 1]);
            break;
        case MUDANCA_BAIXO:
            /* Move para o item acima da opção */
            x_atual = grid.x_meio - 
                (int)(strlen(opcoes[opcao_atual - 1]) / 2);
            move(y_atual - grid.y_delta, x_atual);

            printw("%s", opcoes[opcao_atual - 1]);
            break;
        case MUDANCA_NENHUMA:
        default:
            break;
    }

    x_atual = grid.x_meio - (int)(strlen(opcoes[opcao_atual]) / 2);
    /* Move o cursor a opção que está selecionada */
    move(y_atual, x_atual);
    /* Inicia a cor do highlight */
    attron(COLOR_PAIR(1));
    /* Exibe a opção com o highlight */
    printw("%s", opcoes[opcao_atual]);
    /* Volta a cor normal */
    attroff(COLOR_PAIR(1));

    /* Imprime as alterações na tela */
    refresh();
}

struct grid_processado processa_grid(
        struct tamanho_grid grid,int num_opcoes) {
    struct grid_processado grid_proc;

    /* Define a metade do eixo X do grid */
    grid_proc.x_meio = grid.x[GRID_COMECO] + 
        (int)((grid.x[GRID_FINAL] - grid.x[GRID_COMECO]) / 2);

    /* Tamanho total do eixo Y do grid */
    int y = grid.y[GRID_FINAL] - grid.y[GRID_COMECO];

    /* Define quantas linhas há entre um item e outro */
    float y_delta;
    y_delta = y - num_opcoes;
    y_delta = y_delta / (num_opcoes + 1);

    /* Define onde ficará a primeira opção */
    grid_proc.y_inicial = grid.y[GRID_COMECO] + (int)y_delta;

    /* 
     * Aumenta a variação para os próximos itens, o primeiro ficará
     * mais acima 
     */
    grid_proc.y_delta = (int)y_delta + 1;

    /* Se adiferença entre uma linha e outra não for exata, aumenta a 
     * distancia 
     */
    if ( y_delta != (int)y_delta ) {
        grid_proc.y_inicial++;
        grid_proc.y_delta++;
    }

    /* Define onde a última opção ficará */
    grid_proc.y_final = grid_proc.y_inicial +
        (grid_proc.y_delta * (num_opcoes - 1));

    /* Se a última ultrapassar o grid, devemos diminuir a distância */
    if ( grid_proc.y_final >= grid.y[GRID_FINAL] ) {
        grid_proc.y_inicial--;
        grid_proc.y_delta--;
        grid_proc.y_final = grid_proc.y_inicial + 
            (grid_proc.y_delta * (num_opcoes - 1));
    }

    /* Retorna o grid processado */
    return grid_proc;
}
