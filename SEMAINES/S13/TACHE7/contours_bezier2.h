#ifndef CONTOURS_BEZIER2
#define CONTOURS_BEZIER2
#include "contours_segments.h"

typedef struct cellule_liste_chainee_bezier2 Cell_Bezier2;
typedef struct cellule_liste_listes_chainee_bezier2 Cell_Liste_Bezier2;

typedef struct cellule_liste_chainee_bezier {
    Bezier2 c;
    Cell_Bezier2 *suiv;
} Cell_Bezier2;

typedef struct liste_chainee_bezier {
    Cell_Bezier2 *tete;
    Cell_Bezier2 *queue;
    int taille;
} Liste_Bezier2;

typedef struct cellule_liste_listes_chainee_bezier {
    Liste_Bezier2 *L;
    Cell_Liste_Bezier2 *suiv;
} Cell_Liste_Bezier2;

typedef struct liste_listes_chainee_bezier {
    Cell_Liste_Bezier2 *tete;
    Cell_Liste_Bezier2 *queue;
    int taille;
} Liste_Listes_Bezier2;

/* Initialise une liste de courbes de Bezier de degré 2 vide */
Liste_Bezier2 *initListeBezier2();

/* Initialise une liste de listes de courbes de Bezier de degré 2 vide */
Liste_Listes_Bezier2 *initListeListesBezier2();


#endif CONTOURS_BEZIER2