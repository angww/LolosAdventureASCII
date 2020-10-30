#include "arquivos.h"

int verifica_arquivos(void)
{
    char *niveis[] = NIVEIS;
    int ret;

    /* Pasta necessária */
    ret = arquivo_existe(NIVEIS_PASTA);
    if ( ret ) {
        return 1;
    }

    /* Se não existe pode ser criada */
    ret = arquivo_existe(PASTA);
    if ( ret ) {
        ret = cria_pasta(PASTA);
        if ( ret ) {
            return 2;
        }
    }

    /* Verifica se os níveis estão presentes em niveis/ */
    for ( int i = 0; i < NUM_NIVEIS; i++ ) {
        if ( arquivo_existe(niveis[i]) ) {
            return 3;
        }
    }

    /* Verifica se arquivo de save existe */
    ret = arquivo_existe(PASTA "/" SAVE_FILE);
    if ( ret ) {
        ret = cria_arquivo(PASTA "/" SAVE_FILE);
        if ( ret ) {
            return 4;
        }
    }

    /* Verifica se arquivo de save existe */
    ret = arquivo_existe(PASTA "/" RECORDS_FILE);
    if ( ret ) {
        ret = cria_arquivo(PASTA "/" RECORDS_FILE);
        if ( ret ) {
            return 5;
        }
    }

    return ret;
}

int arquivo_existe(char *filename)
{
    int errsv = SUCCESS;
    int ret;

    ret = access(filename, F_OK);

    if ( ret != SUCCESS ) {
        errsv = errno;

        #ifdef DEBUG
            write_debug_messagef("Erro: %s: %s", strerror(errno), filename);
        #endif
    } else {
        #ifdef DEBUG
            write_debug_messagef("Arquivo %s existe", filename);
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

        #ifdef DEBUG
            write_debug_messagef("Erro: %s: %s", strerror(errno), filename);
        #endif
    } else {
        #ifdef DEBUG
            write_debug_messagef("Arquivo %s acessivel", filename);
        #endif
    }

    return errsv;
}

int cria_arquivo(char *filename)
{
    int errsv = SUCCESS;
    int fd;

    mode_t mode = PERMISSOES;

    #ifdef DEBUG
        write_debug_messagef("Criando arquivo %s", filename);
    #endif

    fd = open(filename, O_WRONLY | O_CREAT , mode);

    if ( fd == -1 ){
        errsv = errno;

        #ifdef DEBUG
            write_debug_messagef("Erro: %s: %s", strerror(errno), filename);
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

    #ifdef DEBUG
        write_debug_messagef("Criando pasta %s", filename);
    #endif

    /* Tenta criar a pasta */
    ret = mkdir(filename, PERMISSOES);

    /* Se houve erro, armazena o errno */
    if ( ret != 0 ) {
        errsv = errno;

        #ifdef DEBUG
            write_debug_messagef("Erro: %s: %s", strerror(errno), filename);
        #endif
    }

    return errsv;
}
