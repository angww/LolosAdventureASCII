#pragma once

#include "defines_lolo.h"
#include "dados.h"
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

#define NIVEIS { NIVEIS_PASTA "/nivel1.mapa",\
                NIVEIS_PASTA "/nivel2.mapa",\
                NIVEIS_PASTA "/nivel3.mapa",\
                NIVEIS_PASTA "/nivel4.mapa" }

#define NUM_NIVEIS 4

/* Carrega um mapa determinado por filename */
int carrega_arquivo_mapa(mapa_st *mapa, char *filename);
/*
 * Tenta fechar o arquivo dado por fp, filename e errsv é usado para exibir
 * possíveis erros
 */
int tenta_fechar(FILE *fp, char *filename, int errsv);
/*
 * Mesma funcionalidade do fread, só que ao invés de tratar um FILE *fp, recebe
 * o nome do arquivo
 */
int le_arquivo(void *ptr, size_t size, int nmemb, char *filename);
/*
 * Mesma funcionalidade do fwrite, só que ao invés de tratar um FILE *fp, recebe
 * o nome do arquivo
 */
int escreve_arquivo(void *ptr, size_t size, int nmemb, char *filename);
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
