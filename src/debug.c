#include "defines_lolo.h"
#include "debug.h"

void write_debug_message(char *message)
{
    /* string que será armazenado o tempo formatado */
    static char timestrbuf[25];

    /* Obtém o tempo atual */
    static time_t t;
    static struct tm *tmp;
    t = time(NULL);
    tmp = localtime(&t);

    /* Abre o arquivo de debug sem sobreescrevê-lo */
    FILE *fp;
    fp = fopen(DEBUG_FILENAME, "a");

    /* Formata a string de tempo */
    strftime(timestrbuf, sizeof (timestrbuf), TIMESTR, tmp);

    /* Imprime a mensagem no arquivo de debug e fecha o arquivo*/
    fprintf(fp, "[%s] %s\n", timestrbuf, message);
    fclose(fp);
}

void write_debug_messagef(char *fmessage, ...)
{
    /*
     * Conforme o manual 3 printf, caso snpritnf ou vsnprint sejam chamados
     * com size=0 e buffer=NULL, retornam o número de caracteres que seriam
     * escritos, ou seja, o tamanho da string final.
     * O código abaixo é, tirando as pequenas modificações, idêntico ao código
     * apresentado como exemplo no mesmo manual.
     */

    /* Armazenará quantos bytes o vsnprintf escreveu */
    int n_bytes = 0;
    /* Tamanho necessário para a string */
    size_t size = 0;
    /* Ponteiro para a string */
    char *message = NULL;
    /* Declara a variável que lidará com a lista de argumentos */
    va_list ap;

    /*
     * va_start() e va_end() operam sobre a lista de argumentos, esta primeira
     * execução do vsnprintf determinará o tamanho necessário
     */
    va_start(ap, fmessage);
    n_bytes = vsnprintf(message, size, fmessage, ap);
    va_end(ap);

    /* Se for menor do que 0, houve algum erro ao formatar a string */
    if (n_bytes >= 0) {
        /* Aumenta em um para armazenar o '\0' */
        size = (size_t) n_bytes + 1;
        message = malloc(size);

        /* Verifica se foi alocado */
        if (message != NULL) {
            /* Formata a string */
            va_start(ap, fmessage);
            n_bytes = vsnprintf(message, size, fmessage, ap);
            va_end(ap);

            /* Se for menor que 0, houve algum erro a formatar a string */
            if (n_bytes >= 0) {
                write_debug_message(message);
            } else {
                write_debug_message("Erro ao formatar mensagem de erro.");
            }

            /* Limpa o espaço que havia sido alocado */
            free(message);
        } else {
            write_debug_message("Erro ao alocar memória para a string "
                "formatada.");
        }
    } else {
        write_debug_message("Erro ao formatar mensagem de erro.");
    }
}
