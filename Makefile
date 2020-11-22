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

# Flags para o compilador
CFLAGS=-lncurses -Wall
# Diretório onde estão os arquivos a serem compilados
SRC_DIR=./src/
# Arquivo de saída
BIN_OUT=lolosgame.out
# Diretório de saída
OUT_DIR=bin/
# Diretório onde está os niveis
NIVEIS_DIR=niveis/
# Arquivos fonte
SRCS=$(wildcard $(SRC_DIR)*.c)
# Arquivos objeto
OBJS=$(SRCS:.c=.o)

# Configura a ação padrão
.DEFAULT_GOAL := compile
.PHONY : clean

# Compila, depende de OBJS para compilar
compile: $(OBJS)
	@# Cria pasta necessárias, caso não existam
	@mkdir -vp $(OUT_DIR)
	@mkdir -vp $(OUT_DIR)$(NIVEIS_DIR)
	@# Copia os niveis para o dirétorio desejado
	@# Recursivo, verboso e sobreescreve caso já exista
	@cp -rfv $(SRC_DIR)$(NIVEIS_DIR)* $(OUT_DIR)$(NIVEIS_DIR)
	@# Compila main para o diretório desejado
	$(CC) $(CFLAGS) -o $(OUT_DIR)$(BIN_OUT) $(OBJS)

# Se executar o compile, irá copiar todos os arquivos novamente
run: compile
	@echo "Executando $(OUT_DIR)$(BIN_OUT)"
	@cd $(OUT_DIR) ; ./$(BIN_OUT)

# Para cada objeto, usa sua fonte
OBJS: SRCS
	$(CC) -c $@ $< $(CFLAGS)

# Remove os objetos
clean:
	@echo "Removendo arquivos .o"
	rm -f $(OBJS)
