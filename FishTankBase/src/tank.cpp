#include "tank.hpp"
#include <stdio.h>
tank::tank()
{
	bl.setParentMC(&mc);
	br.setParentMC(&mc);
	fl.setParentMC(&mc);
	fr.setParentMC(&mc);
	b.setParentMC(&mc);
	t.setParentMC(&mc);
	ytop = 3.0 ; // y top
	ybot = -1.0; //y bottom
	zcl = 3.0; // z close
	zf = -2.0; //zfar
	xl = -5.3 ; ; //xleft
	xr = 1.3; //xright
	thic = 0.20 ;

	//5, 0.25, -0.25, 4.25, -4.25, -6.25, 6.25
	//int text, float yt, float yb, float zcl, float zf, float xl, float xr
}

tank::~tank()
{
}

void tank::draw()
{
	b.set(8,ybot + thic, ybot, zcl,zf,xl,xr) ;
	t.set(8,ytop, ytop - thic, zcl,zf,xl,xr) ;
	bl.set(8,ytop,ybot + thic,zf + thic, zf,xl, xl + thic) ;
	br.set(8,ytop,ybot+ thic,zf + thic, zf,xr - thic, xr) ;
	fl.set(8,ytop,ybot+ thic,zcl, zcl - thic,xl, xl + thic) ;
	fr.set(8,ytop,ybot+ thic,zcl, zcl - thic,xr - thic, xr) ;
    glPushMatrix();
    this->ctmMultiply();
	glScalef(s, s, s);
	t.draw() ;
	b.draw();
	bl.draw() ;
	br.draw() ;
	fl.draw() ;
	fr.draw() ;
//	cube.draw();
//	pyramid.draw();
	glPopMatrix();
}
