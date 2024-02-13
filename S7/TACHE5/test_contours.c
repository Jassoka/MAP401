#include <stdio.h>
#include "contours_detection.h"

int main(int argc, char **argv)
{
    Image I = lire_fichier_image(argv[1]);
    Liste_Listes *T;
    T = detectionContours(I);
    
    if (argc > 2) {
        FILE *f;
        f = fopen(argv[2], "w");
        ecritureContours(I, f, T);
        fclose(f);
    }

    return 0;

}