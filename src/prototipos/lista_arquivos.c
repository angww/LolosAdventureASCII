#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

/*
 * Salva em filenames os arquivos que terminam com .mapa, o número de arquivos
 * é salvo em num_mapa_files, path não seŕa um argumento na implementação
 */
int lista_mapas_disponiveis(char ***filenames, int *num_mapa_files, char *path);

/* Dada um ponteiro de lista de strings, adiciona uma string no final */
int insere_mapa_lista(char ***filenames, char *filename, int num_mapa_files);

int main(int argc, char **argv)
{
    if ( argc != 2 ) { printf("Informe uma pasta.\n"); return 1; }

    char **ptr;
    int *mapas;

    lista_mapas_disponiveis(&ptr, mapas, argv[1]);

    printf("Arquivos que terminam com \".mapa\": \n");

    for ( int i  = 0; i < *mapas; i++ ) {
        printf("%s\n", ptr[i]);
        /* Limpa a memória que foi alocada */
        free(ptr[i]);
    }

    /* Limpa a memória que foi alocada */
    free(ptr);

    return 0;
}

int insere_mapa_lista(char ***filenames, char *filename, int num_mapa_files)
{
    /* Realoca o ponteiro */
    *filenames = realloc(*filenames, sizeof (char *) * num_mapa_files);

    if ( *filenames == NULL ) {
        return errno;
    }

    /* Aloca o espaço para armazenar o nome do arquivo */
    char *file = malloc(sizeof (char) * strlen(filename) + 1);

    if ( filename == NULL ) {
        return errno;
    }

    /* Copia o nome do arquivo para file e coloca na lista */
    strcpy(file, filename);
    (*filenames)[num_mapa_files-1] = file;

    return 0;
}

int lista_mapas_disponiveis(char ***filenames, int *num_mapa_files, char *path)
{
    struct dirent **dir_list;
    *filenames = malloc(sizeof (char *));
    *num_mapa_files = 0;

    char *filename;
    int num_arquivos;
    int ret;
    DIR *dp;
    struct dirent *tmp;

    dp = opendir(path);

    while ( (tmp = readdir(dp)) != NULL ) {
        /* Nome do arquivo */
        filename = tmp->d_name;

        /* Se o final da string for ".mapa", é um arquivo de mapa */
        if ( !strcmp(&filename[strlen(filename) - 5], ".mapa") ) {
            ret = insere_mapa_lista(filenames, filename, ++(*num_mapa_files));

            if ( ret != 0 ) {
              return ret;
            }
        }
    }

    closedir(dp);

    return 0;
}
