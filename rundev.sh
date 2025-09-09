#!/bin/bash

IMAGE_NAME=shoot_em_up_dev

# Construire l'image si elle n'existe pas
docker build -t $IMAGE_NAME .

# Monter le dossier local dans Docker en gérant les espaces
docker run -it --rm -v "$(pwd -W)":/app $IMAGE_NAME bash
