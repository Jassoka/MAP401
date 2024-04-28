#ifndef CONTOURS_DETECTION
#define CONTOURS_DETECTION
#include "contour_calcul.h"

/* Renvoie l'image masque*/
Image imageMasque(Image I);

/* Renvoie un point candidat, avec l'image masque en argument*/
Point pointCandidat(Image M);

/**/
Liste_Points *calculContour(Image I, Image M);

Liste_Listes *detectionContours(Image I);

/* Renvoie le nombre de segments total */
int ecritureContours(Image I, FILE *f, Liste_Listes *T);

/* Fonction auxiliaire qui ecrit une seule liste dans un fichier EPS */
void ecrireContourEPS(FILE *f, Liste_Points *L, int ymax);

/* Renvoie le nombre de segments total, ecrit completement un fichier EPS (supposé vide) */
int ecritureEPS(FILE *f, Liste_Listes *T, int xmax, int ymax);

#endif