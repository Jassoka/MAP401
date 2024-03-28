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
