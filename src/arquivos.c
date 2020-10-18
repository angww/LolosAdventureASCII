#include "arquivos.h"

int existe_pasta(char *filename)
{
    /* Tenta abrir a pasta */
    DIR *dir;
    dir = opendir(filename);

    int errsv = SUCCESS;

    /* errsv = errno apenas se houve erro, errno pode conter valor antigo */
    if ( dir == NULL ) {
        errsv = errno;
    } else {
        closedir(dir);
    }

    return errsv;
}

int cria_pasta(char *filename)
{
    int errsv = SUCCESS;
    int ret;

    /* Tenta criar a pasta */
    ret = mkdir(filename, PERMISSOES);

    /* Se houve erro, armazena o errno */
    if ( ret != 0 ) {
        errsv = errno;
    }

    return errsv;
}

int tenta_abrir_ou_criar_pasta(char *filename)
{
    #ifdef DEBUG
        write_debug_messagef("Tentanto abrir pasta %s", filename);
    #endif

    /* Verifica se a pasta existe */
    int ret = existe_pasta(filename);

    /* Verifica o retorno, se a pasta não existe, tenta criá-la */
    switch ( ret ) {
        case SUCCESS:
            #ifdef DEBUG
                write_debug_messagef("A pasta %s existe.", filename);
            #endif

            break;
        case ENOENT:
            #ifdef DEBUG
                write_debug_messagef("Tentando criar a pasta %s", filename);
            #endif

            /* Tenta criar a pasta */
            ret = cria_pasta(filename);

            /* Verifica o retorno */
            switch ( ret ) {
                case SUCCESS:
                    #ifdef DEBUG
                        write_debug_messagef("A pasta %s foi criada.", filename);
                    #endif

                    break;
                default:
                    #ifdef DEBUG
                        write_debug_messagef("Erro: %s: %s", strerror(ret),
                            filename);
                    #endif

                    fprintf(stderr, "Erro: %s: %s\n", strerror(ret), filename);
                    break;
                break;
            }

            break;
        default:
            #ifdef DEBUG
                write_debug_messagef("Erro: %s: %s", strerror(ret), filename);
            #endif

            fprintf(stderr, "Erro: %s: %s\n", strerror(ret), filename);
            break;
    }

    return ret;
}
