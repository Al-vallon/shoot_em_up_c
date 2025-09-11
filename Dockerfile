FROM gcc:13

WORKDIR /app

# Installer SDL2 et outils X11
RUN apt-get update && apt-get install -y \
    libsdl2-dev \
    libsdl2-image-dev \
    libsdl2-ttf-dev \
    libsdl2-mixer-dev \
    x11-apps \
    && rm -rf /var/lib/apt/lists/*

# Optionnel : installer make si tu veux l'utiliser dans le conteneur
RUN apt-get update && apt-get install -y make
