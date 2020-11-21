#include "jogo.h"

int novojogo(void)
{
    gravacao_st tmp_gravacao[5];
    gravacao_st gravacao;
    int id;

    clear();
    desenha_borda(stdscr);

    if ( le_nome(gravacao.nome_jogador) ) {
        return 0;
    }

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

    gravacao.identificador = id;
    gravacao.totalpts = 0;
    gravacao.ultimafase = 0;
    gravacao.vidas = 3;
    gravacao.inicio = time(NULL);
    gravacao.final = time(NULL);

    return joga_mapas(&gravacao);
}

int carregarjogo(void)
{
    /* Ainda incompleto, próximo commit deverá conter as novas funções */
    gravacao_st gravacao;
    int ret;

    clear();
    desenha_borda(stdscr);

    ret = seleciona_gravacao();

    /* Sair */
    if ( ret == -1 ) {
        return 0;
    }

    le_arquivo_pos(&gravacao, sizeof (gravacao_st), PASTA "/" SAVE_FILE, ret);
    altera_inicio(&gravacao, gravacao.final);

    return joga_mapas(&gravacao);
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

        if ( ret == JOGO_PERDEU || ret == JOGO_VOLTAR ||
             ret == JOGO_DENOVO || ret == JOGO_CARREGAR ) {
            break;
        } else if ( ret == JOGO_ERRO ) {
            return 1;
        } else if ( ret == JOGO_AFOGADO ) {
            continue;
        }
    }

    if ( ret == JOGO_GANHOU ) {
        salva_recorde(gravacao);
        ret = exibe_submenu(JOGO_GANHOU);

        if ( ret == 0 ) { ret = JOGO_DENOVO; }
        else if ( ret ==  1 ) { ret = JOGO_CARREGAR; }
        else { ret = JOGO_OK; }
    }

    if ( ret == JOGO_DENOVO ) {
        return novojogo();
    } else if ( ret == JOGO_CARREGAR ) {
        return carregarjogo();
    }

    return 0;
}

int salva_recorde(gravacao_st *gravacao)
{
    /* Recordes já existentes */
    recorde_st tmp_recorde[5];
    recorde_st tmp1, tmp2;

    le_arquivo(tmp_recorde, sizeof (recorde_st), 5, PASTA "/" RECORDS_FILE);

    strncpy(tmp1.nome_jogador, gravacao->nome_jogador, 9);
    tmp1.tempo_total = (time_t) difftime(gravacao->final, gravacao->inicio);
    tmp1.totalpts = gravacao->totalpts + (10000 * (1 / tmp1.tempo_total));
    tmp1.totalpts *= gravacao->vidas;

    for ( int i = 0; i < 5; i++ ) {
        if ( tmp1.totalpts > tmp_recorde[i].totalpts ) {
            tmp2.totalpts = tmp_recorde[i].totalpts;
            strncpy(tmp2.nome_jogador, tmp_recorde[i].nome_jogador, 9);
            tmp2.tempo_total = tmp_recorde[i].tempo_total;

            escreve_arquivo_pos(&tmp1, sizeof (recorde_st),
                PASTA "/" RECORDS_FILE, i);

            tmp1.totalpts = tmp2.totalpts;
            strncpy(tmp1.nome_jogador, tmp2.nome_jogador, 9);
            tmp1.tempo_total = tmp2.tempo_total;
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
    int jogando = 1;
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
                default:
                    break;
            }

            /* movimenta_lolo precisa atualizar alguma informação */
            if ( ret ) {
                atualiza_info(&lolo, mapa, y_delta_info, y_inicio_info, ret);
            }

            if ( ret & (ATUALIZA_GANHOU|ATUALIZA_AGUA) || lolo.vidas < 1 ) {
                jogando = 0;
            }

            if ( movimenta_inimigos(mapa, &lolo, y_inicio_info, y_delta_info) ) {
                limpa_inimigos(&(mapa->inimigos), mapa->inimigos_num);
                mapa->inimigos_num = 0;

                return JOGO_ERRO;
            }

            if ( lolo.vidas < 1 ) {
                jogando = 0;
                break;
            }

            /* Atualiza o tempo */
            formata_delta_tempo(buf, 19,
                (long int)difftime(time(NULL), gravacao->final));
            exibe_item(buf, 7, y_inicio_info, y_delta_info, 55+2+11);

            refresh();
        } while ( jogando );

        if ( ch == ESC ) {
            tmp = time(NULL);
            ret_submenu = exibe_submenu(ch);
            altera_inicio(gravacao, tmp);

            switch ( ret_submenu ) {
                case 2:
                    jogando = 0;
                    break;
                case 1:
                    salvarjogo(gravacao);
                case 0:
                default:
                    jogando = 1;
            }

            /* Redesenha mapa */
            exibe_jogo(&lolo, gravacao, mapa, y_delta_info, y_inicio_info);
        }
    } while ( jogando );

    /* Limpa os inimigos remanescentes */
    limpa_inimigos(&(mapa->inimigos), mapa->inimigos_num);
    mapa->inimigos_num = 0;

    if ( ret_submenu == 2 ) {
        return JOGO_VOLTAR;
    } else if ( lolo.vidas < 1 ) {
        refresh();
        ret_submenu = exibe_submenu(GAME_OVER);
        clear();

        switch ( ret_submenu ) {
            case 0:
                return JOGO_DENOVO;
            case 1:
                return JOGO_CARREGAR;
            default:
                break;
        }

        return JOGO_PERDEU;
    }

    gravacao->vidas = lolo.vidas;

    if ( !(ret & ATUALIZA_AGUA) ) {
        /* Atualiza os dados */
        gravacao->totalpts = lolo.pontos;
        gravacao->final = time(NULL);
    } else {
        /* Jogar a mesma, caso tenha vidas */
        gravacao->ultimafase--;
    }

    /* Indica que ganhou */
    if ( ret & ATUALIZA_GANHOU ) {
        return JOGO_GANHOU;
    }

    return JOGO_OK;
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
