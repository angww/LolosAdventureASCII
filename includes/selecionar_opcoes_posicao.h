#pragma once

#include <ncurses.h>
#include <string.h>

#define MUDANCA_NENHUMA     0
#define MUDANCA_INICIO      1
#define MUDANCA_BAIXO       2
#define MUDANCA_CIMA        3
#define MUDANCA_CICLO_BAIXO 4
#define MUDANCA_CICLO_CIMA  5

#define GRID_COMECO 0
#define GRID_FINAL  1

/* Informação enviada ao seleciona_opcao */
struct tamanho_grid {
    /* Ponto onde começa e termina o eixo x do grid */
    int x[2];
    /* Ponto onde começa e termina o eixo y do grid */
    int y[2];
};

/* Informação enviada para exibe_opcoes */
struct grid_processado {
    /* Tamanho da linha */
    int x_meio;
    /* Linha em que se deve começar a exibir */
    int y_inicial;
    /* Distância entre as linhas */
    int y_delta;
    /* Última posição de y */
    int y_final;
};

struct grid_processado processa_grid(struct tamanho_grid grid, int num_opcoes);
int seleciona_opcao(char **opcoes, int num_opcoes, struct tamanho_grid grid);
void exibe_opcoes(char **opcoes, int num_opcoes, int opcao_atual, int mudanca, struct grid_processado grid);
