#ifndef SOLAR_H
#define SOLAR_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>
#include "Sphere.hpp"

class Solar : public Shape {
protected:

public:
	Sphere* Sun;
	Sphere* Earth;
	Sphere* Moon;

	Solar();
	~Solar();
	void draw();
	void set_color(GLfloat, GLfloat, GLfloat);
	void scale_change(GLfloat x);
	void translate(GLfloat tx, GLfloat ty, GLfloat tz);
	void rotate_origin(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle);
	void reset();
};

#endif
