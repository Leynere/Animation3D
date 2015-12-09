#ifndef __ANIM__
#define __ANIM__

#include <draw.h>
#include <math.h>

#define XMIN -100
#define XMAX 100
#define YMIN -50
#define YMAX  50
#define EPSILON 1.E-6

/*
	Initialise la norme de v par la norme newn.
	Renvoie l'ancienne norme.
*/
double normalize(G2Xvector *v, double newn);

/*
	Enrichie le comportement d'une particule de type loup l pour qu'il se mette en chasse contre les moutons de M.
*/
void chasse(Particule *l, Particule *M, double a, int nm);

/*
	Simule une collision entre une particule p et une particule p2.
*/
void collision_particule(Particule *p, Particule *p2);

/*
	Calcule la prochaine position de la particule en fonction de sa position, direction et vitesse.
*/
void partMove(Particule *p);

/*
	Enrichie le comportement de la particule p de façon à ce qu'elle se dirige vers le point M.
*/
void cible(Particule *p, G2Xpoint M, double d);

/*
	Vérifie si la particule p ne se trouve pas à l'intérieur de l'obstacle c.
	Si oui, elle sort la particule de cet obstacle.
*/
int part_inside(Particule *p, Circle* c,G2Xvector pc);

/*
	Enrichie le comportement de la particule p de façon à ce qu'elle évites l'ensemble d'obstacles crc.
	Le paramètre nc représente le nombre d'obstacle contenu dans le tableau crc.
*/
int evite_obstacle(Particule *p, Circle *crc, int nc);

/*
	Enrichie le comportement de la particule p de façon à ce qu'elle évite la collision en changeant de direction u.
*/
void traite_collision(Particule *p, Circle* collision, G2Xvector u);

/*
	Simule la traversée de la particule p sur l'écran.
*/
void traverse(Particule *p);

/*
	Simule le rebon de la particule p sur l'écran.
*/
void rebond(Particule *p);

#endif
