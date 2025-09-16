#!/bin/bash

IMAGE_NAME=shoot_em_up_dev

# Construire l'image
docker build -t $IMAGE_NAME .

# Variables pour X11
export DISPLAY=host.docker.internal:0
export XDG_RUNTIME_DIR=/tmp/runtime-root
mkdir -p $XDG_RUNTIME_DIR

# Ajout de valgrind au lancement
# Lancer le conteneur avec valgrind
if [ "$1" == "valgrind" ]; then
    docker run -it --rm \
        -e DISPLAY=$DISPLAY \
        -e XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR \
        -v "$(pwd -W)":/app \
        $IMAGE_NAME valgrind ./shoot_em_up
else
    # Lancer le conteneur normalement
    docker run -it --rm \
        -e DISPLAY=$DISPLAY \
        -e XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR \
        -v "$(pwd -W)":/app \
        $IMAGE_NAME bash
fi

# Ajout d'une option pour optimiser les fichiers PNG
if [ "$1" == "optimize" ]; then
    docker run -it --rm \
        -v "$(pwd -W)":/app \
        $IMAGE_NAME optipng -o7 assets/sprite/ship/*.png
    exit 0
fi
