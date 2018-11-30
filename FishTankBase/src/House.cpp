#include "House.hpp"
#include <stdio.h>
House::House()
{
	cube.setParentMC(&mc);
	pyramid.setParentMC(&mc);
	pyramid.translate(0, 1, 0);
}

House::~House()
{
}

void House::draw()
{
    glPushMatrix();
    this->ctmMultiply();
	glScalef(s, s, s);
	cube.draw();
	pyramid.draw();
	glPopMatrix();
}
