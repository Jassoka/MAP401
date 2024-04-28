#include "contours_detection.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Syntaxe: %s <nom de fichier.pbm> <nom de fichier.eps>\n", argv[0]);
        return 1;
    }
    bool fill = true;
    if (argc > 3 && argv[3][0] == 's')
    {
        fill = false; // 3e argument optionnel stroke (par défaut fill)
    }

    Image I = lire_fichier_image(argv[1]);
    Liste_Listes *T;
    int n;
    FILE *f;

    T = detectionContours(I);
    
    int xmax = I.la_largeur_de_l_image;
    int ymax = I.la_hauteur_de_l_image;

    f = fopen(argv[2], "w");

    n = ecrireContoursEPS(f, T, xmax, ymax, fill);
    printf("%s: %d contours, %d segments\n",argv[1], T->taille, n);

    fclose(f);

    return 0;
}
