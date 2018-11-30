#include "Sphere.hpp"

Sphere::Sphere() {
	radius = 1.0;
	mode = MODE_WIRE;
	textureID = 0;
	splices = 50;
	stacks = 50;
	quad = gluNewQuadric();
	sx = 1 ;
	sy = 1 ;
	sz = 1 ;
}

Sphere::~Sphere() {
	gluDeleteQuadric(quad);
}

void Sphere::draw() {


		quad = gluNewQuadric();
		gluQuadricTexture(this->quad, GL_TRUE);
		gluQuadricOrientation(this->quad, GLU_OUTSIDE);
		gluQuadricNormals(this->quad, GLU_SMOOTH);

		glPushMatrix();
		ctmMultiply();
		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glScalef(this->s, this->s, this->s);
		glScalef(this->sx, this->sy, this->sz);
		gluSphere(this->quad, radius, 50, 50);
		glDisable(GL_TEXTURE_2D);
		gluDeleteQuadric(this->quad);
		glPopMatrix();



}

