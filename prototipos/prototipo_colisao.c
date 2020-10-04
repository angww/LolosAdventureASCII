#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h> /* usleep() */

#define PERSONAGEM 'E'

/* 
 * Arquivo criado com propósito de se ter uma idéia
 * geral de como pode ser feita a implementação do teste
 * de colisão, se trata de versão de teste em que apenas
 * impede que saia do mapa.
 * 
 * A função retorna char, pois ao meu ver não há necessidade
 * de retornar um inteiro, podemos vir a usar constantes para
 * definir se o inimigo, ao se mover, alcançou Lolo, nesse caso
 * o retorno poderia ser visto dessa maneira:
 *
 * 	0b000 00000
 *
 * Onde os últimos 5 bits contém as informações que precisamos:
 * 	4 -> Encostou em Lolo		soma 2^4
 * 	5 -> Mover-se para cima		soma 2^3
 * 	6 -> Mover-se para baixo	soma 2^2
 * 	7 -> Mover-se para direita	soma 2^1
 * 	8 -> Mover-se para esquerda	soma 2^0
 *
 * Onde podemos usar um bit and para verificar se o retorno tem
 * determinada "1" em true.
 *
 * Ainda é necessário contruir o caso em que, ao colidir com
 * um bloco móvel, vá para uma livre.
 */

char decide_proximo_mov(int *pos, char *tela[14]);

int main(void) {
	char *tela[14] = { "=============\n",
 	                   "=           =\n",
 	                   "=           =\n",
	                   "=           =\n",
 	                   "=           =\n",
 	                   "=           =\n",
 	                   "=============\0"};

	int pos[2] = {1,1}; /* Posição inicial */
	char mov = 0; /* Retorno da função */
	
	initscr();
	curs_set(0);

	for ( int i = 0; i < 7; i++ )
		printw(tela[i]);

	move(pos[0], pos[1]);
	printw("%c", PERSONAGEM);

	refresh();
	usleep(500000);

	for ( int i = 0; i< 1000; i++ ) {
		/* Deixa em branco a posição anterior */
		move(pos[0], pos[1]);
		printw(" ");

		/* Altera o valor de pos */
		mov = decide_proximo_mov(pos, tela);
		switch ( mov ) {
			case 1:
				pos[0]++;
				break;
			case 2:
				pos[0]--;
				break;
			case 3:
				pos[1]++;
				break;
			case 4:
				pos[1]--;
				break;
			default:
				break;
		};
		
		/* Move o cursor para pos */
		move(pos[0], pos[1]);
		printw("%c", PERSONAGEM);

		refresh();
		usleep(500000);
	}

	endwin();

	return 0;
}

char decide_proximo_mov(int *pos, char *tela[14]){
	/* 
	 * 0 -> Não se movimenta no eixo x
	 * 1 -> Move-se para a direita
	 * 2 -> Move-se para a esquerda
	 */
	char x = (rand() % 3);

	if ( x == 1 ) {
		if ( tela[pos[0] + 1][pos[1]] == ' ' ) {
			return x;
		}
	} else if ( x == 2 ) {
		if ( tela[pos[0] - 1][pos[1]] == ' ' ) {
			return x;
		}
	}

	/*
	 * No caso de não ser possível a movimentação
	 * no eixo x, tenta decidir uma movimentação para
	 * o eixo y, onde:
	 * 	0 -> Não se movimenta no eixo y
	 * 	1 -> Move-se para cima
	 * 	2 -> Move-se para baixo
	 *
	 * Soma-se dois para diferenciar do retorno de x.
	 */	
	char y = (rand() % 3);

	if ( y == 1 ) {
		if ( tela[pos[0]][pos[1] + 1] == ' ' ) {
			return y + 2;
		}
	} else if ( y == 2 ) {
		if ( tela[pos[0]][pos[1] - 1] == ' ' ) {
			return y + 2;
		}
	}

	/* Não se move */
	return 0;
}
