#include <stdio.h>
#include <math.h>
#include "contour_calcul.h"

/*
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
*/

Liste_Points *initListePoints() {
    Liste_Points *L = malloc(sizeof(Liste_Points));
    if (!L) return NULL; // malloc fail
    L->tete = NULL;
    L->queue = NULL;
    L->taille = 0;
    return L; 
}

Robot initRobot(double x, double y, Orientation o) {
    Robot r;
    Point p = creerPoint(x, y);
    r.pos = p;
    r.o = o;
    return r;
}

Orientation getO (Robot r) {
    return r.o;
}

int getX (Robot r) {
    return (int)(r.pos.x + 1e-9);
}

int getY (Robot r) {
    return (int)(r.pos.y + 1e-9);
}

void enfilerPoint(Liste_Points *L, double x, double y) {
    Point *p = malloc(sizeof(Point));
    *p = creerPoint(x, y);
    Cell_Point *cell = malloc(sizeof(Cell_Point));
    cell->p = p;
    cell->suiv = NULL;
    if (!L->tete) {
        L->tete = cell;
        L->queue = cell;
    }
    else {
        L->queue->suiv = cell;
        L->queue = cell;
    }
    L->taille++;
}

void memoriserPosition(Robot r, Liste_Points *L) {
    enfilerPoint(L, r.pos.x, r.pos.y);
}

void avancer(Robot *r) {
    switch(r->o) {
        case Nord:
            r->pos.y--;
        break;
        case Sud:
            r->pos.y++;
        break;
        case Est:
            r->pos.x++;
        break;
        case Ouest:
            r->pos.x--;
        break;
    }
}

Pixel pixelGauche(Image I, Robot r) {
    int x = getX(r);
    int y = getY(r);
    switch(r.o) {
        case Nord:
            return get_pixel_image(I, x, y);
        break;
        case Sud:
            return get_pixel_image(I, x+1, y+1);
        break;
        case Est:
            return get_pixel_image(I, x+1, y);
        break;
        case Ouest:
            return get_pixel_image(I, x, y+1);
        break;
    }
}

Pixel pixelDroite(Image I, Robot r) {
    int x = getX(r);
    int y = getY(r);
    switch(r.o) {
        case Nord:
            return get_pixel_image(I, x+1, y);
        break;
        case Sud:
            return get_pixel_image(I, x, y+1);
        break;
        case Est:
            return get_pixel_image(I, x+1, y+1);
        break;
        case Ouest:
            return get_pixel_image(I, x, y);
        break;
    }
}

void nouvelleOrientation(Image I, Robot *r) {
    Pixel G = pixelGauche(I, *r);
    Pixel D = pixelDroite(I, *r);
    if (G == NOIR) {
        r->o = (r->o-1)%4;
    }
    else if (D == BLANC) {
        r->o = (r->o+1)%4;
    }

}
/*
Liste_Points *contourExterieur(Image I) {
    Liste_Points *L = initListePoints();
    Point position_init = premPoint(I);
    int x0 = (int)(position_init.x+1e-9);
    int y0 = (int)(position_init.y+1e-9);
    int x = x0;
    int y = y0;
    Robot r = initRobot(x0, y0, Est);
    do {
        memoriserPosition(r, L);
        avancer(&r);
        nouvelleOrientation(I, &r);
        x = getX(r);
        y = getY(r);
    }
    while (x != x0 || y != y0 || r.o != Est);
    memoriserPosition(r,L);
    return L;
}
*/

void afficherOrientation(Robot r) {
    switch(r.o) {
        case Nord:
            printf("Orientation: Nord\n");
        break;
        case Sud:
            printf("Orientation: Sud\n");
        break;
        case Est:
            printf("Orientation: Est\n");
        break;
        case Ouest:
            printf("Orientation: Ouest\n");
        break;
    }
}

void afficherContour(Liste_Points *L) {
    Cell_Point *curr = L->tete;
    while (curr != NULL) {
        printf("(%.0f,%.0f) ", curr->p->x, curr->p->y);
        curr = curr->suiv;
    }
    printf("\n");
}

void ecrireContour(Liste_Points *L, FILE *f) {
    fprintf(f, "\n%d\n", L->taille);
    Cell_Point *curr = L->tete;
    while (curr != NULL) {
        fprintf(f, " %.1f %.1f\n", curr->p->x, curr->p->y);
        curr = curr->suiv;
    }
}

Liste_Listes *initListeListes() {
    Liste_Listes *T = malloc(sizeof(Liste_Listes));
    T->taille = 0;
    T->tete = NULL;
    return T;
}

void empilerListe(Liste_Listes *T, Liste_Points *L) {
    Cell_Liste *cell = malloc(sizeof(Cell_Liste));
    cell->L = L;
    if (!T->tete) {
        T->tete = cell;
        cell->suiv = NULL;
    }
    else {
        cell->suiv = T->tete;
        T->tete = cell;
    }
    T->taille++;
}