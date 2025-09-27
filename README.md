# run le projet 1
### lance le conteneur

./rundev.sh

### lance le run du projet

gcc main.c -o main $(sdl2-config --cflags --libs)
./main

# Run projet2 SDL2
### lance le contenuer.
./rundev.sh

### créer le binaire shoot_em_up

make

### run shoot_em_up
./shoot_em_up

