#include "contours_segments.h"
#include "contours_detection.h"

int main(int argc, char **argv) {

    if (argc < 4) {
        printf("Syntaxe: %s <nom de fichier.pbm> <distance seuil> <nom de fichier.eps> (s)\n", argv[0]);
        return 1;
    }
    bool fill = true;
    if (argc > 4 && argv[4][0] == 's')
    {
        fill = false; // 4e argument optionnel stroke
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

    n = ecrireContoursSegmentsEPS(f, T_Segments, xmax, ymax, fill);
    printf("%s: %d contours, %d segments\n",argv[1], T_Segments->taille, n);

    fclose(f);
}