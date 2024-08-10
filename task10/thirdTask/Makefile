CC := gcc
CFLAGS := -Wall -Werror

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
BIN_FILE = main
LIB_NAME = bashFunc

all: create_dirs $(BIN_DIR)/$(BIN_FILE)

$(BIN_DIR)/$(BIN_FILE): $(OBJ_DIR)/$(BIN_FILE).o $(OBJ_DIR)/lib$(LIB_NAME).a
	$(CC) $(OBJ_DIR)/$(BIN_FILE).o -o $(BIN_DIR)/$(BIN_FILE) -L$(OBJ_DIR)/  -l$(LIB_NAME)

$(OBJ_DIR)/lib$(LIB_NAME).a: $(OBJ_DIR)/functionality.o
	ar cr $(OBJ_DIR)/lib$(LIB_NAME).a $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -g $(CFLAGS) $< -c -o $@

run:
	./$(BIN_DIR)/$(BIN_FILE)

create_dirs:
	mkdir -p bin/
	mkdir -p obj/

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)