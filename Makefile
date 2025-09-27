CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

SRC = src/main.c src/player/player.c src/game/game.c src/enemies/enemies.c src/collision/collision.c src/hud/hud.c src/weapon/weapon.c
OBJ = $(SRC:.c=.o)
BIN = shoot-em-up.exe

INCLUDES = -Isrc -Isrc/player -Isrc/game -Isrc/ship -Isrc/enemies

all: $(BIN)

$(BIN): $(OBJ)
    $(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(BIN) $(LDFLAGS)

%.o: %.c
    $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
    del /Q $(BIN) $(OBJ)