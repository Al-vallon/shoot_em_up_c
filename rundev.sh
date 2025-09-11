#!/bin/bash

IMAGE_NAME=shoot_em_up_dev

# Construire l'image
docker build -t $IMAGE_NAME .

# Variables pour X11
export DISPLAY=host.docker.internal:0
export XDG_RUNTIME_DIR=/tmp/runtime-root
mkdir -p $XDG_RUNTIME_DIR

# Lancer le conteneur avec montage du projet et variables
docker run -it --rm \
    -e DISPLAY=$DISPLAY \
    -e XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR \
    -v "$(pwd -W)":/app \
    $IMAGE_NAME bash
