#include <stdio.h>
#include "contour_calcul.h"

Point premPoint(Image I)
{
    UINT L = largeur_image(I);
    UINT H = hauteur_image(I);
    Pixel curr;
    Pixel nord;
    Point p;
    int x;
    int y;
    for (y = 1; y < (H + 1); y++)
    {
        for (x = 1; x < (L + 1); x++)
        {
            curr = get_pixel_image(I, x, y);
            nord = get_pixel_image(I, x, y-1);
            if (curr == NOIR && nord == BLANC) {
                p = creerPoint((double)x-1, (double)y-1);
                return p;
            }
        }
    }
    p = creerPoint(0.0, 0.0);
    return p;
}

Liste_Points *initListePoints() {
    Liste_Points *L = malloc(sizeof(Liste_Points));
    if (!L) return NULL; // malloc fail
    L->tete = NULL;
    L->queue = NULL;
    return L; 
}

Robot initRobot(double x, double y, Orientation o) {
    Robot r;
    Point p = creerPoint(x, y);
    r.pos = p;
    r.o = o;
    return r;
}

int getX (Robot r) {
    return (int)r.pos.x;
}

int getY (Robot r) {
    return (int)r.pos.y;
}

void enfilerPoint(Liste_Points *L, int x, int y) {
    Point p = creerPoint((double)x, (double)y);
    Cell_Point *cell = malloc(sizeof(Cell_Point));
    cell->p = &p;
    cell->suiv = NULL;
    if (!L->tete) {
        L->tete = cell;
        L->queue = cell;
    }
    else {
        L->queue->suiv = cell;
        L->queue = cell;
    }
}

void memoriserPosition(Robot r, Liste_Points *L) {
    enfilerPoint(L, r.pos.x, r.pos.y);
}

void avancer(Robot r) {
    switch(r.o) {
        case Nord:
            r.pos.y--;
        break;
        case Sud:
            r.pos.y++;
        break;
        case Est:
            r.pos.x++;
        break;
        case Ouest:
            r.pos.x--;
        break;
    }
}

Pixel pixelGauche(Image I, Robot r) {
    double x = getX(r);
    double y = getY(r);
    switch(r.o) {
        case Nord:
            return get_pixel_image(I, (int)x, (int)y);
        break;
        case Sud:
            return get_pixel_image(I, (int)x+1, (int)y+1);
        break;
        case Est:
            return get_pixel_image(I, (int)x+1, (int)y);
        break;
        case Ouest:
            return get_pixel_image(I, (int)x, (int)y+1);
        break;
    }
}

Pixel pixelDroite(Image I, Robot r) {
    double x = getX(r);
    double y = getY(r);
    switch(r.o) {
        case Nord:
            return get_pixel_image(I, (int)x+1, (int)y);
        break;
        case Sud:
            return get_pixel_image(I, (int)x, (int)y+1);
        break;
        case Est:
            return get_pixel_image(I, (int)x+1, (int)y+1);
        break;
        case Ouest:
            return get_pixel_image(I, (int)x, (int)y);
        break;
    }
}

void nouvelleOrientation(Image I, Robot r) {
    Pixel G = pixelGauche(I, r);
    Pixel D = pixelDroite(I, r);
    if (G == NOIR) {
        r.o = (r.o+1)%4;
    }
    else if (D == BLANC) {
        r.o = (r.o-1)%4;
    }

}

Liste_Points *contourExterieur(Image I) {
    Liste_Points *L = initListePoints();
    Point position_init = premPoint(I);
    int x0 = position_init.x;
    int y0 = position_init.y;
    int x, y;
    Robot r = initRobot(x0, y0, Est);
    do {
        memoriserPosition(r, L);
        avancer(r);
        nouvelleOrientation(I, r);
        x = (int)getX(r);
        y = (int)getY(r);
    }
    while (x != x0 || y != y0 || r.o != Est);
    memoriserPosition(r,L);
    return L;
}