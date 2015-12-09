#include <draw.h>

void drawSpot (Particule *p){
	g2x_Spot(p->pos.x,p->pos.y,p->ray,p->col);
}

void drawCircle (Particule *p){
	g2x_FillCircle(p->pos.x,p->pos.y,p->ray,p->col);
}
