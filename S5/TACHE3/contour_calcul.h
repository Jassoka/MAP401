#ifndef CONTOUR_CALCUL
#define CONTOUR_CALCUL
#include "image.h"
#include "geometrie_2d.h"

typedef enum {Nord = 0, Est = 1, Sud = 2, Ouest = 3} Orientation ;

typedef struct cellule_liste_chainee_points Cell_Point;

typedef struct robot_contour {
    Point pos; // Position
    Orientation o; // Orientation du robot
} Robot;

typedef struct cellule_liste_chainee_points {
    Point *p;
    Cell_Point *suiv;
} Cell_Point;

typedef struct liste_chainee_points {
    Cell_Point *tete;
    Cell_Point *queue;
} Liste_Points;

/* Renvoie le point de depart du contour exterieur d'une image I*/
Point premPoint(Image I);

/* Initialise une liste de points vide */
Liste_Points *initListePoints(void);

/* Initialise un robot a la position x, y et orientation o */
Robot initRobot(double x, double y, Orientation o);

/* Renvoie la coordonnée entiere */
int getX (Robot r);

int getY (Robot r);

/* Ajoute une cellule de coordonnée (x,y) en queue de liste */
void enfilerPoint(Liste_Points *L, int x, int y);

/* Memorise un point dans la liste chainee L */
void memoriserPosition(Robot r, Liste_Points *L); 

/* Avance le robot d'une case dans le sens de l'orientation */
void avancer(Robot r);

/* Renvoie la valeur du pixel devant le robot à sa gauche */
Pixel pixelGauche(Image I, Robot r);

/* Renvoie la valeur du pixel devant le robot à sa droite */
Pixel pixelDroite(Image I, Robot r);

/* Reoriente le robot afin d'avoir un pixel blanc devant a gauche et noir a droite */
void nouvelleOrientation(Image I, Robot r);

/* Renvoie le contour exterieur d'une image */
Liste_Points *contourExterieur(Image I);

#endif