#pragma once

#include <stdio.h>
#include <time.h>

/* Definido apenas se DEBUG estiver ativo */

/* Arquivo que será salvo toda mensagem de debug */
#define DEBUG_FILENAME "log"
/* Formato do tempo */
#define TIMESTR "%F %T"
/* Tamanho máximo da mensagem (não da linha) */
#define DEBUG_MESSAGE_SIZE 80

/* Escreve message no arquivo de debug */
void write_debug_message(char *message);
