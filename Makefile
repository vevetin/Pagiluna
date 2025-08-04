# Diretórios
INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build
BIN = pagiluna

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I$(INCLUDE_DIR)

# Ajustes conforme sistema operacional
ifeq ($(OS),Windows_NT)
    RM = del /Q /F
    BIN := $(BIN).exe
else
    RM = rm -f
endif

# Fontes e objetos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Alvo padrão
all: $(BIN)

# Linka objetos para criar executável
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compilar arquivos objeto (cria build/ conforme o sistema)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
ifeq ($(OS),Windows_NT)
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
else
	@mkdir -p $(BUILD_DIR)
endif
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos compilados e executável
clean:
ifeq ($(OS),Windows_NT)
	-$(RM) $(OBJS) $(BIN)
else
	-$(RM) $(OBJS) $(BIN)
endif

# Executar programa compilado
run: all
ifeq ($(OS),Windows_NT)
	$(BIN)
else
	./$(BIN)
endif

# Compilar testes (exemplo)
#test:
#ifeq ($(OS),Windows_NT)
#	$(CC) $(CFLAGS) test/testeCatalogo.c src/catalogo.c src/operacoesArvore.c -o test/testeCatalogo.exe
#else
#	$(CC) $(CFLAGS) test/testeCatalogo.c src/catalogo.c src/operacoesArvore.c -o test/testeCatalogo
#endif
#
## Limpar testes compilados
#clean-test:
#ifeq ($(OS),Windows_NT)
#	-del /Q test\testeCatalogo.exe
#else
#	-rm -f test/testeCatalogo
#endif

.PHONY: all clean #run test clean-test
