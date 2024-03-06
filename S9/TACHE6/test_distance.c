#include "geometrie_2d.h"
#include <stdio.h>

int main(int argc, char **argv) {

    FILE *f;
    if (argc < 2) return 1;
    f = fopen(argv[1], "r");

    Point a;
    Point b;
    Point p;
    double xA, yA, xB, yB, xP, yP;
    double dist;

    fscanf(f, "%lf %lf %lf %lf %lf %lf", &xA, &yA, &xB, &yB, &xP, &yP);
    a = creerPoint(xA, yA);
    b = creerPoint(xB, yB);
    p = creerPoint(xP, yP);

    Segment s = creerSegment(a, b);

    dist = distancePointSegment(p, s);
    Point q = projection(p, s);
    printf("A: (%.1lf, %.1lf) B: (%.1lf, %.1lf) P: (%.1lf, %.1lf)\n", xA, yA, xB, yB, xP, yP);
    printf("Distance P au segment AB: %.2lf\n", dist);
    return 0;
}