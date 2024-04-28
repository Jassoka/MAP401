#include <stdio.h>
#include <math.h>
#include "contours_segments.h"

Liste_Segments *initListeSegments() {
    Liste_Segments *L = malloc(sizeof(Liste_Segments));
    if (!L) return NULL; // malloc fail
    L->tete = NULL;
    L->queue = NULL;
    L->taille = 0;
    return L; 
}

Liste_Listes_Segments *initListeListesSegments() {
    Liste_Listes_Segments *L = malloc(sizeof(Liste_Listes_Segments));
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

void enfilerListeSegments(Liste_Listes_Segments *T, Liste_Segments *L) {
    Cell_Liste_Segments *cell = malloc(sizeof(Cell_Liste_Segments));
    cell->L = L;
    cell->suiv = NULL;
    if (!T->tete) {
        T->tete = cell;
        T->queue = cell;
    }
    else {
        T->queue->suiv = cell;
        T->queue = cell;
    }
    T->taille++;
}

Liste_Segments *concatListeSegments(Liste_Segments *L1, Liste_Segments *L2) {
    Liste_Segments *L = initListeSegments();
    L->tete = L1->tete;
    L1->queue->suiv = L2->tete;
    L->queue = L2->queue;
    L->taille = L1->taille + L2->taille;
    free(L1);
    free(L2);
    return L;
}

Liste_Segments *simplificationDouglas(Cell_Point *p1, Cell_Point *p2, double d)
{
    Liste_Segments *L = NULL;
    Segment s = creerSegment(p1->p, p2->p);
    double d_max = 0;
    double d_j;
    Cell_Point *cur = p1->suiv;
    Cell_Point *k;
    while (cur && cur != p2)
    {
        d_j = distancePointSegment(cur->p, s);
        if (d_max < d_j) {
            d_max = d_j;
            k = cur;
        }
        cur = cur->suiv;
    }
    if (d_max-d <= 1e-9) {
        L = initListeSegments();
        enfilerSegment(L, s);
    }
    else {
        Liste_Segments *L1 = simplificationDouglas(p1, k, d);
        Liste_Segments *L2 = simplificationDouglas(k, p2, d);
        L = concatListeSegments(L1, L2);
    }
    return L;
}

Liste_Listes_Segments *simplificationSegment(Liste_Listes *T, double d) {
    Cell_Liste *cell = T->tete;
    Cell_Point *p1;
    Cell_Point *p2;
    Liste_Listes_Segments *T_seg = initListeListesSegments();
    Liste_Segments *L_seg;
    while (cell) {
        p1 = cell->L->tete;
        p2 = cell->L->queue;
        L_seg = simplificationDouglas(p1, p2, d);
        enfilerListeSegments(T_seg, L_seg);
        cell = cell->suiv;
    }
    return T_seg;
}

int ecrireSegmentsEPS(FILE *f, Liste_Segments *cont, int ymax) {
    int n = 0;
    Cell_Segment *curr = cont->tete;

    fprintf(f, "%.0f %.0f moveto\n", xPoint(pointA(curr->s)), ymax - yPoint(pointA(curr->s)));
    while (curr != NULL) {
        fprintf(f, "%.0f %.0f lineto\n", xPoint(pointB(curr->s)), ymax - yPoint(pointB(curr->s)));
        n++;
        curr = curr->suiv;
    }
    fprintf(f, "\n");
    return n;
}


int ecrireContoursSegmentsEPS(FILE *f, Liste_Listes_Segments *T, int xmax, int ymax, bool fill) {
    int n = 0;
    Cell_Liste_Segments *cell = T->tete;

    fprintf(f, "%%!PS−Adobe−3.0 EPSF−3.0\n");
    fprintf(f,"%%%%BoundingBox: 0 0 %u %u\n", xmax, ymax);
    while (cell) {
        n += ecrireSegmentsEPS(f, cell->L, ymax);
        cell = cell->suiv;
    }
    if (fill) fprintf(f, "fill\n");
    else fprintf(f, "stroke\n");
    fprintf(f, "showpage\n");
    return n;
}