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

/* TODO: apenas funcionamento básico, 's' para sair */
int loop_jogo(mapa_st *mapa, gravacao_st *gravacao)
{
    /* Onde deve exibir as informações */
    int y_delta_info;
    int y_inicio_info;
    char buf[19];
    lolo_st lolo;
    int ch;
    int ret;

    /* Carrega as informações do último nível e a posição atual */
    lolo.vidas = gravacao->vidas;
    lolo.pos.y = mapa->lolo.y;
    lolo.pos.x = mapa->lolo.x;
    lolo.pontos = gravacao->totalpts;

    /* Exibe todo o mapa */
    exibe_grid(mapa->elementos);

    /* Exibe um separador entre o mapa e as informações */
    move(1,56);
    attron(COLOR_PAIR(HIGHLIGHT));
    vline(' ', 23);
    attroff(COLOR_PAIR(HIGHLIGHT));

    /* Exibe as informações */
    exibe_dados_inicial(gravacao, mapa, &lolo, &y_delta_info, &y_inicio_info);

    /* Loop principal */
    do {
        /* Espera 1000/20 ms, então lê a entrada */
        napms(1000 / 20);
        ch = getch();
        /* Descarta o resto da entrada */
        flushinp();

        switch ( ch ){
            /* Chama movimenta_lolo apenas se for uma tecla de movimentação */
            case KEY_UP:
            case KEY_DOWN:
            case KEY_RIGHT:
            case KEY_LEFT:
                ret = movimenta_lolo(&lolo, ch);

                /* Atualiza informações conforme a Movimentação do Lolo */
                switch ( ret ) {
                    case 2:
                    case 3:
                    case 4:
                    case 255:
                        /* Atualiza a vida */
                        snprintf(buf, 19, "Vidas: %d", lolo.vidas);
                        exibe_item(buf, 1, y_inicio_info, y_delta_info, 55+2+11);

                        /* Não tem mais vidas */
                        if ( ret == 255 ) {
                            /* TODO: Mostrar menu */
                            ch = 's';
                        /* Matou um inimigo */
                        } else if ( ret == 2 ) {
                            /* TODO: Adicionar verificação */
                            limpa_inimigo_pos(&(mapa->inimigos), &(mapa->inimigos_num),
                                lolo.pos.y, lolo.pos.x);
                            snprintf(buf, 19, "inimigos: %d", mapa->inimigos_num);
                            exibe_item(buf, 2, y_inicio_info, y_delta_info, 55+2+11);
                        /* Pegou um coração */
                        } else if ( ret == 4 ) {
                            mapa->coracoes_num--;
                            snprintf(buf, 19, "Coracoes: %d", mapa->coracoes_num);
                            exibe_item(buf, 3, y_inicio_info, y_delta_info, 55+2+11);
                        }

                        break;
                    default:
                        break;
                }
            default:
                break;
        }

        /* Movimenta os inimigos que estão vivos */
        for ( int i = 0; i < mapa->inimigos_num; i++ ) {
            movimenta_inimigo((mapa->inimigos)[i]);
        }

        /* Atualiza o tempo */
        formata_delta_tempo(buf, 19,
            (long int)difftime(time(NULL), gravacao->final));
        exibe_item(buf, 7, y_inicio_info, y_delta_info, 55+2+11);

        refresh();
    } while ( ch != 's' );

    /* Limpa os inimigos remanescentes */
    limpa_inimigos(&(mapa->inimigos), mapa->inimigos_num);
    mapa->inimigos_num = 0;

    /* Atualiza os dados, TODO: não atualizar se usuário deseja salvar */
    gravacao->vidas = lolo.vidas;
    gravacao->totalpts = lolo.pontos;
    gravacao->final = time(NULL);

    /* TODO: outros retorno, por enquanto não há necessidade */
    return (lolo.vidas == 0 ? 1 : 0);
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

int movimenta_lolo(lolo_st *lolo, int key)
{
    /* Próxima posição de Lolo */
    ponto_st new_pos = muda_pos(lolo->pos, key);
    /* Usado no caso de new_pos ser a posição de um bloco móvel */
    ponto_st bloco_pos;

    /* ch -> próxima localicazão, _ch usado caso seja BLOCO_MOVEL */
    chtype ch = mvinch(new_pos.y, new_pos.x) & A_CHARTEXT; /* Extrai o texto */
    chtype _ch;
    /* Indica se precisamos mudar a posição de lolo em sua estrutura */
    int movimenta = 0;
    /* Valor a ser retornado */
    int ret = 0;

    switch ( ch ) {
        /* Não se mexe */
        case BLOCO_FIXO:
            ret = 1;
            break;
        /* Verifica se é válido */
        case BLOCO_MOVEL:
            bloco_pos = muda_pos(new_pos, key);
            _ch = mvinch(bloco_pos.y, bloco_pos.x) & A_CHARTEXT;

            /* Se a próxima posição for um bloco móvel então é válido */
            if ( _ch == LIVRE ) {
                exibe_caractere_jogo(BLOCO_MOVEL, bloco_pos.y, bloco_pos.x);
                movimenta = 1;
            /* Se não for não fazemos nada */
            } else {
                /* Indica que não houve nenhuma mudança na posição */
                ret = 1;
            }
            break;
        case INIMIGO:
        case AGUA:
            lolo->vidas--;

            /* Se tiver vidas o suficente, move-se e perde uma vida */
            if ( lolo->vidas > 0 ) {
                movimenta = 1;
                ret = (ch == INIMIGO ? 2 : 3);
            /* Se não perdeu */
            } else {
                movimenta = 1;
                ret =  255;
            }
            break;
        /* Se foi uma coração devemos aumentar a vida */
        case CORACAO:
            lolo->vidas++;
            movimenta = 1;
            ret = 4;
            break;
        /*
        * Se foi o baú nos movemos para ele e verificamos no loop principal se está
        * aberto
        */
        case BAU:
            movimenta = 1;
            ret = 5;
            break;
        /* Bloco Livre */
        default:
            movimenta = 1;
            break;
    }

    /* Atualiza a posição de Lolo em sua estrtura */
    if ( movimenta ) {
        /* O loop deve ver se antigamente era um baú */
        exibe_caractere_jogo(LIVRE, lolo->pos.y, lolo->pos.x);
        exibe_caractere_jogo(LOLO, new_pos.y, new_pos.x);
        lolo->pos = new_pos;
    }

    /* retorno o código específico */
    return ret;
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

    /* Desenha o inimigo na nova posição */
    exibe_caractere_jogo(INIMIGO, inimigo->pos.y, inimigo->pos.x);

    /* Indica que a posição do inimigo mudou */
    return 1;
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
