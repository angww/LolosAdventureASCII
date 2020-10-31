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
#define LOLO        '@' /* 01000000 */
#define BLOCO_FIXO  'P' /* 01010000 */
#define BLOCO_MOVEL 'M' /* 01001101 */
#define INIMIGO     'E' /* 01000101 */
#define CORACAO     'C' /* 01000011 */
#define BAU         'T' /* 01010100 */
#define AGUA        'A' /* 01000001 */
#define LIVRE       ' ' /* 00100000 */
#define MASCARA_INIMIGO  0b00011111

typedef struct {
    int identificador;
    int totalpts;
    int ultimafase;
    int vidas;
    char nome_jogador[9];
    int tempo_total_segundos;
    int tempo_fase_segundos;
} gravacao_st;

typedef struct {
    char nome_jogador[9];
    int totalpts;
    int tempo_total_segundos;
} recorde_st;

typedef struct {
    char x;
    char y;
} ponto_st;

typedef struct {
    int vidas;
    ponto_st pos;
} lolo_st;

typedef struct {
    ponto_st pos;
} inimigo_st;

/* Informações do mapa */
typedef struct {
    char elementos[21][53];         /* Mapa estático */
    ponto_st lolo;       /* Onde posicionar Lolo */
    ponto_st bau;        /* Mudar a cor do baú quando for aberto */
    int inimigos_num;          /* Controla o loop de movimentação */
    inimigo_st *inimigos; /* Inimigos serão alocados dinamicamente */
} mapa_st;
