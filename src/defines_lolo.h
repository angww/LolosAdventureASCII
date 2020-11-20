#pragma once

#include <time.h>

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

/* Janela do Jogo */
#define JOGO_JANELA_X 55
#define JOGO_JANELA_Y 23

/* Janela da inforção do Jogo */
#define JOGO_INFO_X 22
#define JOGO_INFO_Y 23

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

/* Informações a serem salvas e mantidas/modificadas entre níveis */
typedef struct {
    int identificador;
    int totalpts;
    int ultimafase;
    int vidas;
    char nome_jogador[9];
    time_t inicio;
    time_t final;
} gravacao_st;

/* Entrada de recorde */
typedef struct {
    char nome_jogador[9];
    int totalpts;
    time_t tempo_total;
} recorde_st;

/* Ponto x,y */
typedef struct {
    char x;
    char y;
} ponto_st;

/* Informações sobre o estado atual do lolo */
typedef struct {
    int vidas;
    ponto_st pos;
    int pontos;
} lolo_st;

/* Posição do inimigo */
typedef struct {
    ponto_st pos;
} inimigo_st;

/* Informações do mapa */
typedef struct {
    char elementos[JOGO_JANELA_Y][JOGO_JANELA_X];
    ponto_st lolo;
    ponto_st bau;
    int coracoes_num;
    int inimigos_num;
    inimigo_st **inimigos;
} mapa_st;
