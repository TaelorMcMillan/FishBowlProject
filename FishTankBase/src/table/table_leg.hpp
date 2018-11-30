#ifndef CTABLE_LEG_H
#define CTABLE_LEG_H

#include <GL/glut.h>

#include "../Shape.hpp"
#include "../Camera.hpp"
#include "../Light.hpp"

class table_leg: public Shape {
protected:
	GLfloat vertex[8][3];
	GLint face[6][4];
	GLfloat faceColor[6][3];
	GLfloat faceNormal[6][3];

public:
	table_leg();
	void draw();

private:
	void drawFace(int);
	bool isFrontface(int faceindex, Camera camera);
	GLfloat getShade(int faceindex, Light light);
};

#endif
