#pragma once

#include <stdio.h>
#include <errno.h>     /* Códigos de erro */
#include <string.h>    /* strerror */
#include <unistd.h>    /* Acesso a recursos específicos do Unix */
#include <dirent.h>    /* opendir */
#include <sys/types.h> /* opendir precisa do tipo DIR */
#include <sys/stat.h>  /* mkdir */

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
* Permite a leitura, escrita e execução para usuário e grupo, para outros
* permite a leitura e a execução
*/
#define PERMISSOES S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH

/*
 * Verifica a existência de uma pasta, retorna 0 caso exista, se não retorna um
 * código de erro
 */
int existe_pasta(char *filename);
/* Cria uma pasta, retorna 0 caso consiga, se não retorna um código de erro */
int cria_pasta(char *filename);
/*
 * Função que verifica a existência de uma pasta, caso não exista tenta criá-la,
 * caso consiga retorna 0, se não retorna um código de erro e imprime em stderr
 * uma mensagem
 */
int tenta_abrir_ou_criar_pasta(char *filename);

/* Abaixo há uma lista de erros que são esperados e notificados */

/*
 * Para a função cria_pasta espera-se:
 *
 * EROFS -> read-only file system
 * ENOSPC -> sem espaço
 * EEXIST -> ja existe
 * EACCES -> nao pode escrever
 */

/*
 * Para a função existe_pasta espera-se:
 *
 * EACCES -> sem permissao de acesso
 * ENOENT -> Nao existe
 * ENOTDIR -> Nao é uma pasta
 */

/*
 * Outros valores que podem ser atribuídos a errno(para ver todos veja o manual
 * 3 errno):
 *
 * ENOTDIR       -> Not a directory
 * EACCES        -> Permission Denied
 * EEXIST        -> File Exists
 * EISDIR        -> Is a directory
 * ENOENT        -> No such file or directory
 * ENOTEMPTY     -> Directory not empty
 * EPERM         -> Operation not permitted
 * EROFS         -> Read-only filesystem
 * ETXTBUSY      -> Text file busy
 * ENAMETOOLONG  -> Filename too long
 * EIO           -> Input/output error
 * EFBIG         -> File too big
 * EBUSY         -> Device on resource busy
 * EADDRINUSE    -> Address already in use
 * EADDRNOTAVAIL -> Address not avaible
*/
