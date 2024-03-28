#include "contours_detection.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    Image I = lire_fichier_image(argv[1]);
    Liste_Listes *T;
    int n;
    FILE *f;

    T = detectionContours(I);

    /* Conversion de string "image.pbm" a "image.eps" */
    char* nom_fichier = malloc(sizeof(char)*strlen(argv[1])*2);
    strcpy(nom_fichier, argv[1]);
    char* extension;
    extension = strchr(nom_fichier, '.');
    *extension = '\0';
    strcat(nom_fichier, ".eps");
    
    int xmax = I.la_largeur_de_l_image;
    int ymax = I.la_hauteur_de_l_image;

    f = fopen(nom_fichier, "w");
    free(nom_fichier);


    n = ecritureEPS(f, T, xmax, ymax);
    printf("%s: %d contours, %d segments\n",argv[1], T->taille, n);

    fclose(f);

    return 0;
}
