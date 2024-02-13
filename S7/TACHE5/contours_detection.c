#include <stdio.h>
#include <math.h>
#include "contour_calcul.h"

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
    printf("x0: %d, y0: %d\n", x0, y0);
    if (x0 == -1 || y0 == -1)
        return L; // Aucun point candidat
    int x = x0;
    int y = y0;
    Robot r = initRobot(x0, y0, Est);

    Orientation o;
    do
    {
        memoriserPosition(r, L);
        o = getO(r);
        if (o == Est)
        {
            set_pixel_image(M, x + 1, y + 1, BLANC); // Si le robot est orienté à l'est on supprime le pixel SE
        }
        avancer(&r);
        x = getX(r);
        y = getY(r);
        nouvelleOrientation(I, &r);
    } while (x != x0 || y != y0 || r.o != Est);
    memoriserPosition(r, L);
    return L;
}

Liste_Listes *detectionContours(Image I) {
    Image M = imageMasque(I);
    Liste_Listes *T = initListeListes();
    Liste_Points *L = calculContour(I, M);
    while (L->taille != 0) {
        empilerListe(T, L);
        L = calculContour(I, M);
    }
    return T;
}

void ecritureContours(Image I, FILE *f, Liste_Listes *T)
{
    Cell_Liste *cell = T->tete;
    fprintf(f, "%d\n", T->taille);
    while (cell) {
        ecrireContour(cell->L, f);
        cell = cell->suiv;
    }
}