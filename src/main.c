#include <ncurses.h>
#include "janela_tamanho.h"
#include "defines_lolo.h"
#include "selecionar_opcoes_posicao.h"
#include "menus.h"
#include "arquivos.h"

#ifdef DEBUG
#include "debug.h"
#endif

int main(int argc, char **argv)
{
    /* Escreve no arquivo de DEBUG que o debug está ativado */
    #ifdef DEBUG
        write_debug_message("Debug ativado.");
    #endif

    /*
     * Tenta abrir os diretórios usados pelo jogo, caso não consiga, encerra a
     * execução
     */
    if ( tenta_abrir_ou_criar_pasta(PASTA) ) {
        #ifdef DEBUG
            write_debug_messagef("Encerrando o jogo, houve erro ao tentar "
                "acessar a pasta: %s.", PASTA);
        #endif

        return 1;
    }

    /* Inicializa a janela */
    initscr();

    /* Configura a entrada */
    noecho();
    curs_set(0);
    raw();
    halfdelay(10);
    keypad(stdscr, true);

    /* Inicializa a cor do highlight */
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    int opcao;

    do {
        /* Se o tamanho da janela não for válido, espera até que seja */
        if ( !(tamanho_valido())) {
          espera_tamanho_valido();
        }

        /* Desenha uma borda na janela principal */
        desenha_borda(stdscr);

        /* Obtém a opção selecionada pelo usuário */
        opcao = menu_principal();

        /* Escreve no arquivo de DEBUG a opção selecionada */
        #ifdef DEBUG
            write_debug_messagef("Opcao selecionada: %d", opcao);
        #endif

        /* Incompleto */
        switch ( opcao ) {
            case MENU_PRINCIPAL_JOGAR:
                clear();
                desenha_borda(stdscr);

                //jogo();
                break;
            /* Apenas volta para o loop */
            case KEY_RESIZE:
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
