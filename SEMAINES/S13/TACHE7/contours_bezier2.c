#include <stdio.h>
#include <math.h>
#include "contours_bezier2.h"

Liste_Bezier2 *initListeBezier2() {
    Liste_Bezier2 *L = malloc(sizeof(Liste_Bezier2));
    if (!L) return NULL; // malloc fail
    L->tete = NULL;
    L->queue = NULL;
    L->taille = NULL
}

Liste_Listes_Bezier2 *initListeListesBezier2() {
    Liste_Listes_Bezier2 *T = malloc(sizeof(Liste_Listes_Bezier2));
    if (!T) return NULL; // malloc fail
    T->tete = NULL;
    T->queue = NULL;
    T->taille = 0;
    return T; 
}

void enfilerBezier2(Liste_Bezier2 *L, Bezier2 c) {
    Cell_Bezier2 *cell = malloc(sizeof(Cell_Bezier2));
    cell->c = c;
    cell->suiv = NULL;
    if (!L->tete) {
        L->tete = cell;
        L->queue = cell;
    }
    else {
        L->queue->suiv = cell;
        L->queue = cell;
    }
    L->taille++;
}
