#ifndef __DRAW__
#define __DRAW__

#include <circle.h>


/*
	Structure qui définie une particule de l'animation
*/
typedef struct _part_{
	G2Xpoint pos;
	G2Xvector vit;
	G2Xcolor col;
	double ray;
	int digestion;
	int eaten;
	void (*draw)(struct _part_ *);
	void (*move)(struct _part_ *);
	void (*edge)(struct _part_ *);
	struct _part_ *next;
}Particule;

/*
	Dessine un spot en fonction de la Particule a.
*/
void drawSpot (Particule *p);

/*
	Dessine un cercle remplie en fonction de la particule a.
*/
void drawCircle (Particule *p);

#endif
