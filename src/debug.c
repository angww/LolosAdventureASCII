#include "defines_lolo.h"
#include "debug.h"

void write_debug_message(char *message) {
    /* Obtém o tempo atual */
    static time_t t;
    static struct tm *tmp;
    t = time(NULL);
    tmp = localtime(&t);
    /* Onde será armazenado o tempo formatado */
    static char timestrbuf[25];

    /* Abre o arquivo de debug sem sobreescrevê-lo */
    FILE *fp;
    fp = fopen(DEBUG_FILENAME, "a");

    /* Formata a string de tempo */
    strftime(timestrbuf, sizeof (timestrbuf), TIMESTR, tmp);
    /* Imprime a mensagem no arquivo de debug */
    fprintf(fp, "[%s] %s\n", timestrbuf, message);
    /* Fecha o arquivo de debug */
    fclose(fp);
}
