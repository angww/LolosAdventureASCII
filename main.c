#include <stdio.h>

#include "includes/defines_lolo.h"
#include "includes/rlutil.h"
#include "includes/utils.h"
#include "includes/janelas.h"

int main() {

    hidecursor();
	saveDefaultColor();
	
	setColor(15);
    cls();

    desenha_janela_titulo("Menu Principal");
    locate(1, JANELA_MAX_Y);
    regua80();
    anykey("\nHit any key to start.\n");

    desenha_janela_quadro_animado(15,4,30,20);
    locate(1, JANELA_MAX_Y);
    anykey("\nHit any key to start.\n");

    cls();
    resetColor();
	showcursor();
    return 0;
}