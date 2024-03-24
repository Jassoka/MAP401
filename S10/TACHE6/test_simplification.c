#include "contours_simplification.h"
#include "contours_detection.h"

int main(int argc, char **argv) {

    if (argc < 3) {
        printf("Syntaxe: ./%s <nom de fichier.pbm> <distance seuil> <nom de fichier.eps>", argv[0]);
        return 1;
    }

    int n;
    FILE *f;

    Image I = lire_fichier_image(argv[1]);
    Liste_Listes *T_Points; // Contour non simplifié
    T_Points = detectionContours(I);
    

    int xmax = largeur_image(I);
    int ymax = hauteur_image(I);

    f = fopen(argv[3], "w");

    double d = atof(argv[2]);

    Liste_Listes_Segments *T_Segments = simplificationSegment(T_Points, d);

    n = ecrireContoursSegmentsEPS(f, T_Segments, xmax, ymax);
    printf("%s: %d contours, %d segments\n",argv[1], T_Segments->taille, n);

    fclose(f);
}