#include <ncurses.h>
#include "janela_tamanho.h"
#include "defines_lolo.h"
#include "selecionar_opcoes_posicao.h"
#include "menus.h"
#include "arquivos.h"
#include "jogo.h"
#include "cores.h"

#ifdef DEBUG
#include "debug.h"
#endif

int main(int argc, char **argv)
{
    /* Escreve no arquivo de DEBUG que o debug está ativado */
    #ifdef DEBUG
        debug_message("Debug ativado.");
    #endif

    /* Verifica se o jogo tem todas os arquivo necessários para executar */
    int res = verifica_arquivos();

    if ( res ) {
        #ifdef DEBUG
            debug_message("Encerrando o jogo por erro");
        #endif

        printf("Nao foi possivel carregar todos os arquivos necessarios.\n");
        return 1;
    }

    /* Inicializa a janela */
    initscr();

    if ( !has_colors() || !can_change_color() ) {
        #ifdef DEBUG
            debug_message("Erro: O terminal nao suporta cores");
        #endif

        printf("Seu terminal nao suporta cores.\n");
        endwin();

        return 2;
    }


    /* Configura a entrada */
    noecho();
    curs_set(0);
    raw();
    timeout(140);
    keypad(stdscr, true);
    /*
     *  Muda o ESCDELAY na Ncurses. É o tempo que aguarda para uma combinação
     *  de teclas.  No jogo não é utilizada combinação de teclas, então é
     *  setado para 1ms para que a tecla ESC no submenu do jogo funcione sem
     *  delay
     */
    set_escdelay(1);

    inicializa_cores();

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
              debug_message("Opcao selecionada: %d", opcao);
            }
        #endif

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
                if ( novojogo() ) {
                    endwin();
                    return 1;
                }

                clear();
                break;
            case CARREGARJOGO:
                if ( carregarjogo() ) {
                    endwin();
                    return 1;
                }

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
        debug_message("Encerrando o jogo normalmente");
    #endif

    /* Encerra a janela */
    endwin();

    return 0;
}
