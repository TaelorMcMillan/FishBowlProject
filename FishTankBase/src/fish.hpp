#ifndef FISH_HPP_
#define FISH_HPP_

#include <GL/glut.h>

#include "rectangle.hpp"
#include "solar/Sphere.hpp"
#include "Pyramid.hpp"

class fish: public Shape{
protected:
Sphere body ;
Pyramid tail ;
Pyramid dorsal ;
Pyramid larm ;
Pyramid rarm ;
Sphere leye ;
Sphere reye ;
double size ;
float yp ; // y position
float zp ; // z  position
float xp ; //x position
public:
	~fish();
	fish();
	void tfish(double x, double y, double z) ;
	void otfish(double x, double y, double z) ;
	void rfish(double x, double y, double z, double ang) ;
	void setsize(double size) ;
	void draw();
};


#endif /* FISH_HPP_ */
