#ifndef ROOM_H
#define ROOM_H

#include <GL/glut.h>

#include "Shape.hpp"
#include "Camera.hpp"
#include "Light.hpp"

class Room: public Shape {
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
	Room();
	void draw();
	int textureID;

private:
	void drawFace(int);
	bool isFrontface(int faceindex, Camera camera);
	GLfloat getShade(int faceindex, Light light);
};

#endif
