#pragma once

#include <stdio.h>
/* Alocação de memória dinâmica (malloc e free) */
#include <stdlib.h>
/* Na mensagem será exibido quando write_debug_message foi chamado */
#include <time.h>
/* Define ..., possibilitando um número arbitrário de argumentos */
#include <stdarg.h>

/* Arquivo que será salvo toda mensagem de debug */
#define DEBUG_FILENAME "log_lolo.log"
/* Formato do tempo */
#define TIMESTR "%F %T"

/* Escreve message no arquivo de debug */
void write_debug_message(char *message);
/* Escreve a mensagem formata no arquivo de debug */
void write_debug_messagef(char *fmessage, ...);
