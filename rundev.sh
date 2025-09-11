#!/bin/bash

IMAGE_NAME=shoot_em_up_dev

# Construire l'image
docker build -t $IMAGE_NAME .

# Définir la variable DISPLAY pour Windows
export DISPLAY=host.docker.internal:0

# Lancer le conteneur avec montage du projet et variable DISPLAY
docker run -it --rm -e DISPLAY=$DISPLAY -v "$(pwd -W)":/app $IMAGE_NAME bash
