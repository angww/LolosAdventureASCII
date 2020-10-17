##
## Instruções de uso do makefile:
##
## make        : Compila rotina principal
## make run    : Compila rotina principal e roda programa princial
## make tests  : Compila tudo e roda a rotina de testes.
## make clean  : Remove todos os binários e objetos
## variaveis   : Lista variáveis utilizadas internamentes no make.
## help        : Exibe estas mesmas instruções.
##
# Documentação oficial do make em https://www.gnu.org/software/make/manual/make.html

# Compilador
CC=gcc
# Flags para o compilador
CFLAGS=-lncurses -Wall
# Diretório onde estão os arquivos a serem compilados
SRC_DIR=./src/
# Arquivo de saída
BIN_OUT=lolosgame.out
# Arquivos fonte
SRCS=$(wildcard $(SRC_DIR)*.c)
# Arquivos objeto
OBJS=$(SRCS:.c=.o)

# Configura a ação padrão
.DEFAULT_GOAL := compile
.PHONY : clean

# Compila, depende de OBJS para compilar
compile: $(OBJS)
	@echo "Compilando... "
	@echo "Arquivo executável de saída:  " $(BIN_OUT)
	$(CC) -o $(BIN_OUT) $(OBJS) $(CFLAGS)

# Roda o commando compile antes
run: compile
	@echo "Executando ./$(BIN_OUT)"
	$(BIN_OUT)

# Para cada objeto, usa sua fonte
OBJS: SRCS
	$(CC) -c $@ $< $(CFLAGS)

# Remove os objetos
clean:
	@echo "Removendo arquivos .o"
	rm -f $(OBJS)
