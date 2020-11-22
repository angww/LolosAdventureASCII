
# LolosAdventureASCII

> Versão simplificada em terminal do jogo Lolo's Adventure, lançado em 1989 para a plataforma NES.

:notes:  Este jogo é um trabalho de graduação para a cadeira de INF01202 - Algoritmos e Programação, curso de Ciência da Computação da UFRGS.

![Screenshoot Menu](https://raw.githubusercontent.com/angww/LolosAdventureASCII/main/misc/Lolos-menu.png)

![Screenshoot Fase 2](https://raw.githubusercontent.com/angww/LolosAdventureASCII/main/misc/Lolos-Gif-Fase2.gif)

![Screenshoot Fase 1](https://raw.githubusercontent.com/angww/LolosAdventureASCII/main/misc/Lolos-Fase1.png)

## Modificações

* Menu principal

Adicionado menu de recordes que armazenam as cinco maiores pontuções, com a seguinte estrutura:

```C
typedef struct {
    char nome_jogador[9];
    int totalpts;
    time_t tempo_total;
} recorde_st;
```

* Funcionamento do jogo

Adicionado registro de tempo para fases.

* Vidas

Ao invés do Lolo necessitar pegar um coração antes de eliminar um inimigo, ele pode eliminar o inimigo a qualquer momento.
A fase recomeça apenas após Lolo se afogar.
Lolo não ganha uma vida ao eliminar o 10º inimigo consecutivo.

* Pontuação

Cada inimigo eliminado soma 30 ao invés de 1.

* Implementação

Na estrutura de gravação foi adicionado registro de início e final do tempo de jogo.

``` C
typedef struct {
    int identificador;
    int totalpts;
    int ultimafase;
    int vidas;
    char nome_jogador[9];
    time_t inicio;
    time_t final;
} gravacao_st;
```

A estrutura da fase foi alterada para armazenar informações sobre o início e o estado atual da fase, `elementos` armazena o grid estático, `lolo` e `bau` armazenam a posição inicial de Lolo e do baú, respectivamente, `inimigo` armazena o ponteiro para cada inimigo, `inimigos_num` e `coracoes_num` armazenam a quantidade de inimigos e corações, respectivamente.
```C
typedef struct {
    char elementos[JOGO_JANELA_Y][JOGO_JANELA_X];
    ponto_st lolo;
    ponto_st bau;
    int coracoes_num;
    int inimigos_num;
    inimigo_st **inimigos;
} mapa_st;
```

## COMPILAÇÃO 

A compilação foi testada tanto no site `repl.it` quanto localmente usando o comando `make`, no `repl.it` é necessário compilar com o `clang`, localmente foi utilzado o `gcc`. Ao compilar é criado diretório `bin` contendo o binário e um subdiretório contendo os níveis, para executar pode-se tanto usar `make run` ou executar `lolosgame.out` caso esteja dentro do diretório `bin`.

Caso seja compilado com a opção `DEBUG` habilitada, será criado o arquivo `bin/log_lolo.log` que terá informações básicas sobre o que está ocorrendo no jogo.

[![Run on Repl.it](https://repl.it/badge/github/angww/LolosAdventureASCII)](https://repl.it/github/angww/LolosAdventureASCII)
