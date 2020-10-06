#pragma once

#include <ncurses.h>
#include <stdio.h>

#define MUDANCA_NENHUMA     0
#define MUDANCA_INICIO      1
#define MUDANCA_BAIXO       2
#define MUDANCA_CIMA        3
#define MUDANCA_CICLO_BAIXO 4
#define MUDANCA_CICLO_CIMA  5

int seleciona_opcao(char **opcoes, int num_opcoes);
void exibe_opcoes(char **opcoes, int num_opcoes, int opcao_atual, int mudanca);
