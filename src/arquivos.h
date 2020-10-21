#pragma once

#include <stdio.h>
#include <errno.h>     /* Códigos de erro */
#include <string.h>    /* strerror */
#include <unistd.h>    /* Acesso a recursos específicos do Unix */
#include <dirent.h>    /* opendir */
#include <sys/types.h> /* opendir precisa do tipo DIR */
#include <sys/stat.h>  /* mkdir */
#include <fcntl.h>     /* open e O_RDONLY */

#ifdef DEBUG
#include "debug.h"
#endif

/* Pastas e arquivos a serem usados */
#define PASTA        "lolosgame"
#define NIVEIS_PASTA "niveis"
#define SAVE_FILE    "saves.lolo"
#define RECORDS_FILE "records.lolo"

#define SUCCESS 0

/*
 * Permite a leitura e escrita para usuário, para grupo e outros permite a
 * leitura
 */
#define PERMISSOES S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

/* Verifica se determinado arquivo ou pasta existe */
int arquivo_existe(char *filename);
/* Verifica se podemos ler e escrever o arquivo */
int arquivo_acessivel(char *filename);
/* Cria um arqivo arquivo */
int cria_arquivo(char *filename);
/* Cria uma pasta, retorna 0 caso consiga, se não retorna um código de erro */
int cria_pasta(char *filename);
/* Função que checa se os arquivos necessários para rodar existem */
int verifica_arquivos(void);
