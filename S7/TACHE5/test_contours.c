#include <stdio.h>
#include "contours_detection.h"

int main(int argc, char **argv)
{
    Image I = lire_fichier_image(argv[1]);
    Liste_Listes *T;
    T = detectionContours(I);
    
    if (argc > 2) {
        FILE *f;
        int n;
        f = fopen(argv[2], "w");
        n = ecritureContours(I, f, T);
        printf( "%s: %d contours, %d segments\n",argv[1], T->taille, n);
        fclose(f);
    }

    return 0;

}