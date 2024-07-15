CC := gcc
CFLAGS := -Wall -Werror

BIN_DIR := bin
OBJ_DIR := obj
SRC_DIR := src
BIN_FILE := main

CUR_DIR := $(PWD)
LIB_PATH := $(LD_LIBRARY_PATH)

all: create_dirs $(BIN_DIR)/$(BIN_FILE)

$(BIN_DIR)/$(BIN_FILE): $(OBJ_DIR)/$(BIN_FILE).o $(OBJ_DIR)/libcalc.so
	$(CC) $(OBJ_DIR)/$(BIN_FILE).o -o $(BIN_DIR)/$(BIN_FILE) -L$(OBJ_DIR)/  -lcalc

$(OBJ_DIR)/libcalc.so: $(OBJ_DIR)/add.o $(OBJ_DIR)/sub.o $(OBJ_DIR)/mul.o $(OBJ_DIR)/div.o 
	$(CC) -shared $^ -o $(OBJ_DIR)/libcalc.so

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -fPIC -c -o $@

run:
	LD_LIBRARY_PATH=$(CUR_DIR)/$(OBJ_DIR)/:$(LIB_PATH) ./$(BIN_DIR)/$(BIN_FILE)

create_dirs:
	mkdir -p bin/
	mkdir -p obj/

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)