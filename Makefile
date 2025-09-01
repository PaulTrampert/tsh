CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =
SRC_DIR = src
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

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR) src/grammar/rules/*.o src/grammar/*.o src/*.o
