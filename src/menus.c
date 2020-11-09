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
        MEIO_X);
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
    /* TODO: ler arquivo de recordes */
    char *recordes[] = {
                       "Recordes",
                       "#0001 127389 912738 18293",
                       "#0001 127389 912738 18293",
                       "#0001 127389 912738 18293",
                       "#0001 127389 912738 18293",
                       "#0001 127389 912738 18293"};

    char *opcao = "Voltar ao menu principal";
    int y_delta = distancia_itens(7, 23, 2);
    int y_inicio = 2 + (y_delta / 2);

    exibe_itens(recordes, 6, y_inicio, y_delta, MEIO_X);

    return seleciona_opcao(opcao, y_inicio + (y_delta * 6), MEIO_X);
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


int exibe_menu_pause() {

    /* Desenha uma janela sobre o jogo atual */
    WINDOW *w = newwin(16,32,5,12);
    box( w, 0, 0 ); 
    wrefresh(w); 

    char *opcoes[] = { " Continuar Jogando", "Salvar Jogo", "Voltar para o Menu"};
    int y_delta;

    /* Distância no eixo y entre um item e outro */
    y_delta = distancia_itens(3, 15, 5);

    exibe_item(" == LoLo's PAUSE ==", 0, 6, 0, 27);

    /* Retorna a opção selecionada */
    return seleciona_opcoes(opcoes, 3, 10, y_delta, 27);
}


int processa_menu_pause() {

    int comando_menu_pause = exibe_menu_pause();

    switch ( comando_menu_pause ) {
        case OPCAO_CONTINUAR_JOGANDO:
            /* Não faz nada. */
            break; 
        case OPCAO_SALVAR:
            /* TODO: Opcao salvar. */
            break;
        case OPCAO_SAIR: 
            break;
            /* Sair subrotina novojogo. */
    }

    return comando_menu_pause;
}

int exibe_game_over() {

    /* Desenha uma janela sobre o jogo atual */
    WINDOW *w = newwin(16,32,5,12);
    box( w, 0, 0 ); 
    wrefresh(w); 

    char *opcoes[] = { "Novo Jogo", "Carregar Jogo", "Voltar para o Menu"};
    int y_delta;

    /* Distância no eixo y entre um item e outro */
    y_delta = distancia_itens(3, 15, 5);

    exibe_item("==  GAME OVER  ==", 0, 6, 0, 27);

    /* Retorna a opção selecionada */
    return seleciona_opcoes(opcoes, 3, 10, y_delta, 27);

}

int processa_menu_game_over() {
 
    int comando_menu_pause = exibe_game_over();

    switch ( comando_menu_pause ) {
        case OPCAO_NOVO_JOGO:
            /* TODO: Implementar. */
            break;
        case OPCAO_SAIR: 
            break;
            /* Sair subrotina novojogo. */
    }

    return comando_menu_pause;
}