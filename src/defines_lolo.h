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
#define BAU         'T'
#define AGUA        'A'
#define LIVRE       ' '

struct gravacao {
    int identificador;
    int totalpts;
    int ultimafase;
    int vidas;
    char nome_jogador[9];
    int tempo_total_segundos;
    int tempo_fase_segundos;
};

struct ponto {
    char x;
    char y;
};

struct inimigos {
    struct ponto pos;
};

/* Informações do mapa */
struct mapa {
    char elementos[21][53];         /* Mapa estático */
    struct ponto lolo;       /* Onde posicionar Lolo */
    struct ponto bau;        /* Mudar a cor do baú quando for aberto */
    int inimigos_num;          /* Controla o loop de movimentação */
    struct inimigos *inimigos; /* Inimigos serão alocados dinamicamente */
};
