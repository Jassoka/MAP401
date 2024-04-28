#include "contour_calcul.h"
#include <string.h>


void formatEPS(FILE *f, Liste_Points *L, int ymax) {
    Cell_Point *curr = L->tete;
    fprintf(f, "%.0f %.0f moveto\n", curr->p->x, ymax - curr->p->y);
    if (curr) curr = curr->suiv;
    while (curr != NULL) {
        fprintf(f, "%.0f %.0f lineto\n", curr->p->x, ymax - curr->p->y);
        curr = curr->suiv;
    }
}


int main(int argc, char **argv) {
    Image I = lire_fichier_image(argv[1]);
    Liste_Points *L;
    L = contourExterieur(I);

    /* Conversion de string "image.pbm" a "image.eps" */
    char* nom_fichier = malloc(sizeof(char)*strlen(argv[1])*2);
    strcpy(nom_fichier, argv[1]);
    char* extension;
    extension = strchr(nom_fichier, '.');
    *extension = '\0';
    strcat(nom_fichier, ".eps");
    
    int xmax = I.la_largeur_de_l_image;
    int ymax = I.la_hauteur_de_l_image;

    FILE *f = fopen(nom_fichier, "w");
    free(nom_fichier);
    fprintf(f, "%%!PS−Adobe −3.0 EPSF−3.0\n");
    fprintf(f,"%%%%BoundingBox: 0 0 %u %u\n", xmax, ymax);

    formatEPS(f, L, ymax);
    fprintf(f, "fill\n");
    fprintf(f, "showpage\n");
    fclose(f);
}
