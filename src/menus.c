#include "menus.h"

int menu_principal(void)
{
    /* Opçẽos do menu principal */
    char *opcoes[] = { MENU_PRINCIPAL_OPCOES };
    int y_delta;

    /* Distância no eixo y entre um item e outro */
    y_delta = distancia_itens(NUM_OPCOES_MENU_PRINCIPAL,
        FINAL_GRIDY_MENU_PRINCIPAL, INICIO_GRIDY_MENU_PRINCIPAL);

    /* TODO: Transformar valores em constantes */
    exibe_item("LoLo's Adventre", 0, 5, 0, 40);

    /* Retorna a opção selecionada */
    return seleciona_opcao(opcoes, NUM_OPCOES_MENU_PRINCIPAL,
        INICIO_GRIDY_MENU_PRINCIPAL, y_delta, MEIO_GRIDX_MENU_PRINCIPAL);
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
    if ( (num_opcoes + (y_delta * num_opcoes)) >= final_y) {
        y_delta--;
    }

    return y_delta;
}
