# Makefile pour le jeu Shoot 'Em Up
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`


SRC = $(shell find src -name "*.c")

# Nom du binaire
BIN = shoot_em_up

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN) $(LDFLAGS)

clean:
	rm -f $(BIN)
