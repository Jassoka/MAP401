#include <stdio.h>
#include <math.h>
#include "geometrie_2d.h"


Vecteur creerVecteur(double x, double y)
{
    Vecteur u ;
    u.x= x;
    u.y= y;
    return u ;
}

Point creerPoint(double x, double y)
{
    Point a ;
    a.x= x;
    a.y= y;
    return a ;
}

Segment creerSegment(Point a, Point b) {
    Segment s;
    s.a = a;
    s.b = b;
    return s;
}

Bezier2 creerBezier2(Point C0, Point C1, Point C2) {
    Bezier2 c;
    c.C0 = C0;
    c.C1 = C1;
    c.C2 = C2;
    return c;
}

Bezier3 creerBezier3(Point C0, Point C1, Point C2, Point C3) {
    Bezier3 c;
    c.C0 = C0;
    c.C1 = C1;
    c.C2 = C2;
    c.C3 = C3;
    return c;
}

double xPoint(Point a)
{
    return a.x ;
}

double yPoint(Point a)
{
    return a.y ;
}

double xVecteur(Vecteur u)
{
    return u.x ;
}

double yVecteur(Vecteur u)
{
    return u.y ;
}

Point pointA(Segment s) {
    return s.a;
}

Point pointB(Segment s) {
    return s.b;
}

Vecteur sommeVect(Vecteur u1, Vecteur u2)
{
    double x1,y1,x2,y2;
    x1 = xVecteur(u1);
    y1= yVecteur(u1);
    x2= xVecteur(u2);
    y2= yVecteur(u2);

    Vecteur res = creerVecteur(x1+x2,y1+y2);
    return res ;

}

Vecteur differenceVect(Vecteur u1, Vecteur u2)
{
    double x1,y1,x2,y2;
    x1= xVecteur(u1);
    y1= yVecteur(u1);
    x2= xVecteur(u2);
    y2= yVecteur(u2);

    Vecteur res = creerVecteur(x1-x2,y1-y2);
    return res ;

}

Point sommePoints(Point a, Point b) 
{
    return sommeVect(a, b);
}

Vecteur vectPoints(Point a, Point b) 
{
    return differenceVect(b,a) ;
}

double norme(Vecteur u)
{
    double x = xVecteur(u);
    double y = yVecteur(u);
    return sqrt(x*x+y*y);
}

double produitScalaire(Vecteur u1, Vecteur u2)
{
    return xVecteur(u1)*xVecteur(u2) + yVecteur(u1)*yVecteur(u2); 
}

double distance(Point a, Point b)
{
    return norme(vectPoints(a, b));
}

Vecteur multScalaire(Vecteur u, double lambda)
{
    Vecteur v;
    double x = xVecteur(u);
    double y = yVecteur(u);
    v = creerVecteur(x*lambda, y*lambda);
    return v;
}

Point projection(Point p, Segment s) {
    Point o = creerPoint(0.0, 0.0);
    Vecteur AP = vectPoints(pointA(s), p);
    Vecteur AB = vectPoints(pointA(s), pointB(s));
    Vecteur OA = vectPoints(o, pointA(s));
    double lambda;
    lambda = produitScalaire(AP, AB)/produitScalaire(AB, AB);
    Vecteur OQ = sommeVect(OA, multScalaire(AB, lambda));
    return OQ;
}

double distancePointSegment(Point p, Segment s) {
    Vecteur AP = vectPoints(pointA(s), p);
    if (xPoint(pointA(s)) == xPoint(pointB(s)) && yPoint(pointA(s)) == yPoint(pointB(s))) {
        return norme(AP);
    }
    Point o = creerPoint(0.0, 0.0);
    Vecteur AB = vectPoints(pointA(s), pointB(s));
    Vecteur OA = vectPoints(o, pointA(s));
    double lambda;
    lambda = produitScalaire(AP, AB)/produitScalaire(AB, AB);
    Point q = sommeVect(OA, multScalaire(AB, lambda));
    
    if (lambda > 1) return distance(pointB(s), p);
    if (lambda < 0) return distance(pointA(s), p);
    return distance(q,p);
}

Point evalBezier2(Bezier2 c, double t) {
    if (t < -1e-9) t = 0.0;
    else if (t-1 > 1e-9) t = 1.0;
    Point C_t;
    Point C_2_0 = multScalaire(c.C0, (1-t)*(1-t)); // C0(1-t)^2
    Point C_2_1 = multScalaire(c.C1, (1-t)*t*2); // 2C1(1-t)t
    Point C_2_2 = multScalaire(c.C2, t*t); // C2(t^2)
    C_t = sommePoints(C_2_0, sommePoints(C_2_1, C_2_2));
    return C_t;
}

Point evalBezier3(Bezier3 c, double t) {
    if (t < -1e-9) t = 0.0;
    else if (t-1 > 1e-9) t = 1.0;
    Point C_t;
    Point C_3_0 = multScalaire(c.C0, (1-t)*(1-t)*(1-t)); // C0(1-t)^3
    Point C_3_1 = multScalaire(c.C1, (1-t)*(1-t)*t*3); // 3C1((1-t)^2)t
    Point C_3_2 = multScalaire(c.C2, (1-t)*t*t*3); // 3C2(1-t)t^2
    Point C_3_3 = multScalaire(c.C3, t*t*t); // C3(t^3)
    C_t = sommePoints(sommePoints(C_3_0, C_3_1), sommePoints(C_3_2, C_3_3));
    return C_t;
}

Bezier3 conversionBezier2(Bezier2 c2) {
    Bezier3 c3;
    Point C0, C1, C2, C3;
    C0 = c2.C0;
    C1 = sommePoints( multScalaire(c2.C1, 2.0/3.0), multScalaire(c2.C0, 1.0/3.0) );
    C2 = sommePoints( multScalaire(c2.C1, 2.0/3.0), multScalaire(c2.C2, 1.0/3.0) );
    C3 = c2.C2;
    c3 = creerBezier3(C0, C1, C2, C3);
    return c3;
}

double distancePointBezier2(Point p, Bezier2 c, double t_i) {
    Point C_ti = evalBezier2(c, t_i);
    return distance(p, C_ti);
}

double distancePointBezier3(Point p, Bezier3 c, double t_i) {
    Point C_ti = evalBezier3(c, t_i);
    return distance(p, C_ti);
}