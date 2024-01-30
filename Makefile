# Define the compiler
CC=gcc

# Define any compile-time flags
CFLAGS=-Wall -Werror -Wextra -pedantic  -g -I../ -L/usr/lib

# OpenSSL library
LIBS=-lcrypto

# Source files directory
SRC_DIR=./

# Test files directory
TEST_DIR=./test

# Executable files directory
BIN_DIR=./bin

# Source files (excluding main files)
SRCS=$(wildcard $(SRC_DIR)*.c)

# Test source files (main files)
TEST_SRCS=$(wildcard $(TEST_DIR)*-main.c)

# Object files corresponding to source files
OBJS=$(patsubst $(SRC_DIR)%.c, $(BIN_DIR)/%.o, $(SRCS))

# Executable files
EXECS=$(patsubst $(TEST_DIR)/%-main.c, $(BIN_DIR)/%, $(TEST_SRCS))

.PHONY: all clean

all: $(EXECS)

$(BIN_DIR)/%: $(TEST_DIR)/%-main.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BIN_DIR)/%.o: $(SRC_DIR)%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(BIN_DIR)/*

