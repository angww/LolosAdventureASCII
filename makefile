# Modo de uso:
# make        # compila rotina principal
# make run    # compila rotina principal e roda programa princial
# make tests  # roda testes
# make clean  # remove todos os binários e objetos
#
# Documentação oficial do make em https://www.gnu.org/software/make/manual/make.html

CC = gcc	# Compilador a ser utilizado
CFLAGS = -lncurses
MAIN = main.c
BIN_OUT = logosgame.out 

.DEFAULT_GOAL := compile

compile:
	@echo "Compilando... "
	@echo "Arquivo executável de saída:  " $(BIN_OUT)
	$(CC) -o $(BIN_OUT) $(MAIN) $(CFLAGS)

run: compile
	./$(BIN_OUT)

clean:
	@echo "Removendo arquivos .o & .out"
	# Procura todos os arquivos +100 (executáveis) na raiz e subsdiretórios, exceto no .git e DELETA
	find . -perm +100 -type f -not -path "./.git/*" -delete

tests:
	# TODO: Caso seja realizado uma rotina de testes, implementar esta função.
	@echo "Rodando testes...""
	@echo "Ainda não implementado"


