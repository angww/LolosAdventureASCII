#include <ncurses.h>
#include "janela_tamanho.h"
#include "defines_lolo.h"
#include "selecionar_opcoes_posicao.h"
#include "menus.h"
#include "arquivos.h"
#include "jogo.h"

#ifdef DEBUG
#include "debug.h"
#endif

int main(int argc, char **argv)
{
    /* Escreve no arquivo de DEBUG que o debug está ativado */
    #ifdef DEBUG
        write_debug_message("Debug ativado.");
    #endif

    /* Vericia se o jogo tem todas os arquivo necessários para executar */
    int res = verifica_arquivos();

    if ( res ) {
        #ifdef DEBUG
            write_debug_message("Enecerrando o jogo por erro");
        #endif

        printf("Nao foi possivel carregar todos os arquivos necessarios.\n");
        return 1;
    }

    /* Inicializa a janela */
    initscr();

    /* Configura a entrada */
    noecho();
    curs_set(0);
    raw();
    halfdelay(JANELA_MSEC_ANIMACAO);
    keypad(stdscr, true);

    /* Inicializa a cor do highlight */
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    /* Se o tamanho da janela não for válido, espera até que seja */
    if ( !(tamanho_valido())) {
      espera_tamanho_valido();
    }

    int opcao = 0;

    do {
        /* Desenha uma borda na janela principal */
        desenha_borda(stdscr);

        /* Obtém a opção selecionada pelo usuário */
        opcao = menu_principal();

        /*
         * Escreve no arquivo de DEBUG a opção selecionada, caso não seja
         * KEY_RESIZE
         */
        #ifdef DEBUG
            if ( opcao != KEY_RESIZE ) {
              write_debug_messagef("Opcao selecionada: %d", opcao);
            }
        #endif

        /* Incompleto */
        switch ( opcao ) {
            case CREDITOS:
                clear();
                desenha_borda(stdscr);
                creditos();

                clear();
                break;
            case RECORDES:
                clear();
                desenha_borda(stdscr);
                recordes();

                clear();
                break;
            case NOVOJOGO:
                clear();
                desenha_borda(stdscr);
                novojogo();

                clear();
                break;
            case CARREGARJOGO:
                clear();
                desenha_borda(stdscr);
                carregarjogo();

                clear();
                break;
            /* Apenas volta para o loop */
            case KEY_RESIZE:
                /* Se o tamanho da janela não for válido, espera até que seja */
                if ( !(tamanho_valido())) {
                  espera_tamanho_valido();
                }

                break;
            case ESC:
            default:
                break;
        }
    } while ( opcao != MENU_PRINCIPAL_SAIR );

    #ifdef DEBUG
        write_debug_message("Encerrando o jogo normalmente");
    #endif

    /* Encerra a janela */
    endwin();

    return 0;
}
