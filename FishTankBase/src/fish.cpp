#include "fish.hpp"
#include <stdio.h>
fish::fish()
{
//	bl.setParentMC(&mc);
	body.setParentMC(&mc) ;
	tail.setParentMC(&mc) ;
	dorsal.setParentMC(&mc) ;
	larm.setParentMC(&mc) ;
	rarm.setParentMC(&mc) ;
	leye.setParentMC(&mc) ;
	reye.setParentMC(&mc) ;
	size = 1 ;
	xp = 0.0 ;
	yp = 0.0 ;
	zp = 0.0 ;
	otfish(xp, yp, zp) ;
	//5, 0.25, -0.25, 4.25, -4.25, -6.25, 6.25
	//int text, float yt, float yb, float zcl, float zf, float xl, float xr
}

fish::~fish()
{
}

void fish::draw()
{
	reye.scaleChange(-size*0.35) ;
leye.scaleChange(-size*0.35) ;
double adj = 1.0 ;
//shape
body.sx = size*2 ;
body.sy =  size*1.35 ;
dorsal.sx =  size*1.45 ;
dorsal.sz =  size*0.25 ;
dorsal.sy =  size*1.6 ;
tail.sx = size*1.6 ;
tail.sz = size*0.32 ;
tail.sy = size*1.5 ;
rarm.sx = size*1.2 ;
rarm.sy = size*1.25 ;
rarm.sz = size*0.08 ;
larm.sy = size*1.25 ;
larm.sz = size*0.08;
//texture
body.textureID =  3 ;
tail.textureID = 5 ;
reye.textureID = 8 ;
leye.textureID = 8 ;
dorsal.textureID = 4 ;
rarm.textureID = 4 ;
larm.textureID = 4 ;
//scale fish
setsize(0) ;
//move
reye.translate(size*1.35*adj,0,0.5*size*adj) ;
leye.translate(size*1.35*adj,0,0.5*-size*adj) ;
dorsal.translate(-size*0.3*adj,size*0.65*adj,0) ;
tail.translate(-size*2.65*adj, 0, 0) ;
rarm.translate(0,-size*0.60,size*0.60) ;
larm.translate(0,-size*0.6,-size*0.6) ;
//scale
dorsal.rotateMC(0,0,1, 15) ;
tail.rotateMC(0,0,1,270) ;
rarm.rotateMC(1,0,0,148) ;
larm.rotateMC(1,0,0,360-148) ;
reye.rotateMC(1,0,0,90) ;
reye.rotateMC(0,1,0,-60) ;
leye.rotateMC(1,0,0,-90) ;
leye.rotateMC(0,1,0,60) ;
//	tfish(0, 0.0, 0) ;
//	rfish(0,0,0,50) ;
//draw
tfish(0,1.8,0) ;
body.draw();
reye.draw() ;
leye.draw() ;
dorsal.draw() ;
tail.draw() ;
rarm.draw() ;
larm.draw() ;
}

void fish::tfish(double x, double y, double z) {
	body.translate(x,y,z) ;
	tail.translate(x,y,z) ;
	dorsal.translate(x,y,z) ;
	larm.translate(x,y,z) ;
	rarm.translate(x,y,z) ;
	leye.translate(x,y,z) ;
	reye.translate(x,y,z) ;
	xp = xp + x ;
	yp = yp + y ;
	zp = zp + z ;

}
void fish::otfish(double x, double y, double z) {
	body.translate(x,y,z) ;
	tail.translate(x,y,z) ;
	dorsal.translate(x,y,z) ;
	larm.translate(x,y,z) ;
	rarm.translate(x,y,z) ;
	leye.translate(x,y,z) ;
	reye.translate(x,y,z) ;

}
void fish::rfish(double x, double y, double z, double ang) {
	body.rotateRelative(xp,yp,zp,x,y,z,ang) ;
	tail.rotateRelative(xp,yp,zp,x,y,z,ang) ;
	dorsal.rotateRelative(xp,yp,zp,x,y,z,ang) ;
	larm.rotateRelative(xp,yp,zp,x,y,z,ang) ;
	rarm.rotateRelative(xp,yp,zp,x,y,z,ang) ;
	leye.rotateRelative(xp,yp,zp,x,y,z,ang) ;
	reye.rotateRelative(xp,yp,zp,x,y,z,ang) ;

}
void fish::setsize(double size) {
	body.scaleChange(size) ;
	tail.scaleChange(size) ;
	dorsal.scaleChange(size) ;
	larm.scaleChange(size) ;
	rarm.scaleChange(size) ;
	leye.scaleChange(size) ;
	reye.scaleChange(size) ;
	this->size = this->size + size ;

}

