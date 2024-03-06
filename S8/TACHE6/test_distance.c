#include "geometrie_2d.h"
#include <stdio.h>

int main() {
    Point a;
    Point b;
    Point p;
    double x, y;

    printf("Point A? (format: \"x y\")\n");
    scanf("%lf %lf", &x, &y);
    a = creerPoint(x, y);
    printf("Point B?\n");
    scanf("%lf %lf", &x, &y);
    b = creerPoint(x, y);
    printf("Point P?\n");
    scanf("%lf %lf", &x, &y);
    p = creerPoint(x, y);


    Point q = projection(p, a, b);
    printf("Q : (%.1f, %.1f)\n", q.x, q.y);

    return 0;
}