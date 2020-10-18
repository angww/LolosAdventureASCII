#pragma once

/*
 * Permite que DEBUG seja inicializado com qualquer valor na compilição
 * Exemplo:
 *      gcc -o main main.c -DDEBUG=1
 */
#ifndef DEBUG
#define DEBUG 0
#endif

/* Código da tecla ESC */
#define ESC 27

/* JANELAS */
#define JANELA_MAX_X 80
#define JANELA_MAX_Y 25
#define JANELA_MSEC_ANIMACAO 10

/* JANELA DO MAPA */
#define JANELA_JOGO_INICIO_X  1
#define JANELA_JOGO_TAMANHO_X 53
#define JANELA_JOGO_FINAL_X   JANELA_JOGO_INICIO_X + JANELA_JOGO_TAMANHO_X
#define JANELA_JOGO_INICIO_Y  1
#define JANELA_JOGO_FINAL_Y   JANELA_MAX_Y - 1
#define JANELA_JOGO_TAMANHO_Y JANELA_JOGO_FINAL_Y - JANELA_JOGO_INICIO_Y

/* Informações ao lado do mapa */
#define JANELA_INFO_INICIO_X  JANELA_JOGO_FINAL_X + 1
#define JANELA_INFO_TAMANHO_X 23
#define JANELA_INFO_FINAL_X   JANELA_INFO_INICIO_X + JANELA_INFO_TAMANHO_X
#define JANELA_INFO_INICIO_Y  1
#define JANELA_INFO_FINAL_Y   JANELA_MAX_Y - 1
#define JANELA_INFO_TAMANHO_Y JANELA_INFO_FINAL_Y - JANELA_INFO_INICIO_Y

/* STRINGS */
#define STR_TITULO              "LoLo's Adventure - ASCII"

/* GAME */
#define LOLO        '@'
#define BLOCO_FIXO  'P'
#define BLOCO_MOVEL 'M'
#define INIMIGO     'E'
#define CORACAO     'C'
#define BAU         'B'
#define AGUA        'A'
#define LIVRE       ' '

struct bloco_movel {
    int pos[2];
};

struct inimigos {
    int pos[2];
    int vivo;
};

struct coracoes {
    int pos[2];
    int coletado;
};

struct bau {
    int pos[2];
    int aberto;
};

/* Informações do mapa */
struct mapa {
    char grid[21][53];
    int lolo_pos_inicial[2];
    struct bau bau;
    int blocos_moveis_num;
    struct bloco_movel *blocos_moveis;
    int inimigos_num;
    struct inimigos *inimigos;
    int coracoes_num;
    struct coracoes *coracoes;
};
