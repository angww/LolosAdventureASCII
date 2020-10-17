##
## Instruções de uso do makefile:
## 
## make        : Compila rotina principal
## make run    : Compila rotina principal e roda programa princial
## make tests  : Compila tudo e roda a rotina de testes.
## make clean  : Remove todos os binários e objetos
## variaveis   : Lista variáveis utilizadas internamentes no make.
## git         : Comita e push para o master (Github). Exemplo: make git m="Mensagem do commit"
## help        : Exibe estas mesmas instruções.
##
# Documentação oficial do make em https://www.gnu.org/software/make/manual/make.html

CC = gcc
CFLAGS = -lncurses -Wall
SRC_DIR = ./src/
MAIN = main.c
BIN_OUT = lolosgame.out 

.DEFAULT_GOAL := compile
.PHONY : clean help git


compile:
	@echo "Compilando... "
	@echo "Arquivo executável de saída:  " $(BIN_OUT)
	$(CC) -o $(BIN_OUT) $(SRC_DIR)$(MAIN) $(CFLAGS)

# roda o commando compile antes
run: compile
	@echo "Executando ./$(BIN_OUT)"
	./$(BIN_OUT)



selecionar_opcoes_posicao.out:  $(SRC_DIR)selecionar_opcoes_main_posicao.o $(SRC_DIR)selecionar_opcoes_posicao.o
	$(CC) -o $@ ./$^ $(CFLAGS)

$(SRC_DIR)selecionar_opcoes_main_posicao.o: $(SRC_DIR)selecionar_opcoes_main_posicao.c $(SRC_DIR)selecionar_opcoes_posicao.h
	$(CC) -c $< $(CFLAGS) -o $@

$(SRC_DIR)selecionar_opcoes_posicao.o: $(SRC_DIR)selecionar_opcoes_posicao.c $(SRC_DIR)selecionar_opcoes_posicao.h
	$(CC) -c $< $(CFLAGS) -o $@


variaveis :
	@echo "Listando variáveis:"
	@echo "@:" $@
	@echo "CC:" $(CC)
	@echo "CFLAGS:" $(CFLAGS)
	@echo "MAIN:" $(MAIN)
	@echo "BINOUT:" $(BIN_OUT)
	@echo "SRC: $(SRC)"
	@echo "Wildcard: $(wildcard ./src/*.c)"
	@echo "Função patsubst: $(patsubst ./src/%.c,%.o,$(wildcard ./src/*.c))"
	@echo "Função:" $(SRC:%.c=%.o)
	@echo "SRC_PROTOTIPOS" $(SRC_PROTOTIPOS)



# Procura todos os arquivos +100 (executáveis) na raiz e subsdiretórios, exceto no .git e DELETA
clean:
	@echo "Removendo arquivos executáveis +x"
	find . -perm -u=x -type f -not -path "./.git/*" -print -delete
	@echo "Removendo arquivos tipo objeto *.o"
	find . -type f -name "*.o" -not -path "./.git/*" -print -delete
	@echo "Removendo arquivos *.d"
	find . -type f -name "*.d" -not -path "./.git/*" -print -delete

# TODO: Caso seja realizado uma rotina de testes, implementar esta função.
tests:
	@echo "Rodando testes..."
	@echo "Ainda não implementado."

git:
	git add .
	git commit -m "$m"
	git push -u origin master

help : Makefile
	@sed -n 's/^##//p' $<