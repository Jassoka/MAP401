#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "contours_bezier2.h"
#include "contours_detection.h"

int main() {
    Liste_Points *L;
    Bezier2 B;
    Point P0, P1, P2, P3, P4, P5, P6, P7, P8;
    int i, n = 0;
    double indice;
    srand(time(NULL));

    /* Cas n = 1 */
    printf("Test 1\n\n");

    L = initListePoints();
    
    P0 = creerPoint(rand()%20-10, rand()%20-10);
    P1 = creerPoint(rand()%20-10, rand()%20-10);
    enfilerPoint(L,P0);
    enfilerPoint(L,P1);
    B = approx_bezier2(L->tete, L->queue);

    printf("P0:(%.0f, %.0f), P1:(%.0f, %.0f)\n", P0.x, P0.y, P1.x, P1.y);
    printf("B = [(%.2f, %.2f),(%.2f, %.2f),(%.2f, %.2f)]\n", B.C0.x, B.C0.y, B.C1.x, B.C1.y, B.C2.x, B.C2.y);

    printf("(P0 + P1)/2 = (%.2f, %.2f) ( = C1 )\n", (P0.x+P1.x)/2, (P0.y+P1.y)/2);

    /* Cas n ≥ 2 */
    printf("\nTest 2\n\n");

    Point Q0, Q1, Q2;
    Q0 = creerPoint(rand()%20-10, rand()%20-10);
    Q1 = creerPoint(rand()%20-10, rand()%20-10);
    Q2 = creerPoint(rand()%20-10, rand()%20-10);
    printf("Q0:(%.0f, %.0f), Q1:(%.0f, %.0f), Q2:(%.0f, %.0f)\n", Q0.x, Q0.y, Q1.x, Q1.y, Q2.x, Q2.y);
    B.C0 = Q0;
    B.C1 = Q1;
    B.C2 = Q2;
    printf("Donner un entier n: \n");
    scanf("%d", &n);
    L = initListePoints();
    for (i = 0; i <= n; i++) {
        indice = (double)i/(double)n;
        P0 = evalBezier2(B, indice);
        enfilerPoint(L, P0);
    }
    B = approx_bezier2(L->tete, L->queue);
    printf("B = [(%.2f, %.2f),(%.2f, %.2f),(%.2f, %.2f)]\n", B.C0.x, B.C0.y, B.C1.x, B.C1.y, B.C2.x, B.C2.y);
    
    /* Exemple du cours */
    printf("\nExemple du cours\n\n");

    P0 = creerPoint(0, 0);
    P1 = creerPoint(1, 0);
    P2 = creerPoint(1, 1);
    P3 = creerPoint(1, 2);
    P4 = creerPoint(2, 2);
    P5 = creerPoint(3, 2);
    P6 = creerPoint(3, 3);
    P7 = creerPoint(4, 3);
    P8 = creerPoint(5, 3);

    L = initListePoints();
    enfilerPoint(L, P0);
    enfilerPoint(L, P1);
    enfilerPoint(L, P2);
    enfilerPoint(L, P3);
    enfilerPoint(L, P4);
    enfilerPoint(L, P5);
    enfilerPoint(L, P6);
    enfilerPoint(L, P7);
    enfilerPoint(L, P8);

    B = approx_bezier2(L->tete, L->queue);
    n = L->taille-1;
    Cell_Point *curr = L->tete->suiv;
    Point p;
    
    for (i = 1; i <= n-1; i++) {
        p = curr->p;
        indice = (double)i/(double)n;
        printf("Distance entre (%.0f,%.0f) et C(%.3f)\n", p.x, p.y, indice);
        printf("%.3f\n", distancePointBezier2(p, B, indice));
        curr = curr->suiv;
    }
    return 0;
}