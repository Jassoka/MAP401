#include <stdio.h>
#include <math.h>
#include "contours_bezier3.h"
#include "contours_bezier2.h"

Liste_Bezier3 *initListeBezier3() {
    Liste_Bezier3 *L = malloc(sizeof(Liste_Bezier3));
    if (!L) return NULL; // malloc fail
    L->tete = NULL;
    L->queue = NULL;
    L->taille = 0;
    return L;
}

Liste_Listes_Bezier3 *initListeListesBezier3() {
    Liste_Listes_Bezier3 *T = malloc(sizeof(Liste_Listes_Bezier3));
    if (!T) return NULL; // malloc fail
    T->tete = NULL;
    T->queue = NULL;
    T->taille = 0;
    return T; 
}

void enfilerBezier3(Liste_Bezier3 *L, Bezier3 c) {
    Cell_Bezier3 *cell = malloc(sizeof(Cell_Bezier3));
    cell->c = c;
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

void enfilerListeBezier3(Liste_Listes_Bezier3 *T, Liste_Bezier3 *L) {
    Cell_Liste_Bezier3 *cell = malloc(sizeof(Cell_Liste_Bezier3));
    cell->L = L;
    cell->suiv = NULL;
    if (!T->tete) {
        T->tete = cell;
        T->queue = cell;
    }
    else {
        T->queue->suiv = cell;
        T->queue = cell;
    }
    T->taille++;
}

Liste_Bezier3 *concatListeBezier3(Liste_Bezier3 *L1, Liste_Bezier3 *L2) {
    Liste_Bezier3 *L = initListeBezier3();
    L->tete = L1->tete;
    L1->queue->suiv = L2->tete;
    L->queue = L2->queue;
    L->taille = L1->taille + L2->taille;
    free(L1);
    free(L2);
    return L;
}

double gamma_bez(double k, double n) {
    return 6*k*k*k*k - 8*n*k*k*k + 6*k*k - 4*n*k + n*n*n*n - n*n;
}

Bezier3 approx_bezier3(Cell_Point *p1, Cell_Point *p2) {
    Bezier3 B;
    double n = p2->indice - p1->indice;
    B.C0 = p1->p;
    B.C3 = p2->p;
    if (n < 3) {
        Bezier2 B2 = approx_bezier2(p1, p2);
        B = conversionBezier2(B2);
    }
    else {
        Point C1;
        Point C2;

        double alpha = ( (-15)*n*n*n + 5*n*n + 2*n + 4 )/( 3*(n + 2)*(3*n*n + 1) );
        double beta = ( 10*n*n*n - 15*n*n + n + 2 )/( 3*(n + 2)*(3*n*n + 1) );
        double lambda = ( 70*n )/( 3*(n*n - 1)*(n*n - 4)*(3*n*n + 1) );

        Point sum1 = creerPoint(0, 0);
        Point sum2 = creerPoint(0, 0);
        
        Cell_Point *cur = p1->suiv;
        int i;
        for (i = 1; cur != p2; i++) {
            sum1 = sommeVect(sum1, multScalaire(cur->p, gamma_bez(i, n) * lambda)); // Somme de P_(i+j1)*gamma(i)
            sum2 = sommeVect(sum2, multScalaire(cur->p, gamma_bez(n - i, n) * lambda)); // Somme de P_(i+j1)*gamma(n-i)
            cur = cur->suiv;
        }
        C1 = sum1; // C1 = somme
        C1 = sommeVect(C1, multScalaire(p1->p, alpha)); // C1 += alpha*p1
        C1 = sommeVect(C1, multScalaire(p2->p, beta)); // C1 += beta*p1
        B.C1 = C1;

        C2 = sum2; // C2 = somme
        C2 = sommeVect(C2, multScalaire(p1->p, beta)); // C2 += beta(p1)
        C2 = sommeVect(C2, multScalaire(p2->p, alpha)); // C2 += alpha(p1)
        B.C2 = C2;
    }
    return B;
}

Liste_Bezier3 *douglasBezier3(Cell_Point *p1, Cell_Point *p2, double d) {
    Liste_Bezier3 *L = NULL;

    Bezier3 B = approx_bezier3(p1, p2);
    int n = p2->indice - p1->indice;

    double d_max = 0;
    double d_j;
    Cell_Point *cur = p1->suiv;
    Cell_Point *k = p1;
    int i;
    for (i = 1; cur && cur != p2; i++)
    {
        d_j = distancePointBezier3(cur->p, B, (double)i/(double)n);
        if (d_max < d_j) {
            d_max = d_j;
            k = cur;
        }
        cur = cur->suiv;
    }
    if (d_max-d <= 1e-9) {
        L = initListeBezier3();
        enfilerBezier3(L, B);
    }
    else {
        Liste_Bezier3 *L1 = douglasBezier3(p1, k, d);
        Liste_Bezier3 *L2 = douglasBezier3(k, p2, d);
        L = concatListeBezier3(L1, L2);
    }
    
    return L;
}

Liste_Listes_Bezier3 *simplificationBezier3(Liste_Listes *T, double d) {
    Cell_Liste *cell = T->tete;
    Cell_Point *p1;
    Cell_Point *p2;
    Liste_Listes_Bezier3 *T_bez = initListeListesBezier3();
    Liste_Bezier3 *L_bez;
    while (cell) {
        p1 = cell->L->tete;
        p2 = cell->L->queue;
        L_bez = douglasBezier3(p1, p2, d);
        enfilerListeBezier3(T_bez, L_bez);
        cell = cell->suiv;
    }
    return T_bez;
}

int ecrireBezier3EPS(FILE *f, Liste_Bezier3 *cont, int ymax) {
    int n = 0;
    Cell_Bezier3 *curr = cont->tete;
    Bezier3 B;

    fprintf(f, "%.2f %.2f moveto\n", xPoint(curr->c.C0), ymax - yPoint(curr->c.C0));
    while (curr != NULL) {
        B = curr->c;
        fprintf(f, "%.2f %.2f %.2f %.2f %.2f %.2f curveto\n", xPoint(B.C1), ymax - yPoint(B.C1), xPoint(B.C2), ymax - yPoint(B.C2), xPoint(B.C3), ymax - yPoint(B.C3) );
        n++; 
        curr = curr->suiv;
    }
    fprintf(f, "\n");
    return n;
}

int ecrireContoursBezier3EPS(FILE *f, Liste_Listes_Bezier3 *T, int xmax, int ymax, bool fill) {
    int n = 0;
    Cell_Liste_Bezier3 *cell = T->tete;

    fprintf(f, "%%!PS−Adobe−3.0 EPSF−3.0\n");
    fprintf(f,"%%%%BoundingBox: 0 0 %u %u\n", xmax, ymax);
    while (cell) {
        n += ecrireBezier3EPS(f, cell->L, ymax);
        cell = cell->suiv;
    }
    if (fill) fprintf(f, "fill\n");
    else fprintf(f, "stroke\n");
    fprintf(f, "showpage\n");
    return n;
}