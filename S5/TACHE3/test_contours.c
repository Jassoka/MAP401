#include "contour_calcul.h"

int main(int argc, char **argv) {
    Point p;
    Image I = lire_fichier_image(argv[1]);
    p = premPoint(I);
    printf(" Premier point de l'image %s: (%.2f, %.2f)\n", argv[1], p.x, p.y);       
}