#include "defines_lolo.h"
#include "debug.h"

void debug_message(char *fmessage, ...)
{
    /* string que será armazenado o tempo formatado */
    static char timestrbuf[25];

    static time_t t;
    static struct tm *tmp;

    va_list ap;
    FILE *fp;

    /* Obtém o tempo atual */
    t = time(NULL);
    tmp = localtime(&t);

    /* Abre o arquivo de debug sem sobreescrevê-lo */
    fp = fopen(DEBUG_FILENAME, "a");

    /* Formata a string de tempo e escreve nome arquivo */
    strftime(timestrbuf, sizeof (timestrbuf), TIMESTR, tmp);
    fprintf(fp, "[%s] ", timestrbuf);

    /* Escreve a mensagem formatada no arquivo */
    va_start(ap, fmessage);
    vfprintf(fp, fmessage, ap);
    va_end(ap);

    /* Insere uma quebra de linha e fecha o arquivo */
    fprintf(fp, "\n");
    fclose(fp);
}
