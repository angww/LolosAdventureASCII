#pragma once

#include <stdio.h>
#include <time.h>

/* Definido apenas se DEBUG estiver ativo */
#define DEBUG_FILENAME "log"
#define TIMESTR "%F %T"
#define DEBUG_MESSAGE_SIZE 80

void write_debug_message(char *message);
