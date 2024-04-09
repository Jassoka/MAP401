#include <stdio.h>
#include <math.h>
#include "contours_detection.h"

Image imageMasque(Image I)
{
    UINT L = largeur_image(I);
    UINT H = hauteur_image(I);
    Pixel curr, nord;
    Image M = creer_image(L, H);
    int x, y;

    for (y = 1; y < (H + 1); y++)
    {
        for (x = 1; x < (L + 1); x++)
        {
            curr = get_pixel_image(I, x, y);
            nord = get_pixel_image(I, x, y - 1);
            if (curr == NOIR && nord == BLANC)
            {
                set_pixel_image(M, x, y, NOIR);
            }
        }
    }
    return M;
}

Point pointCandidat(Image M)
{
    UINT L = largeur_image(M);
    UINT H = hauteur_image(M);
    Pixel curr;
    Point p;
    int x, y;
    for (y = 1; y < (H + 1); y++)
    {
        for (x = 1; x < (L + 1); x++)
        {
            curr = get_pixel_image(M, x, y);
            if (curr == NOIR)
            {
                p = creerPoint((double)x - 1, (double)y - 1);
                return p;
            }
        }
    }
    p = creerPoint(-2.0, -2.0);
    return p;
}

Liste_Points *calculContour(Image I, Image M)
{
    Liste_Points *L = initListePoints();
    Point position_init = pointCandidat(M);
    int x0 = (int)(position_init.x + 1e-9);
    int y0 = (int)(position_init.y + 1e-9);
    if (x0 == -1 || y0 == -1)
        return L; // Aucun point candidat
    int x = x0;
    int y = y0;
    Robot r = initRobot(x0, y0, Est);

    Orientation o = getO(r);
    do
    {
        memoriserPosition(r, L);
        if (o == Est)
        {
            set_pixel_image(M, x + 1, y + 1, BLANC); // Si le robot est orienté à l'est on supprime le pixel SE
        }
        avancer(&r);
        nouvelleOrientation(I, &r);
        x = getX(r);
        y = getY(r);
        o = getO(r);
    } while (x != x0 || y != y0 || o != Est);
    memoriserPosition(r, L);
    return L;
}

Liste_Listes *detectionContours(Image I) {
    Image M = imageMasque(I);
    Liste_Listes *T = initListeListes();
    Liste_Points *L = calculContour(I, M);
    while (L->taille != 0) {
        enfilerListe(T, L);
        L = calculContour(I, M);
    }
    return T;
}

int ecritureContours(Image I, FILE *f, Liste_Listes *T)
{
    Cell_Liste *cell = T->tete;
    int n = 0;
    fprintf(f, "%d\n", T->taille);
    while (cell) {
        ecrireContour(cell->L, f);
        n += cell->L->taille - 1; // Nombre de segments
        cell = cell->suiv;
    }
    return n;
}

void ecrireEPS(FILE *f, Liste_Points *L, int ymax) {
    Cell_Point *curr = L->tete;
    fprintf(f, "%.0f %.0f moveto\n", xPoint(curr->p), ymax - yPoint(curr->p));
    if (curr) curr = curr->suiv;
    while (curr != NULL) {
        fprintf(f, "%.0f %.0f lineto\n", xPoint(curr->p), ymax - yPoint(curr->p));
        curr = curr->suiv;
    }
    fprintf(f, "\n");
}

int ecrireContoursEPS(FILE *f, Liste_Listes *T, int xmax, int ymax, bool fill) {
    Cell_Liste *cell = T->tete;
    int n = 0;

    fprintf(f, "%%!PS−Adobe−3.0 EPSF−3.0\n");
    fprintf(f,"%%%%BoundingBox: 0 0 %u %u\n", xmax, ymax);
    while (cell) {
        ecrireEPS(f, cell->L, ymax);
        n += cell->L->taille - 1; // Nombre de segments
        cell = cell->suiv;
    }
    if (fill) fprintf(f, "fill\n");
    else fprintf(f, "stroke\n");
    fprintf(f, "showpage\n");

    return n;
}