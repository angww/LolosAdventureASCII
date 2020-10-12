#pragma once

#include <ncurses.h>
#include <string.h>

/* Indica se houve mudança ou não */
#define MUDANCA_NENHUMA 0
#define MUDANCA_OPCAO   1

/* Retorna a opção selecionada ou KEY_RESIZED */
int seleciona_opcao(char **opcoes, int num_opcoes, int y_inicio, int y_delta,
    int x_meio);

/* Exibe todos os itens sem highlight */
void exibe_itens(char **opcoes, int num_opcoes, int y_inicio, int y_delta, int x_meio);

/* Exibe apenas um item sem highlight */
void exibe_item(char *opcao, int num, int y_inicio, int y_delta, int x_meio);

/* Exibe apenas um item com highlight */
void exibe_opcao(char *opcao, int opcao_num, int y_inicio, int y_delta, int x_meio);
