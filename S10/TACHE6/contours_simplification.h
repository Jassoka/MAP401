#ifndef CONTOURS_SIMPLIFICATION
#define CONTOURS_SIMPLIFICATION
#include "contour_calcul.h"

typedef struct cellule_liste_chainee_segments Cell_Segment;
typedef struct cellule_liste_listes_chainee_segments Cell_Liste_Segments;

typedef struct cellule_liste_chainee_segments {
    Segment s;
    Cell_Segment *suiv;
} Cell_Segment;

typedef struct liste_chainee_segments {
    Cell_Segment *tete;
    Cell_Segment *queue;
    int taille;
} Liste_Segments;

typedef struct cellule_liste_listes_chainee_segments {
    Liste_Segments *L;
    Cell_Liste_Segments *suiv;
} Cell_Liste_Segments;

typedef struct liste_listes_chainee_segments {
    Cell_Liste_Segments *tete;
    Cell_Liste_Segments *queue;
    int taille;
} Liste_Listes_Segments;

/* Initialise une liste de segments vide */
Liste_Segments *initListeSegments();

/* Initialise une liste de listes de segments vide */
Liste_Listes_Segments *initListeListesSegments();

/* Enfile un segment en queue d'une liste de segments */
void enfilerSegment(Liste_Segments *L, Segment s);

/* Enfile une liste de segments en queue de liste de liste de segments */
void enfilerListeSegments(Liste_Listes_Segments *T, Liste_Segments *L);

/* Renvoie la concatenation de L1 et L2, la memoire de L1 et L2 est liberee */
Liste_Segments *concatListeSegments(Liste_Segments *L1, Liste_Segments *L2);

/* Renvoie la simplification par segments a partir du point p1, jusqu'au point p2, avec une distance seuil d */
Liste_Segments *simplificationDouglas(Cell_Point *p1, Cell_Point *p2, double d);

/* Renvoie la liste des contours apres une simplification par segment, a partir d'une liste de contours T */
Liste_Listes_Segments *simplificationSegment(Liste_Listes *T, double d);

int ecrireSegmentsEPS(FILE *f, Liste_Segments *cont, int ymax);

int ecrireContoursSegmentsEPS(FILE *f, Liste_Listes_Segments *T, int xmax, int ymax);

#endif