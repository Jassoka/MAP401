#include <stdio.h>
#include "contours_bezier3.h"
#include "contours_detection.h"

int main() {
    Liste_Points *L = initListePoints();
    enfilerPoint(L, 0,0);
    enfilerPoint(L, 1,0);
    enfilerPoint(L, 1,1);
    enfilerPoint(L, 1,2);
    enfilerPoint(L, 2,2);
    enfilerPoint(L, 3,2);
    enfilerPoint(L, 3,3);
    enfilerPoint(L, 4,3);
    enfilerPoint(L, 5,3);

    Bezier3 B = approx_bezier3(L->tete, L->queue);
    int n = L->taille;
    Cell_Point *curr = L->tete->suiv;
    Point p;
    double indice;
    for (int i = 1; i <= n-1; i++) {
        p = curr->p;
        indice = (double)i/(double)n;
        printf("Distance entre (%.2f,%.2f) et C(%.2f)\n", p.x, p.y, indice);
        printf("%.2f\n", distancePointBezier3(p, B, indice));
        curr = curr->suiv;
    }
    return 0;
}