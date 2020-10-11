#include "defines_lolo.h"
#include "debug.h"

void write_debug_message(char *message) {
    static time_t t;
    static struct tm *tmp;
    static char timestrbuf[25];
    t = time(NULL);
    tmp = localtime(&t);

    FILE *fp;
    fp = fopen(DEBUG_FILENAME, "a");
    strftime(timestrbuf, sizeof (timestrbuf), TIMESTR, tmp);
    fprintf(fp, "[%s] %s\n", timestrbuf, message);
    fclose(fp);
}
