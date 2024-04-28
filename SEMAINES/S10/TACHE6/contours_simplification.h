#ifndef CONTOURS_SIMPLIFICATION
#define CONTOURS_SIMPLIFICATION
#include "contour_calcul.h"

typedef struct cellule_liste_chainee_segments Cell_Segment;

typedef struct cellule_liste_chainee_segments {
    Segment s;
    Cell_Segment *suiv;
} Cell_Segment;

typedef struct liste_chainee_segments {
    Cell_Segment *tete;
    Cell_Segment *queue;
    int taille;
} Liste_Segments;

Liste_Segments *initListeSegments();

void enfilerSegment(Liste_Segments *L, Segment s);

/* Renvoie la concatenation de L1 et L2, la memoire de L1 et L2 est liberee */
Liste_Segments *concatListeSegments(Liste_Segments *L1, Liste_Segments *L2);

Liste_Segments *simplificationDouglas(Liste_Points *cont, Cell_Point *p1, Cell_Point *p2, double d);

#endif