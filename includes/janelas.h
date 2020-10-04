//__inline setCharAt(char ch, int x, int y);

void desenha_janela_quadro(int start_x, int start_y, int end_x, int end_y, int msec_animacao) {

    for (int i = start_x-1; i < end_x; i++) {
        
        setCharAt('=', i + 1, start_y);
        setCharAt('=', i + 1, start_y+1);

        if (msec_animacao > 0) {
            msleep(msec_animacao);
            fflush(stdout);
        }
    }

    for (int i = start_y+2; i < end_y-2; i++) {
        
        setStringAt("==", start_x, i);
        setStringAt("==", end_x-1, i);
        
        if (msec_animacao > 0) {
            msleep(msec_animacao/2);
            fflush(stdout);
        }

    }

    for (int i = start_x-1; i < end_x; i++) {
        
        setCharAt('=', i + 1, end_y-1);
        setCharAt('=', i + 1, end_y-2);

        if (msec_animacao > 0) {
            msleep(msec_animacao/4);
            fflush(stdout);
        }
    }

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
    desenha_janela_quadro(1, 1, JANELA_MAX_X, JANELA_MAX_Y, 0);
 }



void desenha_janela_titulo(char *str) {

    int posStrX = 0;
    char str_titulo[JANELA_MAX_X];

    sprintf(str_titulo, "| %s |", str); // Coloca barras na volta do título

    // Calcula para centralizar string no quadro
    posStrX = (JANELA_MAX_X / 2) - (strlen(str_titulo) / 2) - 1;
    
    desenha_janela_fullframe_direto();
    setStringAt(str_titulo, posStrX, 1);
}