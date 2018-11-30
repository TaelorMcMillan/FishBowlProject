#ifndef CTABLE_TOP_H
#define CTABLE_TOP_H

#include <GL/glut.h>

#include "../Shape.hpp"
#include "../Camera.hpp"
#include "../Light.hpp"

class table_top: public Shape {
protected:
	GLfloat vertex[8][3];
	GLint face[6][4];
	GLfloat faceColor[6][3];
	GLfloat faceNormal[6][3];
	float ytop  ; // y top
	float ybot ; //y bottom
	float zclose  ; // z close
	float zfar  ; //zfar
	float xleft  ; //xleft
	float xright ; //xright

public:
	table_top();
	void draw();
	int textureID ;

private:
	void drawFace(int);
	bool isFrontface(int faceindex, Camera camera);
	GLfloat getShade(int faceindex, Light light);
};

#endif
