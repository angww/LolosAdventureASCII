#pragma once

#include <ncurses.h>
#include <string.h>

/* Indica se houve mudança ou não */
#define MUDANCA_NENHUMA 0
#define MUDANCA_OPCAO   1

/*
 * Retorna a opção selecionada ou KEY_RESIZED, caso modo=0, opcoes será tratado
 * como um array de strings, caso modo > 0 então opcoes é tratado como uma
 * sequencia de strings de modo caracteres, modo < 0 retorna -1
 */
int seleciona_opcoes(char **opcoes, int num_opcoes, int y_inicio, int y_delta,
    int x_meio, int modo);

/* Retorna apenas uma opção */
int seleciona_opcao(char *opcao, int y_pos, int x_meio);

/* Exibe todos os itens sem highlight */
void exibe_itens(char *opcoes[], int num_opcoes, int y_inicio, int y_delta,
    int x_meio);

/* Exibe apenas um item sem highlight */
void exibe_item(char *opcao, int num, int y_inicio, int y_delta, int x_meio);

/* Exibe apenas um item com highlight */
void exibe_opcao(char *opcao, int opcao_num, int y_inicio, int y_delta,
    int x_meio);

/* Exibe uma opção em dada posição */
void exibe_opcao_pos(char *opcao, int y_pos, int x_meio);
