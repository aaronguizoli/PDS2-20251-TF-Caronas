CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
LDFLAGS =

# Diretórios
BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests

# Executável principal
APP_NAME = ufmg_carona_app

# Executável de testes
TEST_APP_NAME = ufmg_carona_tests

# Arquivos de objeto
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Regra padrão
all: dirs $(BIN_DIR)/$(APP_NAME)

dirs:
	mkdir -p $(BIN_DIR) $(OBJ_DIR) $(TEST_DIR)

# Compilação do aplicativo principal
$(BIN_DIR)/$(APP_NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Regra para compilar e rodar os testes
# Usa filter-out para excluir obj/main.o da lista de objetos vinculados para o executável de teste
TEST_LINK_OBJS = $(filter-out $(OBJ_DIR)/main.o,$(OBJS))

test: dirs $(OBJ_DIR)/testes.o $(TEST_LINK_OBJS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $(OBJ_DIR)/testes.o $(TEST_LINK_OBJS) -o $(BIN_DIR)/$(TEST_APP_NAME) $(LDFLAGS)
	./$(BIN_DIR)/$(TEST_APP_NAME)

$(OBJ_DIR)/testes.o: $(TEST_DIR)/testes.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Regra para rodar o aplicativo principal
run: $(BIN_DIR)/$(APP_NAME)
	./$(BIN_DIR)/$(APP_NAME)

# Limpeza
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: all clean run test dirs