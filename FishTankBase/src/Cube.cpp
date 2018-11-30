#include "Cube.hpp"

extern Camera myCamera;
extern Light myLight;
extern bool isShading;
extern GLuint texture[];
extern bool isTexture;
Cube::Cube()
{  
// your definition of cube vertices and faces

    vertex[0][0] = -1; vertex[0][1] = -1; vertex[0][2] = -1;
    vertex[1][0] = -1; vertex[1][1] = 1; vertex[1][2] = -1;
    vertex[2][0] = 1; vertex[2][1] = 1; vertex[2][2] = -1;
    vertex[3][0] = 1; vertex[3][1] = -1; vertex[3][2] = -1;
    vertex[4][0] = -1; vertex[4][1] = -1; vertex[4][2] = 1;
    vertex[5][0] = -1; vertex[5][1] = 1; vertex[5][2] = 1;
    vertex[6][0] = 1; vertex[6][1] = 1; vertex[6][2] = 1;
    vertex[7][0] = 1; vertex[7][1] = -1; vertex[7][2] = 1;

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

void Cube::drawFace(int i)
{

	if (isTexture) {
		glBindTexture(GL_TEXTURE_2D,texture[i]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(vertex[face[i][0]][0], vertex[face[i][0]][1], vertex[face[i][0]][2]);
		glTexCoord2f(1.0, 0.0);glVertex3f(vertex[face[i][1]][0], vertex[face[i][1]][1], vertex[face[i][1]][2]);
		glTexCoord2f(1.0, 1.0); glVertex3f(vertex[face[i][2]][0], vertex[face[i][2]][1], vertex[face[i][2]][2]);
		glTexCoord2f(0.0, 1.0); glVertex3f(vertex[face[i][3]][0], vertex[face[i][3]][1], vertex[face[i][3]][2]);
		glEnd();


	}
	else {
		if (isShading) {
			GLfloat shade = getShade(i, myLight);
			glColor3f(faceColor[i][0]*shade, faceColor[i][1]*shade, faceColor[i][2]*shade);
		} else {
			glColor3f(faceColor[i][0], faceColor[i][1], faceColor[i][2]);
		}

		glBegin(GL_POLYGON);
		glVertex3fv(vertex[face[i][0]]);
		glVertex3fv(vertex[face[i][1]]);
		glVertex3fv(vertex[face[i][2]]);
		glVertex3fv(vertex[face[i][3]]);
		glEnd();
	}
}

void Cube::draw()
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
bool Cube::isFrontface(int faceindex, Camera camera) {
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

GLfloat Cube::getShade(int faceindex, Light light){
	GLfloat shade = 1, v[4], s[4], temp;

	// assign v the first vertex of face[faceindex]
	v[0] = vertex[face[faceindex][0]][0];
	v[1] = vertex[face[faceindex][0]][1];
	v[2] = vertex[face[faceindex][0]][2];
	v[0] = 1;
	mc.multiplyVector(v);  //compute the position of vertex face[faceindex][0] in WC
	if (pmc != NULL) pmc->multiplyVector(v);

	// compute the light vector s[] = lightposition - face[faceindex][0]
	s[0] = light.getMC().mat[0][3] - v[0];
	s[1] = light.getMC().mat[1][3] - v[1];
	s[2] = light.getMC().mat[2][3] - v[2];

//	//normalize vector s
	temp = sqrt(s[0]*s[0]+s[1]*s[1]+s[2]*s[2]);
	s[0] = s[0]/temp;
	s[1] = s[1]/temp;
	s[2] = s[2]/temp;

    // compute the normal of  face[faceindex] in WC
 	v[0] = faceNormal[faceindex][0];
	v[1] = faceNormal[faceindex][1];
	v[2] = faceNormal[faceindex][2];
	v[3] = 0;
	mc.multiplyVector(v);
	if (pmc != NULL) pmc->multiplyVector(v);

	//normalize face normal
	temp = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	v[0] = v[0]/temp;
	v[1] = v[1]/temp;
	v[2] = v[2]/temp;

	// compute v dot s
	temp = v[0]*s[0]+v[1]*s[1]+v[2]*s[2];

	// compute shade factor
	shade = light.I*light.Rd*temp + light.Ia*light.Ra;

	if (shade < 0) shade = 0;
	if (shade > 1 ) shade = 1;

	return shade;
}
