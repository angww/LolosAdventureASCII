#pragma once

/* FOR DEV */
#define DEBUG  1
#define DEBUG_FILENAME "log"

/* JANELAS */ 
#define JANELA_MAX_X 80
#define JANELA_MAX_Y 25
#define JANELA_MSEC_ANIMACAO 10

/* JANELA DO MAPA */
#define JANELA_GRID_MAX_X 53
#define JANELA_GRID_MAX_Y 21

/* STRINGS */ 
#define STR_TITULO              "LoLo's Adventure - ASCII"
#define STR_MENU_PRINCIPAL      "Menu Principal"
#define STR_MENU_VOLTAR         "Voltar para o menu"

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
