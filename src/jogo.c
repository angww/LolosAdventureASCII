#include "jogo.h"

int novojogo(void)
{
    /* TODO: Obter o nome */

    gravacao_st gravacao;

    /* Exemplo */
    strncpy(gravacao.nome_jogador, "Exemplo", 9);
    gravacao.totalpts = 9090;
    gravacao.ultimafase = 0;
    gravacao.vidas = 3;
    gravacao.inicio = time(NULL);
    gravacao.final = time(NULL);

    joga_mapas(&gravacao);

    return 0;
}

int carregarjogo(void)
{
    /* TODO: Menu para carregar os saves */

    /* Apenas para não repetir as definições */
    novojogo();

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
    int comando_menu_pause = 0;

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
                comando_menu_pause = OPCAO_SAIR;
                break;
            }

            if ( lolo.vidas < 1 ) {
                ch = GAME_OVER;
                break;
            }

            /* Movimenta os inimigos que estão vivos */
            for ( int i = 0; i < mapa->inimigos_num; i++ ) {
                /*
                 * Se o inimigo pegou Lolo, diminui a vida de Lolo e remove o
                 * inimigo
                 */
                if ( movimenta_inimigo((mapa->inimigos)[i]) ) {
                    #ifdef DEBUG
                        debug_message("Inimigo pegou Lolo");
                    #endif

                    if ( !(limpa_inimigo_pos(&(mapa->inimigos), &(mapa->inimigos_num),
                        lolo.pos.y, lolo.pos.x)) && lolo.vidas > 1 ) {
                        lolo.vidas--;
                        atualiza_info(&lolo, mapa, y_delta_info, y_inicio_info,
                            ATUALIZA_VIDA|ATUALIZA_INIMIGO);
                    } else {
                        /* TODO: encerrar jogo */
                        #ifdef DEBUG
                            debug_message("Erro ao limpar inimigo, encerrando");
                        #endif

                        break;
                    }
                }
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
            comando_menu_pause = processa_menu_pause();
            altera_inicio(gravacao, tmp);

            /* Redesenha mapa atualizado */
            exibe_jogo(&lolo, gravacao, mapa, y_delta_info, y_inicio_info);
        }

        if (ch == GAME_OVER) {
            comando_menu_pause = processa_menu_game_over();
        }
    } while (comando_menu_pause != OPCAO_SAIR);

    /* Limpa os inimigos remanescentes */
    limpa_inimigos(&(mapa->inimigos), mapa->inimigos_num);
    mapa->inimigos_num = 0;

    /* Atualiza os dados, TODO: não atualizar se usuário deseja salvar */
    gravacao->vidas = lolo.vidas;
    gravacao->totalpts = lolo.pontos;
    gravacao->final = time(NULL);

    /* TODO: outros retorno, por enquanto não há necessidade */
    return (lolo.vidas == 0 ? 1 : 0) || (comando_menu_pause == OPCAO_SAIR);
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

ponto_st muda_pos(ponto_st pos, int key)
{
    switch ( key ) {
        /* Lolo e inimigo */
        case 0:
        case KEY_UP:
            pos.y--;
            break;
        case 1:
        case KEY_DOWN:
            pos.y++;
            break;
        case 2:
        case KEY_RIGHT:
            pos.x++;
            break;
        case 3:
        case KEY_LEFT:
            pos.x--;
            break;
        default:
            break;
    }

    return pos;
}

int movimenta_lolo(lolo_st *lolo, mapa_st *mapa, int key)
{
    /* Próxima posição de Lolo */
    ponto_st new_pos = muda_pos(lolo->pos, key);
    /* Usado no caso de new_pos ser a posição de um bloco móvel */
    ponto_st bloco_pos;

    /* ch -> próxima localicazão, _ch usado caso seja BLOCO_MOVEL */
    chtype ch = mvinch(new_pos.y, new_pos.x) & A_CHARTEXT; /* Extrai o texto */
    chtype _ch;
    /* Indica se precisamos mudar a posição de lolo em sua estrutura */
    int movimenta = 1;
    /* Valor a ser retornado, indica se devemos atualizar alguma informação */
    int atualiza = 0;

    switch ( ch ) {
        case BLOCO_FIXO:
            movimenta = 0;
            break;
        case BLOCO_MOVEL:
            bloco_pos = muda_pos(new_pos, key);
            _ch = mvinch(bloco_pos.y, bloco_pos.x) & A_CHARTEXT;

            /*
             * Se a próxima posição do bloco móvel estiver livre então é válido,
             * imprime o caractere na tela e atualiza o elementos de mapa
             */
            if ( _ch == LIVRE ) {
                exibe_caractere_jogo(BLOCO_MOVEL, bloco_pos.y, bloco_pos.x);
                atualiza_grid_mapa(mapa, new_pos, LIVRE);
                atualiza_grid_mapa(mapa, bloco_pos, BLOCO_MOVEL);
            } else {
                movimenta = 0;
            }
            break;
        case INIMIGO:
            if ( limpa_inimigo_pos(&(mapa->inimigos), &(mapa->inimigos_num),
                new_pos.y, new_pos.x) ) {
                atualiza = ATUALIZA_ERRO;
                movimenta = 0;
            } else {
                lolo->vidas--;
                atualiza = ATUALIZA_INIMIGO|ATUALIZA_VIDA;
            }
            break;
        case AGUA:
            lolo->vidas--;
            atualiza = ATUALIZA_VIDA;
            break;
        case CORACAO:
            /* Remove o coração dos elementos do mapa */
            atualiza_grid_mapa(mapa, new_pos, LIVRE);
            mapa->coracoes_num--;
            lolo->vidas++;
            atualiza = ATUALIZA_CORACAO|ATUALIZA_VIDA;
            break;
        case BAU:
            /* Se o baú não estiver aberto lolo não pode passar por ele */
            if ( !(mapa->inimigos_num == 0 && mapa->coracoes_num == 0) ) {
                movimenta = 0;
            } else {
                atualiza = ATUALIZA_GANHOU;
            }
            break;
        /* Bloco Livre */
        default:
            break;
    }

    /* Atualiza a posição de Lolo em sua estrtura */
    if ( movimenta ) {
        /* Exibe o caractere que estava abaixo de lolo */
        exibe_caractere_jogo((mapa->elementos)[(lolo->pos.y)-1][(lolo->pos.x)-1],
            lolo->pos.y, lolo->pos.x);
        exibe_caractere_jogo(LOLO, new_pos.y, new_pos.x);
        lolo->pos = new_pos;
    }

    /* retorno o código específico */
    return atualiza;
}

int movimenta_inimigo(inimigo_st *inimigo)
{
    int mov = 0;
    int _mov;
    char adjacentes[4];
    int possibilidades = 0;

    /* Salva as posições adjacentes ao inimigo */
    adjacentes[0] = mvinch(inimigo->pos.y - 1, inimigo->pos.x) & A_CHARTEXT;
    adjacentes[1] = mvinch(inimigo->pos.y + 1, inimigo->pos.x) & A_CHARTEXT;
    adjacentes[2] = mvinch(inimigo->pos.y, inimigo->pos.x + 1) & A_CHARTEXT;
    adjacentes[3] = mvinch(inimigo->pos.y, inimigo->pos.x - 1) & A_CHARTEXT;

    /* Verifica quantas posições válidas existem */
    for ( int i = 0; i < 4; i++ ) {
        if ( !(adjacentes[i] & MASCARA_INIMIGO) ) {
            possibilidades++;
        }
    }

    /* Se não tiver nenhuma posição válida, não se move */
    if ( possibilidades == 0 ) {
        return 0;
    }

    /* Gera 0 até posibilidades -1 */
    _mov = (rand() % possibilidades);

    /* Vai pelas posições válidas */
    for ( int i = 0; i < _mov + 1; i++ ) {
        mov = prox_mov(adjacentes, mov);
    }

    /* Desenha espaço livre onde o inimigo estava */
    exibe_caractere_jogo(LIVRE, inimigo->pos.y, inimigo->pos.x);

    /* Atualiza a posição do inimigo */
    inimigo->pos = muda_pos(inimigo->pos, mov);

    if ( adjacentes[mov] == LOLO ) {
        /* Inimigo pegou Lolo */
        return 1;
    }

    /* Desenha o inimigo na nova posição */
    exibe_caractere_jogo(INIMIGO, inimigo->pos.y, inimigo->pos.x);

    return 0;
}

int prox_mov(char adjacentes[4], int mov) {
    /* Soma mov até que adjacentes[mov] seja uma posição válida para o inimigo */
    do {
        if ( mov == 3 ) {
            mov = 0;
        } else {
            mov++;
        }
    } while ( adjacentes[mov] & MASCARA_INIMIGO );

    return mov;
}

void atualiza_grid_mapa(mapa_st *mapa, ponto_st pos, int item_grid) {
    /* Pos -1 devido a borda da janela */
    mapa->elementos[(pos.y)-1][(pos.x)-1] = item_grid;
}
