#include <init.h>

#define NC 150
#define NM 20

void init();
void draw();
void anim();
void quit();

static Circle  circ[NC];

static Particule moutons[NM];

static Particule chien;

static Particule loup;

static int pix_width = 600;
static int pix_height = 300;


void init(){
  Init_Circles(circ,NC,20.);
  init_moutons(moutons,NM);
	init_chien(&chien);
	init_loup(&loup);
	g2x_SetControlPoint(&chien.pos,10);
}

void draw(){
	Circle *c=circ;
	for (c=circ; c<circ+NC;c++) 
	g2x_FillCircle(c->ctr.x,c->ctr.y,c->ray,c->col);  
	int i = 0;
	for(i = 0; i<NM; i++)
		moutons[i].draw(&moutons[i]);
	loup.draw(&loup);
	chien.draw(&chien);
}

void anim(){

	int i = 0;
	for(i = 0; i<NM; i++){
		int j;
		for(j = i+1; j<NM; j++){
			collision_particule(&moutons[i],&moutons[j]);
		}
	}
	
	for(i = 0; i<NM; i++){
		evite_obstacle(&moutons[i],circ,NC);
	}
	evite_obstacle(&chien,circ,NC);
	evite_obstacle(&loup,circ,NC);
	
	/*cible(&chien,loup.pos,0.1);*/ /*Décommenter pour que le chien poursuive le loup*/
	chien.edge(&chien);
	chien.move(&chien);
	
	for(i = 0; i<NM; i++){
		cible(&moutons[i],chien.pos,0.1);
		fuite(&moutons[i],loup.pos,0.1);
		moutons[i].edge(&moutons[i]);
		moutons[i].move(&moutons[i]);	 
	}
	
	/*fuite(&loup,chien.pos,0.1);*/ /*Décommenter pour que le loup fuit le chien*/
	chasse(&loup,moutons,0.1,NM);
	loup.edge(&loup);
	loup.move(&loup);
}

void quit(){

}

int main(int argc, char* argv[]){
	g2x_InitWindow(*argv,pix_width,pix_height);
	g2x_SetWindowCoord(XMIN,YMIN,XMAX,YMAX);
	g2x_SetInitFunction(init);
	g2x_SetDrawFunction(draw);
	g2x_SetAnimFunction(anim);
	g2x_SetExitFunction(quit);
	
	return g2x_MainStart();
}
