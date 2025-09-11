# run le projet 
### clance le conteneur

./rundev.sh

### lance le run du projet

gcc main.c -o main $(sdl2-config --cflags --libs)
./main