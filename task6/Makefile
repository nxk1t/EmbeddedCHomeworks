CC := gcc
CFLAGS := -Wall -Werror

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
BIN_FILE = DynamicAbonentBase

all: create_dirs $(BIN_DIR)/$(BIN_FILE)

$(BIN_DIR)/$(BIN_FILE): $(OBJ_DIR)/$(BIN_FILE).o $(OBJ_DIR)/libabonentFunctionality.a
	$(CC) $(OBJ_DIR)/$(BIN_FILE).o -o $(BIN_DIR)/$(BIN_FILE) -L$(OBJ_DIR)/  -labonentFunctionality 

$(OBJ_DIR)/libabonentFunctionality.a: $(OBJ_DIR)/aBaseFunctionality.o
	ar cr $(OBJ_DIR)/libabonentFunctionality.a $(OBJ_DIR)/aBaseFunctionality.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -c -o $@

run:
	./$(BIN_DIR)/$(BIN_FILE)

create_dirs:
	mkdir -p bin/
	mkdir -p obj/

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)