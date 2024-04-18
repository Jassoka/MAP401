#ifndef CONTOURS_BEZIER3
#define CONTOURS_BEZIER3
#include "contour_calcul.h"

typedef struct cellule_liste_chainee_bezier3 Cell_Bezier3;
typedef struct cellule_liste_listes_chainee_bezier3 Cell_Liste_Bezier3;

typedef struct cellule_liste_chainee_bezier3 {
    Bezier3 c;
    Cell_Bezier3 *suiv;
} Cell_Bezier3;

typedef struct liste_chainee_bezier3 {
    Cell_Bezier3 *tete;
    Cell_Bezier3 *queue;
    int taille;
} Liste_Bezier3;

typedef struct cellule_liste_listes_chainee_bezier3 {
    Liste_Bezier3 *L;
    Cell_Liste_Bezier3 *suiv;
} Cell_Liste_Bezier3;

typedef struct liste_listes_chainee_bezier3 {
    Cell_Liste_Bezier3 *tete;
    Cell_Liste_Bezier3 *queue;
    int taille;
} Liste_Listes_Bezier3;

/* Initialise une liste de courbes de Bezier de degré 3 vide */
Liste_Bezier3 *initListeBezier3();

/* Initialise une liste de listes de courbes de Bezier de degré 3 vide */
Liste_Listes_Bezier3 *initListeListesBezier3();

void enfilerBezier3(Liste_Bezier3 *L, Bezier3 c);

/* Renvoie la concatenation de L1 et L2, la memoire de L1 et L2 est liberee */
Liste_Bezier3 *concatListeBezier3(Liste_Bezier3 *L1, Liste_Bezier3 *L2);

double gamma_bez(int k, int n);

/* Renvoie l'approximation du contour p1, p2 sous forme d'une courbe de Bezier de degré 3, ainsi que sa longueur n */
Bezier3 approx_bezier3(Cell_Point *p1, Cell_Point *p2);

Liste_Bezier3 *douglasBezier3(Cell_Point *p1, Cell_Point *p2, double d);

Liste_Listes_Bezier3 *simplificationBezier3(Liste_Listes *T, double d);

int ecrireBezier3EPS(FILE *f, Liste_Bezier3 *cont, int ymax);

int ecrireContoursBezier3EPS(FILE *f, Liste_Listes_Bezier3 *T, int xmax, int ymax, bool fill);

#endif //CONTOURS_BEZIER3