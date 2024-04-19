#include "geometrie_2d.h"
#include <stdio.h>

/* Prend en entrée des points A, B et P, puis affiche la distance entre P et le segment AB */
int main(int argc, char **argv) {

    Point a;
    Point b;
    Point p;
    double xA, yA, xB, yB, xP, yP;
    double dist;

    printf("Point A:\n");
    scanf("%lf", &xA);
    scanf("%lf", &yA);
    printf("Point B:\n");
    scanf("%lf", &xB);
    scanf("%lf", &yB);
    printf("Point P:\n");
    scanf("%lf", &xP);
    scanf("%lf", &yP);

    a = creerPoint(xA, yA);
    b = creerPoint(xB, yB);
    p = creerPoint(xP, yP);

    Segment s = creerSegment(a, b);

    dist = distancePointSegment(p, s);
    printf("A: (%.1lf, %.1lf) B: (%.1lf, %.1lf) P: (%.1lf, %.1lf)\n", xA, yA, xB, yB, xP, yP);
    printf("Distance P au segment AB: %.2lf\n", dist);
    return 0;
}