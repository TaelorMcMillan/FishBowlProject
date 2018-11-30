#include "Solar.hpp"

Solar::Solar() {
	Sun = new Sphere();
	Earth = new Sphere();
	Moon = new Sphere();

	Sun->radius = 1;
	Sun->translate(0, 0, 0);

	Earth->radius = 0.25;
	Earth->translate(2, 0, 0);

	Moon->radius = 0.1;
	Moon->translate(2.4, 0, 0);
}

Solar::~Solar() {
	delete Sun;
	delete Earth;
	delete Moon;
}

void Solar::draw() {
	// material setting for the sun
	GLfloat matAmb1[] = { 0.7, 0.53, 0.3, 1.0 };
	GLfloat matDif1[] = { 0.76, 0.57, 0.16, 1.0 };
	GLfloat matSpec1[] = { 1.0, 0.15, 0.0, 1.0 };
	GLfloat matEm1[] = { 0.75, 0.588, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec1);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEm1);
	Sun->draw();

	// material setting for the earth
	GLfloat matAmb2[] = { 0.1, 0.1, 0.2, 1.0 };
	GLfloat matDif2[] = { 0.4, 0.74, 0.7, 1.0 };
	GLfloat matSpec2[] = { 1.0, 0.8, 0.7, 1.0 };
	GLfloat matEm2[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec2);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEm2);
	Earth->draw();

	// material setting for the moon
	GLfloat matAmb3[] = { 0.2, 0.2, 0.25, 1.0 };
	GLfloat matDif3[] = { 0.8, 0.8, 0.95, 1.0 };
	GLfloat matSpec3[] = { 0.3, 0.3, 1.0, 1.0 };
	GLfloat matEm3[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec3);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEm3);
	Moon->draw();

}

void Solar::translate(GLfloat tx, GLfloat ty, GLfloat tz) {
	Sun->translate(tx, ty, tz);
	Earth->translate(tx, ty, tz);
	Moon->translate(tx, ty, tz);
}

void Solar::rotate_origin(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	Sun->rotateOrigin(rx, ry, rz, angle);
	Earth->rotateOrigin(rx, ry, rz, angle);
	Moon->rotateOrigin(rx, ry, rz, angle);
}

void Solar::reset() {
	Sun->reset();
	Sun->translate(0, 0, 0);

	Earth->reset();
	Earth->translate(2, 0, 0);

	Moon->reset();
	Moon->translate(2.4, 0, 0);
}


