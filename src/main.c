#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>    // strlen()
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define WIDTH 20
#define HEIGHT 60
#define MAX_MISSILES 5
#define MAX_ENEMIES 5

// --- Fonctions Linux pour lecture clavier non bloquante ---
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

char getch(void) {
    char c;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    c = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

// --- Génération des ennemis ---
void spawn_enemies(int enemy_x[], int enemy_y[], int active[]) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!active[i]) { // si inactif
            enemy_x[i] = rand() % WIDTH;
            enemy_y[i] = rand() % (HEIGHT / 2); // en haut
            active[i] = 1;
        }
    }
}

int main() {
    char *vaisseau = "^_^";
    int x = (WIDTH - strlen(vaisseau)) / 2;
    int y = HEIGHT - 1;
    char input;

    int missile_x[MAX_MISSILES];
    int missile_y[MAX_MISSILES];
    int missile_active[MAX_MISSILES];

    for(int i = 0; i < MAX_MISSILES; i++) {
        missile_active[i] = 0;
    }

    int enemy_x[MAX_ENEMIES] = {0};
    int enemy_y[MAX_ENEMIES] = {0};
    int enemy_active[MAX_ENEMIES] = {0};
    int enemy_timer = 0;

    srand(time(NULL));

    // Spawn initial des ennemis
    spawn_enemies(enemy_x, enemy_y, enemy_active);

    while (1) {
        system("clear"); // Pour Windows utilisez "cls"

        // --- Déplacement missiles ---
        for (int m = 0; m < MAX_MISSILES; m++) {
            if (missile_active[m]) {
                missile_y[m]--;
                if (missile_y[m] < 0) {
                    missile_active[m] = 0; // missile hors écran
                }
            }
        }

        // --- Incrémentation du timer pour les ennemis ---
        enemy_timer++;

        // --- Déplacement ennemis ---
        if (enemy_timer >= 200) { // tous les 200 cycles
            for (int e = 0; e < MAX_ENEMIES; e++) {
                if (enemy_active[e]) {
                    enemy_y[e]++;
                    if (enemy_y[e] >= HEIGHT) {
                        enemy_active[e] = 0; // ennemi hors écran
                    }
                    // Collision avec le vaisseau
                    if (enemy_y[e] == y && enemy_x[e] >= x && enemy_x[e] < x + strlen(vaisseau)) {
                        printf("Game Over! Vous avez été touché!\n");
                        return 0;
                    }
                }
            }
            enemy_timer = 0;
        }

        // --- Collision missiles <-> ennemis ---
        for (int m = 0; m < MAX_MISSILES; m++) {
            if (missile_active[m]) {
                for (int e = 0; e < MAX_ENEMIES; e++) {
                    if (enemy_active[e] &&
                        missile_y[m] == enemy_y[e] &&
                        missile_x[m] == enemy_x[e]) {
                        enemy_active[e] = 0;    // ennemi détruit
                        missile_active[m] = 0; // missile disparait
                    }
                }
            }
        }

        // --- Affichage de la grille ---
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                int printed = 0;

                // Missile
                for (int m = 0; m < MAX_MISSILES; m++) {
                    if (missile_active[m] && missile_y[m] == i && missile_x[m] == j) {
                        printf("|");
                        printed = 1;
                        break;
                    }
                }

                // Vaisseau
                if (!printed && i == y && j >= x && j < x + strlen(vaisseau)) {
                    printf("%c", vaisseau[j - x]);
                    printed = 1;
                }

                // Ennemis
                if (!printed) {
                    for (int e = 0; e < MAX_ENEMIES; e++) {
                        if (enemy_active[e] && enemy_x[e] == j && enemy_y[e] == i) {
                            printf("X");
                            printed = 1;
                            break;
                        }
                    }
                }

                if (!printed) printf(".");
            }
            printf("\n");
        }

        // --- Lecture clavier ---
        if (kbhit()) {
            input = getch();

            if (input == 'q' && x > 0) x--;          // gauche
            if (input == 'd' && x < WIDTH - strlen(vaisseau)) x++; // droite
            if (input == 'z' && y > 0) y--;          // haut
            if (input == 's' && y < HEIGHT - 1) y++; // bas
            if (input == 27) break;                  // échap
            if (input == ' ') {                       // tir
                for (int m = 0; m < MAX_MISSILES; m++) {
                    if (!missile_active[m]) {
                        missile_x[m] = x + strlen(vaisseau)/2;
                        missile_y[m] = y - 1;
                        missile_active[m] = 1;
                        break;
                    }
                }
            }
        }

        usleep(50000); // 20 fps
    }


    printf("Game Over\n");
    return 0;
}
// Note: This project uses the C language standard version.