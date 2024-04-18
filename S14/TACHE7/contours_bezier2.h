#ifndef CONTOURS_BEZIER2
#define CONTOURS_BEZIER2
#include "contour_calcul.h"

typedef struct cellule_liste_chainee_bezier2 Cell_Bezier2;
typedef struct cellule_liste_listes_chainee_bezier2 Cell_Liste_Bezier2;

typedef struct cellule_liste_chainee_bezier2 {
    Bezier2 c;
    Cell_Bezier2 *suiv;
} Cell_Bezier2;

typedef struct liste_chainee_bezier2 {
    Cell_Bezier2 *tete;
    Cell_Bezier2 *queue;
    int taille;
} Liste_Bezier2;

typedef struct cellule_liste_listes_chainee_bezier2 {
    Liste_Bezier2 *L;
    Cell_Liste_Bezier2 *suiv;
} Cell_Liste_Bezier2;

typedef struct liste_listes_chainee_bezier2 {
    Cell_Liste_Bezier2 *tete;
    Cell_Liste_Bezier2 *queue;
    int taille;
} Liste_Listes_Bezier2;

/* Initialise une liste de courbes de Bezier de degré 2 vide */
Liste_Bezier2 *initListeBezier2();

/* Initialise une liste de listes de courbes de Bezier de degré 2 vide */
Liste_Listes_Bezier2 *initListeListesBezier2();

void enfilerBezier2(Liste_Bezier2 *L, Bezier2 c);

/* Renvoie la concatenation de L1 et L2, la memoire de L1 et L2 est liberee */
Liste_Bezier2 *concatListeBezier2(Liste_Bezier2 *L1, Liste_Bezier2 *L2);

/* Renvoie l'approximation du contour p1, p2 sous forme d'une courbe de Bezier de degré 2, ainsi que sa longueur n */
Bezier2 approx_bezier2(Cell_Point *p1, Cell_Point *p2);

Liste_Bezier2 *douglasBezier2(Cell_Point *p1, Cell_Point *p2, double d);

Liste_Listes_Bezier2 *simplificationBezier2(Liste_Listes *T, double d);

int ecrireBezier2EPS(FILE *f, Liste_Bezier2 *cont, int ymax);

int ecrireContoursBezier2EPS(FILE *f, Liste_Listes_Bezier2 *T, int xmax, int ymax, bool fill);

#endif //CONTOURS_BEZIER2