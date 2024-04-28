#ifndef CONTOUR_CALCUL
#define CONTOUR_CALCUL
#include "image.h"
#include "geometrie_2d.h"

typedef enum {Nord = 0, Est = 1, Sud = 2, Ouest = 3} Orientation ;

typedef struct cellule_liste_chainee_points Cell_Point;
typedef struct cellule_liste_listes_chainee_points Cell_Liste;

typedef struct robot_contour {
    Point pos; // Position
    Orientation o; // Orientation du robot
} Robot;

typedef struct cellule_liste_chainee_points {
    Point p;
    Cell_Point *suiv;
    int indice;
} Cell_Point;

typedef struct liste_chainee_points {
    Cell_Point *tete;
    Cell_Point *queue;
    int taille;
} Liste_Points;

typedef struct cellule_liste_listes_chainee_points {
    Liste_Points *L;
    Cell_Liste *suiv;
} Cell_Liste;

typedef struct liste_listes_chainee_points {
    Cell_Liste *tete;
    Cell_Liste *queue;
    int taille;
} Liste_Listes;


/* Initialise une liste de points vide */
Liste_Points *initListePoints(void);

/* Initialise un robot a la position x, y et orientation o */
Robot initRobot(double x, double y, Orientation o);

/* Renvoie la coordonnée entiere des abscisses du robot */
int getX (Robot r);

/* Renvoie la coordonnée entiere des ordonnees du robot */
int getY (Robot r);

/* Renvoie la coordonnée flottante des abscisses du robot */
double getXf (Robot r);

/* Renvoie la coordonnée flottante des ordonnees du robot */
double getYf (Robot r);

/* Renvoie l'orientation du robot */
Orientation getO (Robot r);

/* Ajoute une cellule de coordonnée (x,y) en queue de liste */
void enfilerPoint(Liste_Points *L, Point p);

/* Avance le robot d'une case dans le sens de l'orientation */
void avancer(Robot *r);

/* Enfile la position du robot r en queue de liste L */
void memoriserPosition(Robot r, Liste_Points *L); 

/* Renvoie la valeur du pixel devant le robot à sa gauche */
Pixel pixelGauche(Image I, Robot r);

/* Renvoie la valeur du pixel devant le robot à sa droite */
Pixel pixelDroite(Image I, Robot r);

/* Reoriente le robot afin d'avoir un pixel blanc devant a gauche et noir a droite */
void nouvelleOrientation(Image I, Robot *r);

/* Affiche dans la sortie standard l'orientation du robot */
void afficherOrientation(Robot r);

/* Affiche dans la sortie standard la liste de points L*/
void afficherContour(Liste_Points *L);

/* Ecrit un contour dans un fichier f ouvert en ecriture */
void ecrireContour(Liste_Points *L, FILE *f);

Liste_Listes *initListeListes(void);

void enfilerListe(Liste_Listes *T, Liste_Points *L);

#endif