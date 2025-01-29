MAKEFLAGS += -s

ifeq ($(shell which bash 2>/dev/null),)
  ifeq ($(shell which sh 2>/dev/null),)
    $(error This Makefile cannot be executed in CMD or PowerShell)
  endif
endif

CC := gcc

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXE := $(BIN_DIR)/as
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS := -I$(SRC_DIR) -Wall

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	-rm -rf $(BIN_DIR) $(OBJ_DIR)
