CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
AR = ar
ARFLAGS = rcs

LIB_DIR = lib
SRC_DIR = src
BUILD_DIR = build

LIB_INCLUDE = $(LIB_DIR)/include
LIB_SRC = $(LIB_DIR)/src/thread.c
LIB_OBJ = $(LIB_DIR)/build/thread.o
LIB_OUTPUT = $(LIB_DIR)/libthread.a

APP_SRC = $(SRC_DIR)/main.c
APP_OBJ = $(BUILD_DIR)/main.o
APP_OUTPUT = $(BUILD_DIR)/main

all: $(LIB_OUTPUT) $(APP_OUTPUT)

$(LIB_OUTPUT): $(LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(LIB_OBJ): $(LIB_SRC) | $(LIB_DIR)/build
	$(CC) $(CFLAGS) -I$(LIB_INCLUDE) -c $< -o $@

$(APP_OUTPUT): $(APP_OBJ) $(LIB_OUTPUT)
	$(CC) $< -o $@ -L$(LIB_DIR) -lthread

$(APP_OBJ): $(APP_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIB_INCLUDE) -c $< -o $@

$(LIB_DIR)/build:
	mkdir -p $(LIB_DIR)/build

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(LIB_DIR)/build $(LIB_OUTPUT) $(BUILD_DIR)

run: $(APP_OUTPUT)
	./$(APP_OUTPUT)

.PHONY: all clean run
