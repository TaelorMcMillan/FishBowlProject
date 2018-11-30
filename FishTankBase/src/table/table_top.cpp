#include "table_top.hpp"

extern Camera myCamera;
extern Light myLight;
extern bool isShading;
extern GLuint texture[];
extern bool isTexture;
table_top::table_top()
{
// your definition of table_top vertices and faces
	textureID = 5 ;
	ytop = 0.25 ; // y top
	ybot = -0.25 ; //y bottom
	zclose = 4.25 ; // z close
	zfar = -4.25 ; //zfar
	xleft = -6.25 ; //xleft
	xright = 6.25 ; //xright
    vertex[0][0] = xleft; vertex[0][1] = ybot; vertex[0][2] = zfar;
    vertex[1][0] = xleft; vertex[1][1] = ytop; vertex[1][2] = zfar;
    vertex[2][0] = xright; vertex[2][1] = ytop; vertex[2][2] = zfar;
    vertex[3][0] = xright; vertex[3][1] = ybot; vertex[3][2] = zfar;
    vertex[4][0] = xleft; vertex[4][1] = ybot; vertex[4][2] = zclose;
    vertex[5][0] = xleft; vertex[5][1] = ytop; vertex[5][2] = zclose;
    vertex[6][0] = xright; vertex[6][1] = ytop; vertex[6][2] = zclose;
    vertex[7][0] = xright; vertex[7][1] = ybot; vertex[7][2] = zclose;

    face[0][0] = 0; face[0][1] = 1; face[0][2] = 2; face[0][3] = 3;
    face[1][0] = 7; face[1][1] = 6; face[1][2] = 5; face[1][3] = 4;
    face[2][0] = 0; face[2][1] = 4; face[2][2] = 5; face[2][3] = 1;
    face[3][0] = 2; face[3][1] = 1; face[3][2] = 5; face[3][3] = 6;
    face[4][0] = 3; face[4][1] = 2; face[4][2] = 6; face[4][3] = 7;
    face[5][0] = 0; face[5][1] = 3; face[5][2] = 7; face[5][3] = 4;

	faceColor[0][0] = 1.0, faceColor[0][1] = 0.0; faceColor[0][2] = 0.0;
	faceColor[1][0] = 0.0, faceColor[1][1] = 1.0; faceColor[1][2] = 0.0;
	faceColor[2][0] = 0.0, faceColor[2][1] = 0.0; faceColor[2][2] = 1.0;
	faceColor[3][0] = 1.0, faceColor[3][1] = 1.0; faceColor[3][2] = 0.0;
	faceColor[4][0] = 1.0, faceColor[4][1] = 0.0; faceColor[4][2] = 1.0;
	faceColor[5][0] = 0.0, faceColor[5][1] = 1.0; faceColor[5][2] = 1.0;

	faceNormal[0][0] = 0.0,faceNormal[0][1] = 0.0,faceNormal[0][2] = -1.0,
	faceNormal[1][0] = 0.0, faceNormal[1][1] = 0.0, faceNormal[1][2] = 1.0;
	faceNormal[2][0] = -1.0, faceNormal[2][1] = 0.0, faceNormal[2][2] = 0.0;
	faceNormal[3][0] = 0.0, faceNormal[3][1] = 1.0, faceNormal[3][2] = 0.0;
	faceNormal[4][0] = 1.0, faceNormal[4][1] = 0.0, faceNormal[4][2] = 0.0;
	faceNormal[5][0] = 0.0, faceNormal[5][1] = -1.0, faceNormal[5][2] = 0.0;


}

void table_top::drawFace(int i)
{
	isTexture = true;
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[textureID]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(vertex[face[i][0]][0], vertex[face[i][0]][1], vertex[face[i][0]][2]);
		glTexCoord2f(1.0, 0.0);glVertex3f(vertex[face[i][1]][0], vertex[face[i][1]][1], vertex[face[i][1]][2]);
		glTexCoord2f(1.0, 1.0); glVertex3f(vertex[face[i][2]][0], vertex[face[i][2]][1], vertex[face[i][2]][2]);
		glTexCoord2f(0.0, 1.0); glVertex3f(vertex[face[i][3]][0], vertex[face[i][3]][1], vertex[face[i][3]][2]);
		glEnd();



}

void table_top::draw()
{
    glPushMatrix();
    this->ctmMultiply();
	glScalef(s, s, s);

    for (int i = 0; i < 6; i++) {
    	if (isFrontface(i, myCamera))
    		drawFace(i);
    }

    glPopMatrix();
}
bool table_top::isFrontface(int faceindex, Camera camera) {
	GLfloat v[4];
	v[0] = faceNormal[faceindex][0];
	v[1] = faceNormal[faceindex][1];
	v[2] = faceNormal[faceindex][2];
	v[3] = 0.0;

	mc.multiplyVector(v);

	if (pmc != NULL) {
		pmc->multiplyVector(v);
		return  (pmc->mat[0][3]-camera.eye.x) * v[0] + (pmc->mat[1][3]-camera.eye.y) * v[1] +  (pmc->mat[2][3]-camera.eye.z) * v[2] < 0;
	} else

	return  (mc.mat[0][3]-camera.eye.x) * v[0] + (mc.mat[1][3]-camera.eye.y) * v[1] +  (mc.mat[2][3]-camera.eye.z) * v[2] < 0;
}


