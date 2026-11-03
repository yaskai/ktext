# Compiler and flags
CC := gcc
CFLAGS := -Wall -std=c99 -Ilibs/raylib/build/raylib 
LDFLAGS := -lm -ldl -lpthread -lGL -lrt -lX11

APP_NAME := ktext

# Paths
SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin
RAYLIB_DIR := libs/raylib/build/raylib
RAYLIB_LIB := $(RAYLIB_DIR)/libraylib.a

# Sources and objects
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Output executable
TARGET := $(BIN_DIR)/$(APP_NAME)

.PHONY: all clean directories

all: directories $(TARGET)

# Link, using explicit path to libraylib.a (no -lraylib)
$(TARGET): $(OBJS) 
	$(CC) $^ -o $@ $(RAYLIB_LIB) $(LDFLAGS)

# Compile .c to .o in build/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | directories
	$(CC) $(CFLAGS) -c $< -o $@

# Create build and bin dirs if missing
directories:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/*

