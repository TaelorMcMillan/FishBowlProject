
#ifndef PYRAMID_HPP_
#define PYRAMID_HPP_

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"
#include "Camera.hpp"
#include "Light.hpp"

class Pyramid: public Shape {
protected:
	GLfloat vertex[5][3];
	GLint face[5][4];
	GLfloat faceColor[5][3];
	Vector faceNormal[5];

public:
	Pyramid();
	void draw();
	int textureID ;
	float sx , sy , sz ;

private:
	void drawFace(GLint i);
	bool isFrontface(int faceindex, Camera camera);
	GLfloat getShade(int faceindex, Light light);

};


#endif /* PYRAMID_HPP_ */
