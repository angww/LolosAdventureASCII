#include "arquivos.h"

int carrega_arquivo_mapa(mapa_st *mapa, char *filename)
{
    #if DEBUG
        debug_message("Carregando nivel \"%s\"", filename);
    #endif

    int ret = 0;
    FILE *fp = fopen(filename, "r");

    if ( fp == NULL ) {
        #if DEBUG
            debug_message("Erro ao carregar o nivel \"%s\": %s", filename,
                strerror(errno));
        #endif

        return 1;
    }

    for ( int linha = 0; linha < JOGO_JANELA_Y; linha++ ){
        ret = fread(mapa->elementos[linha], sizeof (char), JOGO_JANELA_X, fp);

        if ( ret != JOGO_JANELA_X ) {
            #if DEBUG
                debug_message("Erro ao ler arquivo de nivel \"%s\"", filename);
            #endif

            break;
        }

        /* Pula o '\n' do arquivo */
        fgetc(fp);
    }

    if ( fclose(fp) != 0 ) {
        #if DEBUG
            debug_message("Erro ao fechar o arquivo %s: %s", filename,
                strerror(errno));
        #endif

        return 2;
    } else if ( ret != JOGO_JANELA_X ) {
        return 3;
    }

    mapa->inimigos = NULL;
    mapa->inimigos_num = 0;
    mapa->coracoes_num = 0;

    return processa_mapa(mapa);
}

int verifica_arquivos(void)
{
    char *niveis[] = NIVEIS;
    int ret;

    /* Pasta necessária */
    ret = arquivo_existe(NIVEIS_PASTA);
    if ( ret ) {
        return 1;
    }

    /* Verifica se os níveis estão presentes em niveis/ */
    for ( int i = 0; i < NUM_NIVEIS; i++ ) {
        if ( arquivo_existe(niveis[i]) ) {
            return 3;
        }
    }

    /* Se não existe pode ser criada */
    ret = arquivo_existe(PASTA);
    if ( ret ) {
        ret = cria_pasta(PASTA);
        if ( ret ) {
            return 2;
        }
    }

    /* Verifica se arquivo de save existe */
    ret = arquivo_existe(PASTA "/" SAVE_FILE);
    if ( ret ) {
        ret = cria_arquivo(PASTA "/" SAVE_FILE);
        if ( ret ) {
            return 4;
        }

        gravacao_st tmp_gravacao[5];
        for ( int i = 0; i < 5; i++ ) {
            limpa_save(&tmp_gravacao[i]);
        }

        ret = escreve_arquivo(tmp_gravacao, sizeof (gravacao_st), 5, PASTA "/" SAVE_FILE);
        if ( ret ) {
            return 5;
        }
    }

    /* Verifica se arquivo de save existe */
    ret = arquivo_existe(PASTA "/" RECORDS_FILE);
    if ( ret ) {
        ret = cria_arquivo(PASTA "/" RECORDS_FILE);
        if ( ret ) {
            return 6;
        }

        recorde_st tmp_recorde[5];
        grava_inicial_fake_record(tmp_recorde);

        ret = escreve_arquivo(tmp_recorde, sizeof (recorde_st), 5, PASTA "/" RECORDS_FILE);
        if ( ret ) {
            return 7;
        }

    }

    return ret;
}

int le_arquivo(void *ptr, size_t size, int nmemb, char *filename)
{
    int errsv = SUCCESS;
    FILE *fp;

    fp = fopen(filename, "rb");
    if ( fp == NULL ) {
        errsv = errno;

        #if DEBUG
            debug_message("Erro: %s: %s", strerror(errno), filename);
        #endif

        return errsv;
    }

    if ( fread(ptr, size, nmemb, fp) != nmemb ) {
        errsv = errno;

        #if DEBUG
            /* Erro na leitura ou não leu tudo */
            if ( errsv != SUCCESS ) {
                debug_message("Erro: %s: %s", strerror(errno), filename);
            } else {
                debug_message("Erro: Nao foi possivel ler todo arquivo: %s", filename);
            }
        #endif

        /*
         * Se foi possível ler, pelo menos uma parte do arquivo, errsv não é
         * modificado, -1 é um código inexistente, Unknown Error
         */
        if ( errsv == SUCCESS) {
            errsv = -1;
        }

        return tenta_fechar(fp, filename, errsv);
    }

    return tenta_fechar(fp, filename, errsv);
}

int le_arquivo_pos(void *ptr, size_t size, char *filename, int pos)
{
    int errsv = SUCCESS;
    FILE *fp;

    fp = fopen(filename, "rb");
    if ( fp == NULL ) {
        errsv = errno;

        #if DEBUG
            debug_message("Erro: %s: %s", strerror(errno), filename);
        #endif

        return errsv;
    }

    fseek(fp, size * pos, SEEK_SET);

    if ( fread(ptr, size, 1, fp) != 1 ) {
        errsv = errno;

        #if DEBUG
            /* Erro na leitura ou não leu tudo */
            if ( errsv != SUCCESS ) {
                debug_message("Erro: %s: %s", strerror(errno), filename);
            } else {
                debug_message("Erro: Nao foi possivel ler arquivo: %s", filename);
            }
        #endif

        /*
         * Se foi possível ler, pelo menos uma parte do arquivo, errsv não é
         * modificado, -1 é um código inexistente, Unknown Error
         */
        if ( errsv == SUCCESS) {
            errsv = -1;
        }

        return tenta_fechar(fp, filename, errsv);
    }

    return tenta_fechar(fp, filename, errsv);
}

int escreve_arquivo_pos(void *ptr, size_t size, char *filename, int pos)
{
    int errsv = SUCCESS;
    FILE *fp;

    fp = fopen(filename, "rb+");
    if ( fp == NULL ) {
        errsv = errno;

        #if DEBUG
            debug_message("Erro: %s: %s", strerror(errno), filename);
        #endif

        return errsv;
    }

    fseek(fp, size * pos, SEEK_SET);

    if ( fwrite(ptr, size, 1, fp) != 1 ) {
        errsv = errno;

        #if DEBUG
            /* Erro ao escrever */
            if ( errsv != SUCCESS ) {
                debug_message("Erro: %s: %s", strerror(errno), filename);
            } else {
                debug_message("Erro: Nao foi possivel escrever no arquivo: %s", filename);
            }
        #endif

        /*
         * Se foi possível ler, pelo menos uma parte do arquivo, errsv não é
         * modificado, -1 é um código inexistente, Unknown Error
         */
        if ( errsv == SUCCESS) {
            errsv = -1;
        }

        return tenta_fechar(fp, filename, errsv);
    }

    return tenta_fechar(fp, filename, errsv);
}

int escreve_arquivo(void *ptr, size_t size, int nmemb, char *filename)
{
    int errsv = SUCCESS;
    FILE *fp;

    fp = fopen(filename, "wb");
    if ( fp == NULL ) {
        errsv = errno;

        #if DEBUG
            debug_message("Erro: %s: %s", strerror(errno), filename);
        #endif

        return errsv;
    }

    if ( fwrite(ptr, size, nmemb, fp) != nmemb ) {
        errsv = errno;

        #if DEBUG
            /* Erro na leitura ou não leu tudo */
            if ( errsv != SUCCESS ) {
                debug_message("Erro: %s: %s", strerror(errno), filename);
            } else {
                debug_message("Erro: Nao foi possivel escrever todo arquivo: %s", filename);
            }
        #endif

        /*
         * Se foi possível escrever, pelo menos uma parte do arquivo, errsv não é
         * modificado, -1 é um código inexistente, Unknown Error
         */
        if ( errsv == SUCCESS) {
            errsv = -1;
        }

        return tenta_fechar(fp, filename, errsv);
    }

    return tenta_fechar(fp, filename, errsv);
}

int tenta_fechar(FILE *fp, char *filename, int errsv)
{
    if ( errsv ) {
        #if DEBUG
            debug_message("Erro: %s: %s", strerror(errsv), filename);
        #endif
    }

    if ( fclose(fp) != 0 ) {
        errsv = errno;
        #if DEBUG
            debug_message("Erro: %s: %s", strerror(errsv), filename);
        #endif
    }

    return errsv;
}

int arquivo_existe(char *filename)
{
    int errsv = SUCCESS;
    int ret;

    ret = access(filename, F_OK);

    if ( ret != SUCCESS ) {
        errsv = errno;

        #if DEBUG
            debug_message("Erro: %s: %s", strerror(errno), filename);
        #endif
    } else {
        #if DEBUG
            debug_message("Arquivo %s existe", filename);
        #endif
    }

    return errsv;
}

int arquivo_acessivel(char *filename)
{
    int errsv = SUCCESS;
    int ret;

    ret = access(filename, R_OK | W_OK);

    if ( ret != SUCCESS ) {
        errsv = errno;

        #if DEBUG
            debug_message("Erro: %s: %s", strerror(errno), filename);
        #endif
    } else {
        #if DEBUG
            debug_message("Arquivo %s acessivel", filename);
        #endif
    }

    return errsv;
}

int cria_arquivo(char *filename)
{
    int errsv = SUCCESS;
    int fd;

    mode_t mode = PERMISSOES;

    #if DEBUG
        debug_message("Criando arquivo %s", filename);
    #endif

    fd = open(filename, O_WRONLY | O_CREAT , mode);

    if ( fd == -1 ){
        errsv = errno;

        #if DEBUG
            debug_message("Erro: %s: %s", strerror(errno), filename);
        #endif
    } else {
        close(fd);
    }

    return errsv;
}

int cria_pasta(char *filename)
{
    int errsv = SUCCESS;
    int ret;

    #if DEBUG
        debug_message("Criando pasta %s", filename);
    #endif

    /* Tenta criar a pasta */
    ret = mkdir(filename, PERMISSOES);

    /* Se houve erro, armazena o errno */
    if ( ret != 0 ) {
        errsv = errno;

        #if DEBUG
            debug_message("Erro: %s: %s", strerror(errno), filename);
        #endif
    }

    return errsv;
}
