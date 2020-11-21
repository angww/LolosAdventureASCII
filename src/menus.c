#include "menus.h"

int menu_principal(void)
{
    /* Opções do menu principal */
    char *opcoes[] = { "Novo Jogo", "Carregar Jogo", "Recordes", "Creditos",
        "Sair do Jogo" };
    int y_delta;

    /* Distância no eixo y entre um item e outro */
    y_delta = distancia_itens(5, FINAL_GRIDY_MENU_PRINCIPAL,
        INICIO_GRIDY_MENU_PRINCIPAL);

    exibe_item("LoLo's Adventre - ASCII", 0, 5, 0, 40);

    /* Retorna a opção selecionada */
    return seleciona_opcoes(opcoes, 5, INICIO_GRIDY_MENU_PRINCIPAL, y_delta,
        MEIO_X, 0);
}

int creditos(void)
{
    /* Créditos */
    char *creditos[] = { "Creditos",
                         "Andrei Rocha Bereta - 00324442",
                         "Angelo Araujo       - 00172380"};
    char *opcao = "Voltar ao menu principal";

    int y_delta = distancia_itens(4, 23, 2);
    int y_inicio = 2 + (y_delta / 2);

    exibe_itens(creditos, 3, y_inicio, y_delta, MEIO_X);

    return seleciona_opcao(opcao, y_inicio + (y_delta * 3), MEIO_X);
}

int recordes(void)
{
    int y_delta = distancia_itens(7, 23, 2);
    int y_inicio = 2 + (y_delta / 2);
    char recordes_formatados[5][60];
    char tempo_formatado[10];
    recorde_st buffer[5];

    exibe_item("Recordes", 0, y_inicio, y_delta, MEIO_X);

    le_arquivo(buffer, sizeof( recorde_st ), 5, PASTA "/" RECORDS_FILE);

    for ( int i = 0; i < 5; i++ ) {
        formata_delta_tempo(tempo_formatado, 10, (int) (buffer[i].tempo_total));
        snprintf(recordes_formatados[i], 60, "#%d   %05d   %-9s   %6s", i+1,
            buffer[i].totalpts, buffer[i].nome_jogador, tempo_formatado);
    }

    for ( int i = 0; i < 5; i++ ) {
        exibe_item(recordes_formatados[i], i+1, y_inicio, y_delta, MEIO_X);
    }

    return seleciona_opcao("Voltar ao menu principal", y_inicio + (y_delta * 6),
        MEIO_X);
}

int seleciona_gravacao(void)
{
    int num_gravacao = 0;
    int ret;
    int y_delta = distancia_itens(8, 23, 4);
    int y_inicio = 4 + (y_delta / 2);
    char opcoes[6][60];
    gravacao_st buffer[5];

    le_arquivo(buffer, sizeof( gravacao_st ), 5, PASTA "/" SAVE_FILE);

    num_gravacao = formata_gravacao(buffer, opcoes);

    strncpy(opcoes[num_gravacao], "Voltar para o menu principal", 60);

    do {
        exibe_item("Selecione um save", 0, y_inicio, y_delta, MEIO_X);
        exibe_item("id nivel  pts  vidas    nome      tempo  ", 1, y_inicio,
            y_delta, MEIO_X);

        ret =  seleciona_opcoes((char **) opcoes, num_gravacao+1,
            y_inicio + (y_delta * 2), y_delta, MEIO_X, 60);

        if ( ret == KEY_RESIZE ) {
            if ( !tamanho_valido() ) {
                espera_tamanho_valido();
                desenha_borda(stdscr);
            } else {
                resize_term(JANELA_MAX_Y, JANELA_MAX_X);
            }
        }
    } while ( ret < 0 || ret > num_gravacao );

    clear();

    if ( ret == num_gravacao ) {
        return -1;
    }

    return ret;
}

int seleciona_gravacao_sobreescrever(gravacao_st gravacao[5])
{
    int ret;
    int y_delta = distancia_itens(8, 23, 4);
    int y_inicio = 4 + (y_delta / 2);
    char opcoes[6][60];

    formata_gravacao(gravacao, opcoes);
    strncpy(opcoes[5], "Cancelar", 60);

    clear();
    desenha_borda(stdscr);

    do {
        exibe_item("Selecione o save que deseja sobreescrever", 0, y_inicio,
            y_delta, MEIO_X);
        exibe_item("id nivel  pts  vidas    nome      tempo  ", 1, y_inicio,
            y_delta, MEIO_X);

        ret = seleciona_opcoes((char **) opcoes, 6, y_inicio + (y_delta * 2),
            y_delta, MEIO_X, 60);

        if ( ret == KEY_RESIZE ) {
            if ( !tamanho_valido() ) {
                espera_tamanho_valido();
                desenha_borda(stdscr);
            } else {
                resize_term(JANELA_MAX_Y, JANELA_MAX_X);
            }
        }
    } while ( ret < 0 || ret > 6 );

    clear();

    return ret;
}

int distancia_itens(int num_opcoes, int final_y, int inicial_y)
{
    float y_deltaf;
    int y_delta;
    int tamanho_y;

    /* Tamanho disponível para uso */
    tamanho_y = final_y - inicial_y;
    /* Espaço exato que pode ser colcoado entre um item e outro */
    y_deltaf  = (float)(tamanho_y - num_opcoes) / num_opcoes;
    /* Espaço truncado entre um item e outro */
    y_delta   = (int)y_deltaf + 1;

    return y_delta;
}

int exibe_submenu(int ch)
{
    /* Desenha uma janela sobre o jogo atual */
    WINDOW *w = newwin(16, 32, 5, 12);
    box(w, 0, 0);
    wrefresh(w);

    int y_delta;
    int ret;
    char *titulo;
    char *opcoes[3];

    if ( ch == ESC ) {
        titulo = " == LoLo's PAUSE ==";
        opcoes[0] = "Continuar Jogando";
        opcoes[1] = "Salvar Jogo";
    } else {
        if ( ch == GAME_OVER ) {
            titulo = "==  GAME OVER  ==";
        } else {
            titulo = "==  VOCE GANHOU  ==";
        }
        opcoes[0] = "Novo Jogo";
        opcoes[1] = "Carregar Jogo";
    }

    opcoes[2] = "Voltar para o Menu";

    /* Distância no eixo y entre um item e outro */
    y_delta = distancia_itens(3, 15, 5);

    do {
        exibe_item(titulo, 0, 6, 0, 27);

        ret = seleciona_opcoes(opcoes, 3, 10, y_delta, 27, 0);

        if ( ret == KEY_RESIZE ) {
            wclear(stdscr);
            if ( !tamanho_valido() ) {
                espera_tamanho_valido();
            } else {
                resize_term(JANELA_MAX_Y, JANELA_MAX_X);
            }

            wresize(w, 16, 32);
            desenha_borda(stdscr);
            wrefresh(stdscr);
            wrefresh(w);
            box(w, 0, 0);
        } else if ( ret == ESC && ch == ESC ) {
            ret = 0;
        }
    } while ( ret < 0 || ret > 2 );

    return ret;
}

int le_nome(char *buf)
{
    int y_delta;
    int ret;
    int i = 0;
    int opcao = 0;
    int mudou_opcao = 0;
    char *textos[] = {"Insira seu nome:", "Continuar", "Cancelar"};

    strncpy(buf, "________", 9);

    /* Distância no eixo y entre um item e outro */
    y_delta = distancia_itens(4, 20, 7);

    exibe_item(textos[0], 0, 7, y_delta, 40);
    exibe_opcao(buf, 1, 7, y_delta, 40);
    exibe_item(textos[1], 2, 7, y_delta, 40);
    exibe_item(textos[2], 3, 7, y_delta, 40);

    do {
        ret = getch();

        if ( opcao == 0 ) {
            if ( isalnum(ret & A_CHARTEXT) && i < 8 ) {
                buf[i] = ret & A_CHARTEXT;
                i++;
            } else if ( ret == BACKSPACE && i > 0 ) {
                buf[--i] = '_';
            }

            exibe_opcao(buf, 1, 7, y_delta, 40);
        }

        switch ( ret ) {
            case KEY_UP:
                if ( opcao == 0 ) {
                    opcao = 2;
                } else {
                    opcao--;
                }

                mudou_opcao = 1;
                break;
            case KEY_DOWN:
                if ( opcao == 2 ) {
                    opcao = 0;
                } else {
                    opcao++;
                }

                mudou_opcao = 1;
                break;
            default:
                break;
        }

        if ( ret == KEY_RESIZE ) {
            if ( !tamanho_valido() ) {
                espera_tamanho_valido();
                wclear(stdscr);
                mudou_opcao = 1;
            } else {
                resize_term(JANELA_MAX_Y, JANELA_MAX_X);
            }

            desenha_borda(stdscr);
        }

        if ( mudou_opcao ) {
            exibe_item(textos[0], 0, 7, y_delta, 40);
            exibe_item(buf, 1, 7, y_delta, 40);
            exibe_item(textos[1], 2, 7, y_delta, 40);
            exibe_item(textos[2], 3, 7, y_delta, 40);

            if ( opcao == 0 ) {
                exibe_opcao(buf, 1, 7, y_delta, 40);
            } else {
                exibe_opcao(textos[opcao], opcao+1, 7, y_delta, 40);
            }

            mudou_opcao = 0;
            refresh();
        }
    } while ( !(opcao != 0 && ret == '\n') ||
              (opcao == 1 && i < 1) );

    if ( opcao == 1 ) {
        buf[i] = '\0';
        return 0;
    }

    return 1;
}
