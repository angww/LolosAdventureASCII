

void desenha_janela_quadro(int start_x, int start_y, int end_x, int end_y, int msec_animacao) {
    
    WINDOW *win  = newwin(end_y-start_y,end_x-start_x,start_x,start_y);
    WINDOW *wini = newwin(end_y-start_y-2,end_x-start_x-2,start_x+1,start_y+1);
    
    box(win, '=', '=');
    wborder(win, '=', '=', '=','=','=','=','=','=');

    box(wini, '=', '=');
    wborder(wini, '=', '=', '=','=','=','=','=','=');


    refresh();
    wrefresh(win);
    wrefresh(wini);
    
}

void desenha_janela_quadro_animado(int start_x, int start_y, int end_x, int end_y) {
    desenha_janela_quadro(start_x, start_y, end_x, end_y, JANELA_MSEC_ANIMACAO);
}

void desenha_janela_quadro_direto(int start_x, int start_y, int end_x, int end_y) {
    desenha_janela_quadro(start_x, start_y, end_x, end_y, 0);
}

void desenha_janela_fullframe_animado() {
    desenha_janela_quadro(1, 1, JANELA_MAX_X, JANELA_MAX_Y, JANELA_MSEC_ANIMACAO);
 }

void desenha_janela_fullframe_direto() {
    desenha_janela_quadro(0, 0, JANELA_MAX_X, JANELA_MAX_Y, 0);
 }



void desenha_janela_titulo(char *str) {

    int posStrX = 0;
    char str_titulo[JANELA_MAX_X];
    
    /* Coloca barras na volta do título */
    sprintf(str_titulo, "| %s |", str); 

    /* Calcula para centralizar string no quadro */
    posStrX = (JANELA_MAX_X / 2) - (strlen(str_titulo) / 2) - 1;
    
    desenha_janela_fullframe_direto();
    mvprintw(0, posStrX, "%s", str_titulo);
    refresh();
}