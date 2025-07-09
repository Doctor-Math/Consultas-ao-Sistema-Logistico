# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

# Nome do executável
EXEC = tp3.out

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -I$(INC_DIR)

# Lista de arquivos fonte
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Transforma os .cpp em .o (obj/arquivo.o)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Regra padrão
all: $(BIN_DIR)/$(EXEC)

# Regra para gerar o executável
$(BIN_DIR)/$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar os arquivos fonte
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpa binários e objetos
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/$(EXEC)

# Cria as pastas se não existirem (opcional)
init:
	mkdir -p $(SRC_DIR) $(OBJ_DIR) $(BIN_DIR) $(INC_DIR)

.PHONY: all clean init