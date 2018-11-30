#include "pebble.hpp"
void randrgb(int k) ;
void red() ; void green() ; void blue() ;
void meh() ;
pebble::pebble() {
	peb = new Sphere();
	radius = 0.15 ;
	x = -5.0; y = -4.424 ; z = -1.4;  maxx = 0.58 ; maxz = 15 ;
	sh = 8 ; //shuffle factor
//	Moon->radius = 0.1;
//	Moon->translate(2.4, 0, 0);
}

pebble::~pebble() {
delete peb ;
}

void pebble::draw() {
peb->translate(x,y,z) ;
for(int i = 0; i < 7 ; i++) {
this->drawline(0) ;
float adjust = -radius - 0.1 ;
peb->translate((x - maxx+adjust), 0, peb->radius*2) ;
this->drawline(2) ;
peb->translate((x - maxx+adjust), 0, peb->radius*2) ;
}

}
void pebble::drawline(float z1) {
	peb->radius = radius ;
	float i = x ;
	int k = z1 ;
	float inc = radius*2 - radius / 8 ; //spaces the pebbles out x
	float shuffle = radius / 10 ;
	for(; i <= maxx ; i = i +inc) {
	this->ctmMultiply();
	peb->translate(inc,0,0) ; // can implement shuffle here
	if(k == 1) {
		red() ;
		inc = radius*2 - radius/5 ;
		shuffle = radius / (sh) ;
	}
	if(k == 2) {
		blue() ;
		inc = radius*2 - radius/9 ;
		shuffle = -radius / (sh) ;
	}
	if(k == 3) {
		green() ;
		inc = radius*2 - radius/3 ;
		shuffle = radius / (sh) ;
	}
	if(k == 4) {
		meh() ;
		k = 0 ;
		inc = radius*2 - radius/3 ;
		shuffle = -radius / (sh) ;
	}
	k++ ;
	peb->draw() ;
	}

}

void pebble::translate(GLfloat tx, GLfloat ty, GLfloat tz) {
//	Sun->translate(tx, ty, tz);
//	Earth->translate(tx, ty, tz);
//	Moon->translate(tx, ty, tz);
}

void pebble::rotate_origin(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
//	Sun->rotateOrigin(rx, ry, rz, angle);
//	Earth->rotateOrigin(rx, ry, rz, angle);
//	Moon->rotateOrigin(rx, ry, rz, angle);
}

void pebble::reset() {
//	Sun->reset();
//	Sun->translate(0, 0, 0);
//
//	Earth->reset();
//	Earth->translate(2, 0, 0);
//
//	Moon->reset();
//	Moon->translate(2.4, 0, 0);
}

void set_color(GLfloat r, GLfloat g, GLfloat b) {
	glDisable(GL_TEXTURE_2D);
	glColor3f(r, g, b);
}
void red() {
	set_color(1,0,0) ;
}
void green() {
	set_color(0,1,0) ;
}
void blue() {
	set_color(0,0,1) ;
}
void meh() {
	set_color(1,0,1) ;
}
void randrgb(int k) {
	if(k == 1) {
		red() ;
	}
	if(k == 2) {
		blue() ;
	}
	else {
		green() ;
	}
}
