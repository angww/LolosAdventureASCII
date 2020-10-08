#include "processa_mapas.h"

int exibe_informacoes(struct mapa *mp);

int main(int argc, char **argv) {
    if ( argc != 3 ) {
        printf("Uso:\n\t%s modo arquivo\n\n", argv[0]);
        printf("Onde:\n");
        printf("\tmodo pode ser (p)rocessa ou (c)arrega\n");
        printf("\tarquivo é o arquivo\n");
        return 1;
    }

    if ( strcmp(argv[1], "p") == 0 ) {
        FILE *nivel;
        nivel = fopen(argv[2], "r");

        fseek(nivel, 0L, SEEK_END);
        long tamanho = ftell(nivel);

        if ( tamanho != ( (JANELA_GRID_MAX_X + 1) * JANELA_GRID_MAX_Y ) ) {
            fclose(nivel);
            printf("Mapa inválido\n");
            return 2;
        }

        rewind(nivel);

        /* Cria a variável onde o grid será armazenado */
        char grid[JANELA_GRID_MAX_Y][JANELA_GRID_MAX_X];

        for ( int i = 0; i < JANELA_GRID_MAX_Y; i++ ){
            fread(grid[i], (sizeof (char)) * JANELA_GRID_MAX_X, 1, nivel);
            fseek(nivel, 1L, SEEK_CUR);
        }

        fclose(nivel);

        struct mapa mp;
        inicializa_mapa(&mp);
        processa_mapa(&mp, grid);

        char *filename;
        filename = calloc(strlen(argv[2]) + (strlen(EXTENSAO) * sizeof (char)), sizeof (char));
        strcat(filename, argv[2]);
        strcat(filename, EXTENSAO);

        printf("Salvando informações em: %s\n", filename);
        escreve_arquivo(filename, &mp);
        free(filename);

        exibe_informacoes(&mp);
        limpa_memoria(&mp);
    } else if ( strcmp(argv[1], "c") == 0 ) {
        struct mapa mp;

        inicializa_mapa(&mp);
        if ( carrega_arquivo(argv[2], &mp) != 0 ) {
            printf("Arquivo invalido.\n");
            return 4;
        }

        exibe_informacoes(&mp);
        limpa_memoria(&mp);
    } else {
        printf("Opcao invalida: %s.\n", argv[1]);
        return 3;
    }

    return 0;
}

int exibe_informacoes(struct mapa *mp) {
    printf("\n\nInformacoes do mapa:\n");
    printf("Grid estatico:\n");

    for ( int i = 0; i < JANELA_GRID_MAX_Y; i++ ) {
        for ( int j = 0; j < JANELA_GRID_MAX_X; j++ ) {
            putchar(mp->grid[i][j]);
        }
        putchar('\n');
    }

    printf("\nPosicao dos coracoes:\n");
    for ( int i = 0; i<mp->coracoes_num; i++ ) {
        printf("%d -> (Coracao(%d, %d), coletado: %d)\n", i,
                (mp->coracoes[i]).pos[0], (mp->coracoes[i]).pos[1],
                (mp->coracoes[i]).coletado);
    }

    printf("\nPosicao dos inimigos:\n");
    for ( int i = 0; i<mp->inimigos_num; i++ ) {
        printf("%d -> (Inimigo(%d, %d), vivo: %d)\n", i,
                (mp->inimigos[i]).pos[0], (mp->inimigos[i]).pos[1],
                (mp->inimigos[i]).vivo);
    }

    printf("\nPosicao dos blocos moveis:\n");
    for ( int i = 0; i<mp->blocos_moveis_num; i++ ) {
        printf("%d -> (Bloco_movel(%d, %d)\n", i,
                (mp->blocos_moveis[i]).pos[0], (mp->blocos_moveis[i]).pos[1]);
    }

    printf("\nPosicao do bau:\n");
    printf("(Bau(%d, %d), aberto: %d)\n",
            (mp->bau).pos[0], (mp->bau).pos[1], (mp->bau).aberto);

    printf("\nPosicao do lolo:\n");
    printf("(LoLo(%d, %d))\n", mp->lolo_pos_inicial[0], mp->lolo_pos_inicial[1]);

    return 0;
}
