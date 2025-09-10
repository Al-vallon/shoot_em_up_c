#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>    // strlen()
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define WIDTH 20
#define HEIGHT 60
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

    int missile_x = -1;
    int missile_y = -1;

    int enemy_x[MAX_ENEMIES] = {0};
    int enemy_y[MAX_ENEMIES] = {0};
    int enemy_active[MAX_ENEMIES] = {0};
    int enemy_timer = 0;

    srand(time(NULL));

    // Spawn initial des ennemis
    spawn_enemies(enemy_x, enemy_y, enemy_active);

    while (1) {
        system("clear"); // Pour Windows utilisez "cls"

        // Déplacement missile
        if (missile_y >= 0) {
            missile_y--;
            if (missile_y < 0) missile_x = -1; // missile hors écran
        }

        // incrémentation du timer pour la descente des ennemis
        enemy_timer++;


        // Déplacement ennemis
        if (enemy_timer >= 40) { // tous les 40 cycles
            for (int i = 0; i < MAX_ENEMIES; i++) {
                if (enemy_active[i]) {
                    enemy_y[i]++;
                    if (enemy_y[i] >= HEIGHT) {
                        enemy_active[i] = 0; // ennemi hors écran
                    }
                    // Collision avec le vaisseau
                    if (enemy_y[i] == y && enemy_x[i] >= x && enemy_x[i] < x + strlen(vaisseau)) {
                        printf("Game Over! Vous avez été touché!\n");
                        return 0;
                    }
                    // Collision avec le missile
                    if (missile_y == enemy_y[i] && missile_x == enemy_x[i]) {
                        enemy_active[i] = 0; // ennemi détruit
                        missile_x = -1;     // missile disparait
                    }

                    if (enemy_active[i] && missile_y == enemy_y[i] && missile_x == enemy_x[i]) {
                        enemy_active[i] = 0; // ennemi détruit
                        missile_x = -1;     // missile disparait
                    }
            }
            enemy_timer = 0;
        }
    }




        // Affichage de la grille
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                int printed = 0;

                // Missile
                if (i == missile_y && j == missile_x) {
                    printf("|");
                    printed = 1;
                }
                // Vaisseau
                else if (i == y && j >= x && j < x + strlen(vaisseau)) {
                    printf("%c", vaisseau[j - x]);
                    printed = 1;
                }
                // Ennemis
                else {
                    for (int k = 0; k < MAX_ENEMIES; k++) {
                        if (enemy_active[k] && enemy_x[k] == j && enemy_y[k] == i) {
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

        // Lecture clavier
        if (kbhit()) {
            input = getch();

            if (input == 'q' && x > 0) x--;          // gauche
            if (input == 'd' && x < WIDTH - strlen(vaisseau)) x++; // droite
            if (input == 'z' && y > 0) y--;          // haut
            if (input == 's' && y < HEIGHT - 1) y++; // bas
            if (input == 27) break;                  // échap
            if (input == ' ') {                       // tir
                missile_x = x + strlen(vaisseau)/2;  // centre du vaisseau
                missile_y = y - 1;
            }
        }

        usleep(50000); // 20fps
    }

    printf("Game Over\n");
    return 0;
}
// Note: This project uses the C language standard version.