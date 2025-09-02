CC = gcc
BUILD_MODE ?= debug

CFLAGS = -Wall -Wextra
ifeq ($(BUILD_MODE), release)
	CFLAGS += -O2
else
	CFLAGS += -g
endif

LDFLAGS =
SRC_DIR = src
BIN_DIR = bin
SRC = $(shell find $(SRC_DIR) -name "*.c")
OBJ = $(patsubst %.c,%.o,$(SRC))
TARGET = $(shell basename $(CURDIR))

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
	git clean -Xdf
