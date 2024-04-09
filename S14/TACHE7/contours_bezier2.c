#include <stdio.h>
#include <math.h>
#include "contours_bezier2.h"

Liste_Bezier2 *initListeBezier2() {
    Liste_Bezier2 *L = malloc(sizeof(Liste_Bezier2));
    if (!L) return NULL; // malloc fail
    L->tete = NULL;
    L->queue = NULL;
    L->taille = 0;
    return L;
}

Liste_Listes_Bezier2 *initListeListesBezier2() {
    Liste_Listes_Bezier2 *T = malloc(sizeof(Liste_Listes_Bezier2));
    if (!T) return NULL; // malloc fail
    T->tete = NULL;
    T->queue = NULL;
    T->taille = 0;
    return T; 
}

void enfilerBezier2(Liste_Bezier2 *L, Bezier2 c) {
    Cell_Bezier2 *cell = malloc(sizeof(Cell_Bezier2));
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

void enfilerListeBezier2(Liste_Listes_Bezier2 *T, Liste_Bezier2 *L) {
    Cell_Liste_Bezier2 *cell = malloc(sizeof(Cell_Liste_Bezier2));
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

Liste_Bezier2 *concatListeBezier2(Liste_Bezier2 *L1, Liste_Bezier2 *L2) {
    Liste_Bezier2 *L = initListeBezier2();
    L->tete = L1->tete;
    L1->queue->suiv = L2->tete;
    L->queue = L2->queue;
    L->taille = L1->taille + L2->taille;
    free(L1);
    free(L2);
    return L;
}


Bezier2_taille approx_bezier2(Cell_Point *p1, Cell_Point *p2) {
    Bezier2_taille B;
    Bezier2 c;
    double n = 1;
    c.C0 = p1->p;
    c.C2 = p2->p;
    if (p1->suiv == p2) { // Cas n = 1
        c.C1 = multScalaire(sommeVect(p1->p, p2->p), 0.5) ; // C1 = (p1+p2)/2
    }
    else {
        Point sum = creerPoint(0, 0);
        Point C1;
        Cell_Point *cur = p1->suiv;
        while (cur != p2) {
            n++;
            sum = sommeVect(sum, cur->p); // Somme de P_(i+j1)
            cur = cur->suiv;
        }
        double alpha = 3*n/(n*n-1);
        double beta = (1-2*n)/(2*(n+1));
        C1 = multScalaire(sum, alpha); // C1 = alpha*somme
        C1 = sommeVect(C1, multScalaire(sommeVect(p1->p, p2->p), beta)); // C1 += beta(p1+p2)
        c.C1 = C1;
    }
    B.c = c;
    B.taille = (int)(n + 1e-9);
    return B;
}

Liste_Bezier2 *douglasBezier2(Cell_Point *p1, Cell_Point *p2, double d) {
    Liste_Bezier2 *L = NULL;

    Bezier2_taille B = approx_bezier2(p1, p2);
    Bezier2 c = B.c;
    int n = B.taille;

    double d_max = 0;
    double d_j;
    Cell_Point *cur = p1->suiv;
    Cell_Point *k = p1;
    int i;
    for (i = 1; cur && cur != p2; i++)
    {
        d_j = distancePointBezier2(cur->p, c, (double)i/(double)n);
        if (d_max < d_j) {
            d_max = d_j;
            k = cur;
        }
        cur = cur->suiv;
    }
    if (d_max-d <= 1e-9) {
        L = initListeBezier2();
        enfilerBezier2(L, c);
    }
    else {
        Liste_Bezier2 *L1 = douglasBezier2(p1, k, d);
        Liste_Bezier2 *L2 = douglasBezier2(k, p2, d);
        L = concatListeBezier2(L1, L2);
    }
    return L;
}

Liste_Listes_Bezier2 *simplificationBezier2(Liste_Listes *T, double d) {
    Cell_Liste *cell = T->tete;
    Cell_Point *p1;
    Cell_Point *p2;
    Liste_Listes_Bezier2 *T_bez = initListeListesBezier2();
    Liste_Bezier2 *L_bez;
    while (cell) {
        p1 = cell->L->tete;
        p2 = cell->L->queue;
        L_bez = douglasBezier2(p1, p2, d);
        enfilerListeBezier2(T_bez, L_bez);
        cell = cell->suiv;
    }
    return T_bez;
}

int ecrireBezier2EPS(FILE *f, Liste_Bezier2 *cont, int ymax) {
    int n = 0;
    Cell_Bezier2 *curr = cont->tete;
    Bezier3 B;

    fprintf(f, "%.2f %.2f moveto\n", xPoint(curr->c.C0), ymax - yPoint(curr->c.C0));
    while (curr != NULL) {
        B = conversionBezier2(curr->c);
        fprintf(f, "%.2f %.2f %.2f %.2f %.2f %.2f curveto\n", xPoint(B.C1), ymax - yPoint(B.C1), xPoint(B.C2), ymax - yPoint(B.C2), xPoint(B.C3), ymax - yPoint(B.C3) );
        n++;
        curr = curr->suiv;
    }
    fprintf(f, "\n");
    return n;
}


int ecrireContoursBezier2EPS(FILE *f, Liste_Listes_Bezier2 *T, int xmax, int ymax, bool fill) {
    int n = 0;
    Cell_Liste_Bezier2 *cell = T->tete;

    fprintf(f, "%%!PS−Adobe−3.0 EPSF−3.0\n");
    fprintf(f,"%%%%BoundingBox: 0 0 %u %u\n", xmax, ymax);
    while (cell) {
        n += ecrireBezier2EPS(f, cell->L, ymax);
        cell = cell->suiv;
    }
    if (fill) fprintf(f, "fill\n");
    else fprintf(f, "stroke\n");
    fprintf(f, "showpage\n");
    return n;
}