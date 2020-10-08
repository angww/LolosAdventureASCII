#include "../includes/processa_mapas.h"

int processa_mapa(struct mapa *mp, char grid[21][53]) {
    for ( int linha = 0; linha < JANELA_GRID_MAX_Y; linha++ ) {
        for ( int coluna = 0; coluna < JANELA_GRID_MAX_X; coluna++ ) {
            switch ( grid[linha][coluna] ) {
                case INIMIGO:
                    adiciona_inimigo(mp, linha, coluna);
                    mp->grid[linha][coluna] = LIVRE;
                    break;
                case LOLO:
                    mp->lolo_pos_inicial[0] = linha;
                    mp->lolo_pos_inicial[1] = coluna;
                    mp->grid[linha][coluna] = LIVRE;
                    break;
                case CORACAO:
                    adiciona_coracao(mp, linha, coluna);
                    mp->grid[linha][coluna] = LIVRE;
                    break;
                case BAU:
                    adiciona_bau(mp, linha, coluna);
                    mp->grid[linha][coluna] = LIVRE;
                    break;
                case BLOCO_MOVEL:
                    adiciona_bloco_movel(mp, linha, coluna);
                    mp->grid[linha][coluna] = LIVRE;
                    break;
                default:
                    mp->grid[linha][coluna] = grid[linha][coluna];
                    break;
            }
        }
    }

    return 0;
}

int inicializa_mapa(struct mapa *mp) {
    mp->inimigos = NULL;
    mp->coracoes = NULL;
    mp->blocos_moveis = NULL;
    mp->inimigos_num = 0;
    mp->coracoes_num = 0;
    mp->blocos_moveis_num = 0;

    return 0;
}

int carrega_arquivo(char *filename, struct mapa *mp) {
    FILE *arquivo;
    arquivo = fopen(filename, "rb");

    char verificador[strlen(VERIFICADOR) + 1];
    fread(verificador, sizeof (char), strlen(VERIFICADOR), arquivo);
    verificador[strlen(VERIFICADOR)] = '\0';

    if ( strcmp(verificador, VERIFICADOR) != 0 ) {
        return 1;
    }

    fread(mp->grid, sizeof (char) * JANELA_GRID_MAX_Y * JANELA_GRID_MAX_X, 1, arquivo);
    
    fread(mp->lolo_pos_inicial, sizeof (int), 2, arquivo);
    fread(&(mp->bau), sizeof(struct bau), 1, arquivo);

    fread(&(mp->blocos_moveis_num), sizeof (int), 1, arquivo);
    mp->blocos_moveis = calloc(mp->blocos_moveis_num, sizeof (struct bloco_movel));
    fread(mp->blocos_moveis, sizeof (struct bloco_movel), mp->blocos_moveis_num, arquivo);

    fread(&(mp->inimigos_num), sizeof (int), 1, arquivo);
    mp->inimigos = calloc(mp->inimigos_num, sizeof (struct inimigos));
    fread(mp->inimigos, sizeof (struct inimigos), mp->inimigos_num, arquivo);

    fread(&(mp->coracoes_num), sizeof (int), 1, arquivo);
    mp->coracoes = calloc(mp->coracoes_num, sizeof (struct coracoes));
    fread(mp->coracoes, sizeof (struct coracoes), mp->coracoes_num, arquivo);

    fclose(arquivo);
    return 0;
}

int escreve_arquivo(char *filename, struct mapa *mp) {
    FILE *arquivo;
    arquivo = fopen(filename, "wb");

    fwrite(VERIFICADOR, sizeof (char), 10, arquivo);

    fwrite(mp->grid, sizeof (char) * JANELA_GRID_MAX_Y * JANELA_GRID_MAX_X, 1, arquivo);
    fwrite(mp->lolo_pos_inicial, sizeof (int), 2, arquivo);
    fwrite(&(mp->bau), sizeof(struct bau), 1, arquivo);
    fwrite(&(mp->blocos_moveis_num), sizeof (int), 1, arquivo);
    fwrite(mp->blocos_moveis, sizeof (struct bloco_movel), mp->blocos_moveis_num, arquivo);
    fwrite(&(mp->inimigos_num), sizeof (int), 1, arquivo);
    fwrite(mp->inimigos, sizeof (struct inimigos), mp->inimigos_num, arquivo);
    fwrite(&(mp->coracoes_num), sizeof (int), 1, arquivo);
    fwrite(mp->coracoes, sizeof (struct coracoes), mp->coracoes_num, arquivo);
    fclose(arquivo);

    return 0;
}

int limpa_memoria(struct mapa *mp) {
    free(mp->blocos_moveis);
    free(mp->inimigos);
    free(mp->coracoes);
    return 0;
}

int adiciona_coracao(struct mapa *mp, int linha, int coluna) {
    struct coracoes *c = malloc( sizeof (struct coracoes));
    struct coracoes *coracoes = realloc(mp->coracoes, (sizeof (struct coracoes)) * (mp->coracoes_num + 1));

    c->pos[0] = linha;
    c->pos[1] = coluna;
    c->coletado = 0;
    mp->coracoes = coracoes;
    (mp->coracoes)[mp->coracoes_num] = *c;
    mp->coracoes_num++;

    return 0;
}

int adiciona_bau(struct mapa *mp, int linha, int coluna) {
    struct bau b;
    b.pos[0] = linha;
    b.pos[1] = coluna;
    b.aberto = 0;
    mp->bau = b;
    return 0;
}

int adiciona_inimigo(struct mapa *mp, int linha, int coluna) {
    struct inimigos *i = malloc( sizeof (struct inimigos));
    struct inimigos *inimigos = realloc(mp->inimigos, (sizeof (struct inimigos)) * (mp->inimigos_num + 1));

    i->pos[0] = linha;
    i->pos[1] = coluna;
    i->vivo = 0;
    mp->inimigos = inimigos;
    (mp->inimigos)[mp->inimigos_num] = *i;
    mp->inimigos_num++;

    return 0;
}

int adiciona_bloco_movel(struct mapa *mp, int linha, int coluna) {
    struct bloco_movel *b = malloc( sizeof (struct bloco_movel));
    struct bloco_movel *blocos_moveis = realloc(mp->blocos_moveis, (sizeof (struct bloco_movel)) * (mp->blocos_moveis_num + 1));

    b->pos[0] = linha;
    b->pos[1] = coluna;
    mp->blocos_moveis = blocos_moveis;
    (mp->blocos_moveis)[mp->blocos_moveis_num] = *b;
    mp->blocos_moveis_num++;

    return 0;
}
