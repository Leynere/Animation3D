#include <anim.h>

void init_loup_vit(Particule *l){
	l->vit.x = g2x_RandDelta(0.0,1.0)/(double)(l->eaten*0.2);
	l->vit.y = g2x_RandDelta(0.0,1.0)/(double)(l->eaten*0.2);
}

void chasse(Particule *l, Particule *M, double a, int nm){
	int i =  0;
	
	if(l->digestion > 0){
		l->digestion--;
		if(l->digestion == 0){
			init_loup_vit(l);
		}
	}else{
		G2Xvector buff;
	
		buff.x = 0.0;
		buff.y = 0.0;
	
		for( i = 0; i<nm; i++){
		
			G2Xvector dir = g2x_Vector(l->pos,M[i].pos);
		
			double d = normalize(&dir,1.0);
			if( d > 100 )
				continue;
		
			if( d < 20 ){
				l->pos.x = M[i].pos.x;
				l->pos.y = M[i].pos.y;
			
				M[i].pos.x = -9000;
				M[i].pos.y = -9000;
			
				l->vit.x = 0;
				l->vit.y = 0;
				l->eaten++;
				l->digestion = 50;
			}
			double vm = normalize(&M[i].vit,1.0);
			double vl = normalize(&l->vit,1.0);
		
			buff.x += (1/(d*dir.x));
			buff.y += (1/(d*dir.y));
		
			l->vit.x = (1 - a)*l->vit.x + buff.x;
			l->vit.y = (1 - a)*l->vit.y + buff.y;
		
			normalize(&M[i].vit,vm);
			normalize(&l->vit,vl);	
		}
	}
}

void collision_particule(Particule *p, Particule *p2){
	G2Xvector dir = g2x_Vector(p->pos,p2->pos);
	double d = normalize(&dir,1.0);
	double vp = normalize(&p->vit,1.0);
	double vp2 = normalize(&p2->vit,1.0);
	double s1 = 2.5*(vp+vp2);
	if(d>s1)
		return;
	double s0 = 0.5*(vp+vp2);
	double a = SQR((s1 - d)/(s1-s0));
	p->vit.x = (1-a)*p->vit.x - a*dir.x;
	p->vit.y = (1-a)*p->vit.y - a*dir.y;
	p2->vit.x = (1-a)*p2->vit.x + a*dir.x;
	p2->vit.y = (1-a)*p2->vit.y + a*dir.y;
	normalize(&p->vit,vp);
	normalize(&p2->vit,vp2);
}


void fuite(Particule *p, G2Xpoint M, double d){
	G2Xvector pm = g2x_Vector(p->pos,M);
	normalize(&pm,1.0);
	double v = normalize(&p->vit,1.0);
	p->vit.x = (1-d)*p->vit.x - d*pm.x;
	p->vit.y = (1-d)*p->vit.y - d*pm.y;
}

void cible(Particule *p, G2Xpoint M, double d){
	G2Xvector pm = g2x_Vector(p->pos,M);
	normalize(&pm,1.0);
	double v = normalize(&p->vit,1.0);
	p->vit.x = (1-d)*p->vit.x + d*pm.x;
	p->vit.y = (1-d)*p->vit.y + d*pm.y;
}

int part_inside(Particule *p, Circle* c,G2Xvector pc){
	normalize(&pc,1.0);
	p->pos.x = c->ctr.x - c->ray*pc.x;
	p->pos.y = c->ctr.y - c->ray*pc.y;
	double v = normalize(&p->vit,1.0);
	int s;
	if(G2Xprodvect(p->vit,pc)>0)
		s = 1;
	else
		s = -1;
	p->vit.x = +s*pc.y;
	p->vit.y = -s*pc.x;
	
	normalize(&p->vit,v);
	return 0;
}

int evite_obstacle(Particule *p, Circle *crc, int nc){
	Circle *c, *collision = NULL;
	double d2,r2,a,b,s,z=1000;
	G2Xvector pi,pj,pc,dir;
	c = crc;
	while(c<crc+nc){
		pc = g2x_Vector(p->pos,c->ctr);
		d2 = G2Xsqrnorm(pc);
		r2 = SQR(c->ray);
		if(d2<r2)
			return part_inside(p,c,pc);
		if(d2>9*r2){
			c++;
			continue;
		}
		if(G2Xprodscal(p->vit,pc)<=0.0){
			c++;
			continue;
		}
		if(collision && d2>2){
			c++; 
			continue;
		}
		a = r2/d2;
		b = 1-a;
		s = sqrt(a*b);
		pi.x = b*pc.x - s*pc.y;
		pi.y = b*pc.y + s*pc.x;
		pj.x = b*pc.x + s*pc.y;
		pj.y = b*pc.y - s*pc.x;
		a = G2Xprodvect(p->vit,pi);
		b = G2Xprodvect(p->vit,pj);
		if(a*b>= 0){
			c++;
			continue;
		}
		collision = c;
		z = d2;
		if((a*a) < (b*b))
			dir = pi;
		else
			dir = pj;
		c++;
	}
	if(collision != NULL)
		traite_collision(p,collision,dir);
}

double normalize(G2Xvector *v, double newn){
	double oldn = G2Xnorm(*v);
	if(oldn<EPSILON)
		oldn = EPSILON;
	newn /= oldn;
	v->x *= newn;
	v->y *= newn;
	return oldn;
}

void traite_collision(Particule *p, Circle* collision, G2Xvector dir){
	G2Xvector pc = g2x_Vector(p->pos,collision->ctr);
	double d = G2Xnorm(pc);
	double a = pow(((3*collision->ray)-d)/(2*collision->ray),15);
	
	double v = normalize(&p->vit,1.0);
	normalize(&dir,1);
	p->vit.x = (1-a)*p->vit.x + a*dir.x;
	p->vit.y = (1-a)*p->vit.y + a*dir.y;
	normalize(&p->vit,v);
}


void traverse(Particule *p){
	if(p->pos.x < XMIN)
		p->pos.x = XMAX;
	if(p->pos.x > XMAX)
		p->pos.x = XMIN;
		
	if(p->pos.y < YMIN)
		p->pos.y = YMAX;
	if(p->pos.y > YMAX)
		p->pos.y = YMIN;
}

void rebond(Particule *p){
	double x = p->pos.x+p->vit.x;
	double y = p->pos.y+p->vit.y;
	if(x < XMIN || x > XMAX)
		p->vit.x *= -1;
	if(y < YMIN || y > YMAX)
		p->vit.y *= -1;
}


void partMove(Particule *p){
	p->pos.x += p->vit.x;
	p->pos.y += p->vit.y;
}
