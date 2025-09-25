#include <stdlib.h>
#include <stdio.h>
#include "weapon.h"

// head of the missile list
Missile* listeMissiles = NULL;

void tirerMissile(float x, float y) {
    Missile* nouveau = (Missile*)malloc(sizeof(Missile));
    if (!nouveau) {
        perror("Erreur malloc missile");
        return;
    }
    nouveau->x = x;
    nouveau->y = y;
    nouveau->actif = 1;
    nouveau->suivant = listeMissiles; // push front
    listeMissiles = nouveau;
}

void majMissiles() {
    Missile *courant = listeMissiles;
    Missile *precedent = NULL;

    while (courant) {
        if (courant->actif) {
            courant->y -= 5.0f; // missile speed upwards
            if (courant->y < -10.0f) {
                courant->actif = 0; // mark for removal
            }
        }

        if (!courant->actif) {
            Missile *aSupprimer = courant;
            if (precedent == NULL) {
                listeMissiles = courant->suivant;
                courant = listeMissiles;
            } else {
                precedent->suivant = courant->suivant;
                courant = courant->suivant;
            }
            free(aSupprimer);
        } else {
            precedent = courant;
            courant = courant->suivant;
        }
    }
}

void dessinerMissiles(SDL_Renderer *renderer) {
    if (!renderer) return;
    Missile *m = listeMissiles;
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // yellow
    while (m) {
        if (m->actif) {
            SDL_Rect r = { (int)m->x - 2, (int)m->y - 8, 4, 8 };
            SDL_RenderFillRect(renderer, &r);
        }
        m = m->suivant;
    }
}

void detruireMissiles() {
    Missile *m = listeMissiles;
    while (m) {
        Missile *tmp = m;
        m = m->suivant;
        free(tmp);
    }
    listeMissiles = NULL;
}