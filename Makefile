# Makefile pour le jeu Shoot 'Em Up
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lm


SRC = $(shell find src -name "*.c")

# Nom du binaire
BIN = shoot_em_up

# Chemins d'inclusion
INCLUDES = -Isrc -Isrc/player -Isrc/game -Isrc/ship -Isrc/enemies

# Fichiers objets
OBJ = $(SRC:.c=.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(BIN) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(BIN) $(OBJ)
