CC := gcc
CFLAGS := -Wall -Werror

BIN_DIR := bin
OBJ_DIR := obj
SRC_DIR := src
SERVER_FILE := server
CLIENT_FILE := client

all: create_dirs $(BIN_DIR)/$(SERVER_FILE) $(BIN_DIR)/$(CLIENT_FILE)

$(BIN_DIR)/$(SERVER_FILE): $(OBJ_DIR)/$(SERVER_FILE).o
	$(CC) $(OBJ_DIR)/$(SERVER_FILE).o -o $(BIN_DIR)/$(SERVER_FILE) -lrt

$(BIN_DIR)/$(CLIENT_FILE): $(OBJ_DIR)/$(CLIENT_FILE).o
	$(CC) $(OBJ_DIR)/$(CLIENT_FILE).o -o $(BIN_DIR)/$(CLIENT_FILE) -lrt

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -c -o $@

create_dirs:
	mkdir -p bin/
	mkdir -p obj/

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)