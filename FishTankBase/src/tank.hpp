#ifndef TANK_HPP_
#define TANK_HPP_

#include <GL/glut.h>

#include "rectangle.hpp"


class tank: public Shape{
protected:
rectangle bl ; //bottom left
rectangle br ; //bottom right
rectangle fl ; //front left
rectangle fr ; //front right
rectangle b ; //bottom
rectangle t ; //top
float ytop ; // y top
float ybot ; //y bottom
float zcl ; // z close
float zf ; //zfar
float xl ; //xleft
float xr ; //xright
float thic ;
public:
	~tank();
	tank();
	void draw();
};


#endif /* tank_HPP_ */
