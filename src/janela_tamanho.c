#include "janela_tamanho.h"

#ifdef DEBUG
#include "debug.h"
#endif

void espera_tamanho_valido(void)
{
    /* Indica se o tamanho é válido ou não */
    int valido = 0;
    int ch;

    /* Limpa o que estava sendo exibido anteriormente */
    clear();
    move(0, 0);

    /* Exibe o aviso para redimensionar a janela */
    attron(COLOR_PAIR(1));
    printw("Tamanho inferior ao desejado(%d %d).\n", JANELA_MAX_Y, JANELA_MAX_X);
    attroff(COLOR_PAIR(1));

    do {
        ch = getch();

        /*
         * Se o usuário redimensionou a janela, verifica se agora o tamanho é
         * válido
         */
        if ( ch == KEY_RESIZE ) {
            valido = tamanho_valido();
        }
    } while ( !valido );

    /*
     * Limpa a mensagem da tela, a função que chamou espera_tamanho_valido deve
     * reimprimir seu conteúdo
     */
    clear();
}

void desenha_borda(WINDOW *win)
{
    /* Inicializa highlight e desenha a borda padrão */
    attron(COLOR_PAIR(1));
    wborder(win, 0,0,0,0,0,0,0,0);
    attroff(COLOR_PAIR(1));
}

int tamanho_valido(void)
{
    int valido;
    int max_y, max_x;

    /* Tamanho da janela */
    getmaxyx(stdscr, max_y, max_x);
    /* 1 se y e x forem maiores ou iguais ao minímo necessário */
    valido = (max_y >= JANELA_MAX_Y ? (max_x >= JANELA_MAX_X ? 1 : 0 ) : 0);

    /* Redimensiona o terminal para 25 x 80 */
    resize_term(JANELA_MAX_Y, JANELA_MAX_X);

    /*
     * Se DEBUG estiver definido, informa no arquivo de log a alteração do
     * tamanho da janela
     */
    #ifdef DEBUG
        char message[DEBUG_MESSAGE_SIZE];
        snprintf(message, DEBUG_MESSAGE_SIZE, "Janela com tamanho: (%d, %d), valido: %d", max_y, max_x, valido);
        write_debug_message(message);
    #endif

    /* Retorna se a janela tem tamanho válido ou não */
    return valido;
}
