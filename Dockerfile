FROM gcc:13

WORKDIR /app

RUN apt-get update && apt-get install -y \
    libsdl2-dev \
    libsdl2-image-dev \
    libsdl2-ttf-dev \
    libsdl2-mixer-dev \
    x11-apps \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y make
