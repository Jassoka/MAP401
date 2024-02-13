#ifndef CONTOURS_DETECTION
#define CONTOURS_DETECTION
#include "contour_calcul.h"


Image imageMasque(Image I);

Point pointCandidat(Image M);

Liste_Points *calculContour(Image I, Image M);

Liste_Listes *detectionContours(Image I);

/* Renvoie le nombre de segments total */
int ecritureContours(Image I, FILE *f, Liste_Listes *T);

#endif