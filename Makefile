CC = gcc
CFLAGS=-c -lm -pedantic
MAIN = $(wildcard SourceCode/main_code/*.c)
SRC = $(wildcard SourceCode/libs_souce_code/*.c)
OBJ = $(wildcard Objects/*.o)
DEPS = $(wildcard SourceCode/libs_h/*.h)
OUT = Objects/
LIBS_C_IN = SourceCode/libs_source_code/
MAIN_C_IN = SourceCode/main_code/
EXE = exe

all: CreateFolder Compile GenExe

Compile: $(SRC) $(MAIN) $(DEPS)
	@$(CC) -o $(OUT)tArquivos.o $(LIBS_C_IN)tArquivos.c $(CFLAGS)
	@$(CC) -o $(OUT)tEstatisticas.o $(LIBS_C_IN)tEstatisticas.c $(CFLAGS)
	@$(CC) -o $(OUT)tPosicoes.o $(LIBS_C_IN)tPosicoes.c $(CFLAGS)
	@$(CC) -o $(OUT)tMainSnake.o $(LIBS_C_IN)tMainSnake.c $(CFLAGS)
	@$(CC) -o $(OUT)main.o $(MAIN_C_IN)main.c $(CFLAGS)
	@echo compilado objetos!

GenExe:
	@$(CC) -o $(IN)$(EXE) $(OBJ) -lm
	@echo compilado executavel!

PlayMap1:
	@./$(EXE) Maps/1

PlayMap2:
	@./$(EXE) Maps/2
	
PlayMap3:
	@./$(EXE) Maps/3

CreateFolder:
	@mkdir -p Objects

clear:
	@rm -rf Objects && rm $(IN)exe