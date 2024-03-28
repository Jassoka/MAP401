#include <stdio.h>
#include <math.h>
#include "contours_simplification.h"

Liste_Segments *initListeSegments() {
    Liste_Segments *L = malloc(sizeof(Liste_Segments));
    if (!L) return NULL; // malloc fail
    L->tete = NULL;
    L->queue = NULL;
    L->taille = 0;
    return L; 
}

void enfilerSegment(Liste_Segments *L, Segment s) {
    Cell_Segment *cell = malloc(sizeof(Cell_Segment));
    cell->s = s;
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

Liste_Segments *concatListeSegments(Liste_Segments *L1, Liste_Segments *L2) {
    Liste_Segments *L = initListeSegments();
    L->tete = L1->tete;
    L1->queue->suiv = L2->tete;
    L->queue = L2->tete;
    L->taille = L1->taille + L2->taille;
    free(L1);
    free(L2);
    return L;
}

Liste_Segments *simplificationDouglas(Liste_Points *cont, Cell_Point *p1, Cell_Point *p2, double d)
{
    Liste_Segments *L = NULL;
    Segment s = creerSegment(*(p1->p), *(p2->p));
    double d_max = 0;
    double d_j;
    Cell_Point *cur = p1->suiv;
    Cell_Point *k;
    while (cur && cur != p2)
    {
        d_j = distancePointSegment(*(cur->p), s);
        if (d_max < d_j) {
            d_max = d_j;
            k = cur;
        }
        cur = cur->suiv;
    }
    if (d_max < d) {
        L = initListeSegments();
        enfilerSegment(L, s);
    }
    else {
        Liste_Segments *L1 = simplificationDouglas(cont, p1, k, d);
        Liste_Segments *L2 = simplificationDouglas(cont, k, p2, d);
    }
    return L;
}
/*
int ecritureEPS(FILE *f, Liste_Listes *T, int xmax, int ymax) {
    Cell_Liste *cell = T->tete;
    int n = 0;

    fprintf(f, "%%!PS−Adobe−3.0 EPSF−3.0\n");
    fprintf(f,"%%%%BoundingBox: 0 0 %u %u\n", xmax, ymax);
    while (cell) {
        ecrireContourEPS(f, cell->L, ymax);
        n += cell->L->taille - 1; // Nombre de segments
        cell = cell->suiv;
    }
    fprintf(f, "fill\n");
    fprintf(f, "showpage\n");

    return n;
}
*/