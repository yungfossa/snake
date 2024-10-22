# Compiler
CC := gcc

# Compiler flags
CFLAGS := -O2 -std=c99 --pedantic -Wall -Wextra -Iinclude

# Include directories
INCLUDE := -I include

# Directories
SRC_DIR := src
OBJ_DIR := obj
EXE_DIR := build
DOCS_DIR := docs

# Executable
EXE :=$(EXE_DIR)/snake

# Targets and dependencies
snake: main.o points_list.o entities.o moves_list.o maze.o game.o graphics.o
	mkdir -p $(EXE_DIR)
	$(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/points_list.o $(OBJ_DIR)/moves_list.o $(OBJ_DIR)/entities.o $(OBJ_DIR)/maze.o $(OBJ_DIR)/game.o $(OBJ_DIR)/graphics.o -lm $(CFLAGS) -o $(EXE)
	doxygen

main.o:
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(SRC_DIR)/main.c $(INCLUDE) $(CFLAGS) -o $(OBJ_DIR)/main.o

points_list.o:
	$(CC) -c $(SRC_DIR)/points_list.c $(INCLUDE) $(CFLAGS) -o $(OBJ_DIR)/points_list.o

moves_list.o:
	$(CC) -c $(SRC_DIR)/moves_list.c $(INCLUDE) $(CFLAGS) -o $(OBJ_DIR)/moves_list.o

maze.o:
	$(CC) -c $(SRC_DIR)/maze.c $(INCLUDE) $(CFLAGS) -o $(OBJ_DIR)/maze.o

entities.o:
	$(CC) -c $(SRC_DIR)/entities.c $(INCLUDE) $(CFLAGS) -o $(OBJ_DIR)/entities.o

game.o:
	$(CC) -c $(SRC_DIR)/game.c $(INCLUDE) $(CFLAGS) -o $(OBJ_DIR)/game.o

graphics.o:
	$(CC) -c $(SRC_DIR)/graphics.c $(INCLUDE) $(CFLAGS) -o $(OBJ_DIR)/graphics.o

clean:
	rm -rf $(OBJ_DIR) $(EXE_DIR) $(DOCS_DIR)

