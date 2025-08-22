CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SRC = $(shell find $(SRC_DIR) -name "*.c")
OBJ = $(patsubst %.c,%.o,$(SRC))
TARGET = baby-shell

.PHONY: all clean

run: build
	./$(BIN_DIR)/$(TARGET)

build: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
