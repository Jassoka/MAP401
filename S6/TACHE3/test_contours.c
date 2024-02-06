#include "contour_calcul.h"

int main(int argc, char **argv)
{

    Image I = lire_fichier_image(argv[1]);
    Liste_Points *L;
    L = contourExterieur(I);

    if (argc > 2)
    {
        FILE *f;
        f = fopen(argv[2], "w");
        fprintf(f, "1\n");
        ecrireContour(L, f);
        fclose(f);
    }
    else {
        afficherContour(L);
    }
    return 0;
}