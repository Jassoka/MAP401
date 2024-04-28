#include "contour_calcul.h"

int main(int argc, char **argv) {
    Image I = lire_fichier_image(argv[1]);
    contourExterieur(I);   
}