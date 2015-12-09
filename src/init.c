#include <init.h>

void init_loup(Particule *loup){
	loup->pos.x = g2x_RandDelta(0.0,XMAX);
	loup->pos.y = g2x_RandDelta(0.0,YMAX);
	
	loup->vit.x = g2x_RandDelta(0.0,1.0);
	loup->vit.y = g2x_RandDelta(0.0,1.0);
	
	loup->ray = 1.0;
	loup->digestion = 0;
	loup->eaten = 0;
	
	loup->col[0] = 0.0;
	loup->col[1] = 1.0;
	loup->col[2] = 0.0;
	loup->col[3] = 1.0;
	
	loup->draw = drawCircle;
	loup->move = partMove;
	loup->edge = rebond;
}

void init_moutons(Particule * moutons,int nm){
	int i = 0;
	for(i = 0; i<nm; i++){
		moutons[i].pos.x = g2x_RandDelta(0.0,XMAX);
		moutons[i].pos.y = g2x_RandDelta(0.0,YMAX);
	
		moutons[i].vit.x = g2x_RandDelta(0.0,1.0);
		moutons[i].vit.y = g2x_RandDelta(0.0,1.0);
	
		moutons[i].ray = 0.5;
	
		moutons[i].col[0] = 0.0;
		moutons[i].col[1] = 0.0;
		moutons[i].col[2] = 1.0;
		moutons[i].col[3] = 1.0;
	
		moutons[i].draw = drawCircle;
		moutons[i].move = partMove;
		moutons[i].edge = rebond;
	}
	
}


void init_chien(Particule *chien){
	chien->pos.x = g2x_RandDelta(0.0,XMAX);
	chien->pos.y = g2x_RandDelta(0.0,YMAX);
	
	chien->vit.x = g2x_RandDelta(0.0,1.0);
	chien->vit.y = g2x_RandDelta(0.0,1.0);
	
	chien->ray = 1.0;
	
	chien->col[0] = 1.0;
	chien->col[1] = 0.0;
	chien->col[2] = 0.0;
	chien->col[3] = 1.0;
	
	chien->draw = drawCircle;
	chien->move = partMove;
	chien->edge = rebond;
}

