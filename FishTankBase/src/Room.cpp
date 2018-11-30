#include "Room.hpp"
extern Camera myCamera;
extern Light myLight;
extern bool isShading;
extern GLuint texture[];
extern bool isTexture;

Room::Room(){

}


void Room::drawFace(int i)
{

}

void Room::draw()
{
	glBegin(GL_QUADS);
	/* Floor */
	glColor3f(0,0,.75);
	glVertex3f(-10,-7,-10);
	glVertex3f(10,-7,-10);
	glVertex3f(10,-7,10);
	glVertex3f(-10,-7,10);
	/* Ceiling */
	glColor3f(0,0,.75);
	glVertex3f(-10,10,-10);
	glVertex3f(10,10,-10);
	glVertex3f(10,10,10);
	glVertex3f(-10,10,10);
	/* Walls */
	glColor3f(0,0,0.5);
	glVertex3f(-10,-10,10);
	glVertex3f(10,-10,10);
	glVertex3f(10,10,10);
	glVertex3f(-10,10,10);

	glVertex3f(-10,-10,-10);
	glVertex3f(10,-10,-10);
	glVertex3f(10,10,-10);
	glVertex3f(-10,10,-10);

	glVertex3f(10,10,10);
	glVertex3f(10,-10,10);
	glVertex3f(10,-10,-10);
	glVertex3f(10,10,-10);

	glVertex3f(-10,10,10);
	glVertex3f(-10,-10,10);
	glVertex3f(-10,-10,-10);
	glVertex3f(-10,10,-10);
	glEnd();
}
bool Room::isFrontface(int faceindex, Camera camera) {

}






