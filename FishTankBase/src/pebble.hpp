/*
 * pebble.hpp
 *
 *  Created on: Nov 19, 2018
 *      Author: chris
 */

#ifndef PEBBLE_HPP_
#define PEBBLE_HPP_

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>
#include "solar/Sphere.hpp"

class pebble : public Shape { //makes a carpet of pebbles
protected:

public:
	Sphere* peb;
	float x, y, z ; //initial position of lowest x/y
	double radius ; //radius of pebbles.
	float maxx,maxz;  //distance of pebbles
	int sh ; // changes shuffle factor

	pebble();
	~pebble();
	void draw();
	void drawline(float z) ;
	void set_color(GLfloat r, GLfloat g, GLfloat b);
	void scale_change(GLfloat x);
	void translate(GLfloat tx, GLfloat ty, GLfloat tz);
	void rotate_origin(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle);
	void reset();
};



#endif /* PEBBLE_HPP_ */
