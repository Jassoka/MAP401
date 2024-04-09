#ifndef GEOMETRIE_2D
#define GEOMETRIE_2D

typedef struct Point_2D {
    double x;
    double y;
} Point;

typedef Point Vecteur;

typedef struct Segment_2D {
    Point a;
    Point b;
} Segment;

typedef struct Bezier2_2D {
    Point C0;
    Point C1;
    Point C2;
} Bezier2;

typedef struct Bezier3_2D {
    Point C0;
    Point C1;
    Point C2;
    Point C3;
} Bezier3;

/* Renvoie un vecteur de coordonnées x y*/
Vecteur creerVecteur(double x, double y);

/* Renvoie un point de coordonnées x y*/
Point creerPoint(double x, double y);

/* Renvoie le segment AB */
Segment creerSegment(Point a, Point b);

/* Renvoie la courbe de Bezier de degré 2 avec les points de controles C0, C1, C2 */
Bezier2 creerBezier2(Point C0, Point C1, Point C2);

/* Renvoie la courbe de Bezier de degré 3 avec les points de controles C0, C1, C2, C3 */
Bezier3 creerBezier3(Point C0, Point C1, Point C2, Point C3);

double xPoint(Point a);

double yPoint(Point a);

double xVecteur(Vecteur u);

double yVecteur(Vecteur u);

Point pointA(Segment s);

Point pointB(Segment s);

/*Somme de deux vecteurs */
Vecteur sommeVect(Vecteur u1, Vecteur u2);

/*Difference de deux vecteurs u1-u2 */
Vecteur differenceVect(Vecteur u1, Vecteur u2);

/* Renvoie un vecteur allant du point a au point b*/
Vecteur vectPoints(Point a, Point b);

/* Renvoie la norme de u */
double norme(Vecteur u);

/* Renvoie le produit scalaire de u1 par u2 */
double produitScalaire(Vecteur u1, Vecteur u2);

/* Renvoie la distance entre a et b */
double distance(Point a, Point b);

/* Multiplie un vecteur par un reel lambda*/
Vecteur multScalaire(Vecteur u, double lambda);

/* Renvoie la projection de P sur le segment S */
Point projection(Point p, Segment s);

/* Renvoie la distance entre le point p et le segment S */
double distancePointSegment(Point p, Segment s);

/* Evaluation de la courbe c de degré 2 au point 0 >= t >= 1 */
Point evalBezier2(Bezier2 c, double t);

/* Evaluation de la courbe c de degré 3 au point 0 >= t >= 1 */
Point evalBezier3(Bezier3 c, double t);

/* Elevation du degré 2 au degré 3*/
Bezier3 conversionBezier2(Bezier2 c2);

/* Renvoie la distance entre le point p et la courbe de Bezier de degré 2 c au point t_i */
double distancePointBezier2(Point p, Bezier2 c, double t_i);

#endif /* GEOMETRIE_2D */