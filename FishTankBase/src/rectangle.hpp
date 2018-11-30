#ifndef RECT_H
#define RECT_H

#include <GL/glut.h>

#include "Shape.hpp"
#include "Camera.hpp"
#include "Light.hpp"

class rectangle: public Shape {
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
	void set(int text, double yt, double yb, double zcl, double zf, double xl, double xr);
	rectangle();
	void draw();
	int textureID ;

private:
	void drawFace(int);
	bool isFrontface(int faceindex, Camera camera);
	GLfloat getShade(int faceindex, Light light);
};

#endif
