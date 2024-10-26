CC = gcc
CFLAGS = -Iinclude
SRC_DIR = src
BUILD_DIR = build
BIN = space-invaders

# Encontrar todos os arquivos .c na pasta src
SRC = $(wildcard $(SRC_DIR)/*.c)

# Criar os arquivos objeto correspondentes na pasta build
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Regra padrão
all: $(BUILD_DIR) $(BIN)

# Linkar os arquivos objeto para criar o executável
$(BIN): $(OBJ)
	$(CC) -o $@ $^

# Criar os arquivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Limpar os arquivos gerados
clean:
	rm -rf $(BUILD_DIR)/*.o $(BIN)

# Criar o diretório de build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Executar o programa
run: $(BIN)
	./$(BIN)

.PHONY: all clean run