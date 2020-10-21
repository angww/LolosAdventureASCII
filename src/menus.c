#include "menus.h"

int menu_principal(void)
{
    /* Opções do menu principal */
    char *opcoes[] = { "Novo Jogo", "Carregar Jogo", "Recordes", "Como Jogar",
                       "Creditos", "Sair do Jogo" };
    int y_delta;

    /* Distância no eixo y entre um item e outro */
    y_delta = distancia_itens(6, FINAL_GRIDY_MENU_PRINCIPAL,
        INICIO_GRIDY_MENU_PRINCIPAL);

    exibe_item("LoLo's Adventre - ASCII", 0, 5, 0, 40);

    /* Retorna a opção selecionada */
    return seleciona_opcoes(opcoes, 6, INICIO_GRIDY_MENU_PRINCIPAL, y_delta,
        MEIO_X);
}

int creditos(void)
{
    /* Créditos */
    char *creditos[] = { "Creditos",
                         "Andrei Rocha Bereta - 00324442",
                         "Angelo Araujo       - nnnnnnnn"};
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
    /* Variáveis usadas para calcular */
    float y_deltaf;
    int y_delta;
    int tamanho_y;

    /* Tamanho disponível para uso */
    tamanho_y = final_y - inicial_y;
    /* Espaço exato que pode ser colcoado entre um item e outro */
    y_deltaf  = (float)(tamanho_y - num_opcoes) / num_opcoes;
    /* Espaço truncado entre um item e outro */
    y_delta   = (int)y_deltaf + 1;

    /*
     * Se adiferença entre uma linha e outra não for exata, aumenta a
     * distância
     */
    if ( y_delta != (int)y_delta ) {
        y_delta++;
    }

    /* Se a última opção ultrapassar o grid, devemos diminuir a distância */
    if ( (y_delta * num_opcoes) >= final_y) {
        y_delta--;
    }

    return y_delta;
}
