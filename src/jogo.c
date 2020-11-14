#include "jogo.h"

int novojogo(void)
{
    gravacao_st tmp_gravacao[5];
    gravacao_st gravacao;
    int id;

    /*
     * O id será o maior incermentado por um, se o maior for 999 (limite),
     * procura o menor id disponível
     */
    le_arquivo(tmp_gravacao, sizeof (gravacao_st), 5, PASTA "/" SAVE_FILE);
    id = maior_id(tmp_gravacao);
    if ( id == 999 ) {
        id = 1;

        while ( !id_disponivel(tmp_gravacao, id) ) {
            id++;
        }
    } else {
        id++;
    }

    /* TODO: Obter o nome */
    strncpy(gravacao.nome_jogador, "Exemplo", 9);

    gravacao.identificador = id;
    gravacao.totalpts = 0;
    gravacao.ultimafase = 0;
    gravacao.vidas = 3;
    gravacao.inicio = time(NULL);
    gravacao.final = time(NULL);

    joga_mapas(&gravacao);

    return 0;
}

int carregarjogo(void)
{
    /* Ainda incompleto, próximo commit deverá conter as novas funções */
    gravacao_st gravacao;
    int ret;

    ret = seleciona_gravacao();

    /* Sair */
    if ( ret == -1 ) {
        return 0;
    }

    le_arquivo_pos(&gravacao, sizeof (gravacao_st), PASTA "/" SAVE_FILE, ret);
    joga_mapas(&gravacao);

    return 0;
}

int salvarjogo(gravacao_st *gravacao)
{
    /* Número de gravações já existentes */
    gravacao_st tmp_gravacao[5];
    le_arquivo(tmp_gravacao, sizeof (gravacao_st), 5, PASTA "/" SAVE_FILE);
    int pos = num_gravacoes(tmp_gravacao);

    if ( pos == 5 ) {
        pos = seleciona_gravacao_sobreescrever(tmp_gravacao);

        if ( pos == 5 ) {
            return 1;
        }
    }

    escreve_arquivo_pos(gravacao, sizeof (gravacao_st), PASTA "/" SAVE_FILE,
        pos);

    return 0;
}

int joga_mapas(gravacao_st *gravacao)
{
    char *niveis[] = NIVEIS;
    mapa_st mapa;
    int ret;

    /* Execta até chegar no último arquivo, jogador perder ou voltar ao menu */
    for ( ; gravacao->ultimafase < NUM_NIVEIS; gravacao->ultimafase++ ) {
        /* Executa se conseguiu carregar e processar o mapa */
        if ( carrega_arquivo_mapa(&mapa, niveis[gravacao->ultimafase]) == 0 ) {
            ret = loop_jogo(&mapa, gravacao);
        /* Não conseguiu carregar ou processar o mapa */
        } else {
            return 1;
        }

        /* Jogador perdeu */
        if ( ret == 1 ) {
            break;
        }
    }

    return 0;
}

/* TODO: apenas funcionamento básico, ESC abre o menu */
int loop_jogo(mapa_st *mapa, gravacao_st *gravacao)
{
    /* Onde deve exibir as informações */
    int y_delta_info = distancia_itens(9, 22, 3);
    int y_inicio_info = 3 + (y_delta_info / 2);
    time_t tmp;
    char buf[19];
    lolo_st lolo;
    int ch = 0;
    int ret = 0;
    int ret_submenu = 0;

    /* Carrega as informações do último nível e a posição atual */
    lolo.vidas = gravacao->vidas;
    lolo.pos.y = mapa->lolo.y;
    lolo.pos.x = mapa->lolo.x;
    lolo.pontos = gravacao->totalpts;

    if ( !tamanho_valido() ) {
        espera_tamanho_valido();
    }

    exibe_jogo(&lolo, gravacao, mapa, y_delta_info, y_inicio_info);

    /* Loop com submenu de pause */
    do {
        /* Loop principal */
        do {
            /* Espera 1000/20 ms, então lê a entrada */
            //napms(1000 / 20);
            ch = getch();
            /* Descarta o resto da entrada */
            flushinp();

            /* Impede que os inimigos se movam ao pressionar ESC */
            if ( ch == ESC ) {
                break;
            }

            switch ( ch ){
                case KEY_RESIZE:
                    if ( !tamanho_valido() ) {
                        tmp = time(NULL);
                        espera_tamanho_valido();
                        altera_inicio(gravacao, tmp);

                        exibe_jogo(&lolo, gravacao, mapa, y_delta_info, y_inicio_info);
                    } else {
                        resize_term(JANELA_MAX_Y, JANELA_MAX_X);
                    }

                    /* Impede que os inimigos se movam */
                    continue;
                /* Chama movimenta_lolo apenas se for uma tecla de movimentação */
                case KEY_UP:
                case KEY_DOWN:
                case KEY_RIGHT:
                case KEY_LEFT:
                    ret = movimenta_lolo(&lolo, mapa, ch);
                    break;
                case ERR:
                    if ( (mapa->elementos)[(lolo.pos.y)-1][(lolo.pos.x)-1] == AGUA ) {
                        lolo.vidas--;
                        ret = ATUALIZA_VIDA;
                    }
                    break;
                default:
                    break;
            }

            /* movimenta_lolo precisa atualizar alguma informação */
            if ( ret ) {
                atualiza_info(&lolo, mapa, y_delta_info, y_inicio_info, ret);
            }

            /* TODO: */
            if ( ret & ATUALIZA_GANHOU ) {
                ret_submenu = OPCAO_SAIR;
                break;
            }

            if ( lolo.vidas < 1 ) {
                ch = GAME_OVER;
                break;
            }

            /* TODO: gerenciar melhor o erro */
            if ( movimenta_inimigos(mapa, &lolo, y_inicio_info, y_delta_info) ) {
                ch = GAME_OVER;
                ret_submenu = OPCAO_SAIR;
            }

            if ( lolo.vidas < 1 ) {
                ch = GAME_OVER;
                break;
            }

            /* Atualiza o tempo */
            formata_delta_tempo(buf, 19,
                (long int)difftime(time(NULL), gravacao->final));
            exibe_item(buf, 7, y_inicio_info, y_delta_info, 55+2+11);

            ret = 0;
            refresh();
        } while ( ch != ESC && ch != GAME_OVER );

        if (ch == ESC) {
            tmp = time(NULL);
            ret_submenu = exibe_submenu(ch);
            altera_inicio(gravacao, tmp);

            if ( ret_submenu == 1 ) {
                salvarjogo(gravacao);
            } else if ( ret_submenu == 2 ) {
                break;
            }

            /* Redesenha mapa */
            exibe_jogo(&lolo, gravacao, mapa, y_delta_info, y_inicio_info);
        }

        if (ch == GAME_OVER) {
            ret_submenu = exibe_submenu(ch);
        }
    } while (ret_submenu != OPCAO_SAIR);

    /* Limpa os inimigos remanescentes */
    limpa_inimigos(&(mapa->inimigos), mapa->inimigos_num);
    mapa->inimigos_num = 0;

    /* Atualiza os dados para o próximo mapa */
    gravacao->vidas = lolo.vidas;
    gravacao->totalpts = lolo.pontos;
    gravacao->final = time(NULL);

    /* TODO: outros retorno, por enquanto não há necessidade */
    return (lolo.vidas == 0 ? 1 : 0) || (ret_submenu == OPCAO_SAIR);
}

void altera_inicio(gravacao_st *gravacao, time_t inicio)
{
    time_t delta;
    delta = difftime(inicio, time(NULL));

    gravacao->final -= delta;
    gravacao->inicio -= delta;
}

void exibe_jogo(lolo_st *lolo, gravacao_st *gravacao, mapa_st *mapa,
    int y_delta_info, int y_inicio_info)
{
    desenha_borda(stdscr);

    /* Exibe todo o mapa */
    exibe_grid(mapa->elementos);

    /* Exibe Lolo e os inimigos */
    exibe_caractere_jogo(LOLO, lolo->pos.y, lolo->pos.x);

    for ( int i = 0; i < mapa->inimigos_num; i++ ) {
        exibe_caractere_jogo(INIMIGO, (mapa->inimigos[i])->pos.y,
            (mapa->inimigos[i])->pos.x);
    }

    /* Exibe um separador entre o mapa e as informações */
    move(1,56);
    attron(COLOR_PAIR(HIGHLIGHT));
    vline(' ', 23);
    attroff(COLOR_PAIR(HIGHLIGHT));

    /* Exibe as informações */
    exibe_todos_dados(gravacao, mapa, lolo, y_delta_info, y_inicio_info);
}

void exibe_grid(char grid[JOGO_JANELA_Y][JOGO_JANELA_X])
{
    for ( int l = 0; l < JOGO_JANELA_Y; l++ ){
        for ( int c = 0; c < JOGO_JANELA_X; c++ ) {
            /* +1 para x e y pois 0,0 tem a borda da janela */
            exibe_caractere_jogo(grid[l][c], l+1, c+1);
        }
    }
}

void atualiza_grid_mapa(mapa_st *mapa, ponto_st pos, int item_grid) {
    /* Pos -1 devido a borda da janela */
    mapa->elementos[(pos.y)-1][(pos.x)-1] = item_grid;
}
