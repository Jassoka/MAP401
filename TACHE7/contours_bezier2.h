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

/* Enfile une courbe de degré 2 en fin de liste */
void enfilerBezier2(Liste_Bezier2 *L, Bezier2 c);

/* Renvoie la concatenation de L1 et L2, la memoire de L1 et L2 est liberee */
Liste_Bezier2 *concatListeBezier2(Liste_Bezier2 *L1, Liste_Bezier2 *L2);

/* Renvoie l'approximation du contour p1, p2 sous forme d'une courbe de Bezier de degré 2, ainsi que sa longueur n */
Bezier2 approx_bezier2(Cell_Point *p1, Cell_Point *p2);

/* Algorithme de Douglas-Peucker de degré 2 */
Liste_Bezier2 *douglasBezier2(Cell_Point *p1, Cell_Point *p2, double d);

/* Simplifie une liste de contours T en liste de courbes de degré 2 */
Liste_Listes_Bezier2 *simplificationBezier2(Liste_Listes *T, double d);

/* Ecris un contour de courbes de Bezier 2 cont dans un fichier f en lecture, sous format EPS */
int ecrireBezier2EPS(FILE *f, Liste_Bezier2 *cont, int ymax);

/* Ecris tous les contours de courbes de Bezier 2 dans un fichier f en lecture, sous format EPS */
int ecrireContoursBezier2EPS(FILE *f, Liste_Listes_Bezier2 *T, int xmax, int ymax, bool fill);

#endif //CONTOURS_BEZIER2