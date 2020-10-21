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

/* GAME */
#define LOLO        '@'
#define BLOCO_FIXO  'P'
#define BLOCO_MOVEL 'M'
#define INIMIGO     'E'
#define CORACAO     'C'
#define BAU         'B'
#define AGUA        'A'
#define LIVRE       ' '

struct save_game {
    int totalpts;
    int fase;
    int vidas;
    char nome_jogador[9];
};

struct posicao {
    int x;
    int y;
};

struct bloco_movel {
    struct posicao pos;
};

struct inimigos {
    struct posicao pos;
    int vivo;
};

struct coracoes {
    struct posicao pos;
    int coletado;
};

struct bau {
    struct posicao pos;
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
