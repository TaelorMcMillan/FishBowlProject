#include "Menu.hpp"

extern GLint coordinate, selected;
extern GLint type, xBegin, a4option;
extern World myWorld;
extern Camera myCamera;
extern Light myLight;
extern bool isShading, isTexture;



extern GLuint ProgramObject;

//extern GLint solarAnimation;
extern Solar mySolar;


// light properties
GLfloat ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
GLfloat diffuse[] = { .6f, .6f, 1.0f, 1.0f };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat positionSolar[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat position[] = { 1.8, 1.8, 1.5, 1.0 };
GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat local_view[] = { 0.0 };

//Material
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 1, 1, 1, 1 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 1, 1, 1, 1 };

void menu() {


	GLint VCTrans_Menu = glutCreateMenu(VCTransMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Translate x ", 4);
	glutAddMenuEntry(" Translate y ", 5);
	glutAddMenuEntry(" Translate z", 6);
	glutAddMenuEntry(" Clipping Near ", 7);
	glutAddMenuEntry(" Clipping Far ", 8);


/*	GLint Light_Menu = glutCreateMenu(LightMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Translate x ", 4);
	glutAddMenuEntry(" Translate y ", 5);
	glutAddMenuEntry(" Translate z", 6);
	glutAddMenuEntry(" Point Light Intensity I", 7);
	glutAddMenuEntry(" Point Light Reflection Rd", 8);
	glutAddMenuEntry(" Ambient Reflection Ra",9);
	glutAddMenuEntry(" Show Point Light ", 10);
	glutAddMenuEntry(" Hide Point Light ", 11);*/


	glutCreateMenu(mainMenu);      // Create main pop-up menu.
	glutAddMenuEntry(" Reset ", 1);
	glutAddSubMenu(" View Transformations ", VCTrans_Menu);
	glutAddMenuEntry(" Quit", 2);
}







void mainMenu(GLint option) {
	switch (option){
		case 1:
			myCamera.setDefaultCamera();
			myWorld.resetWorld();
			myLight.reset();

			glUseProgram(0);  // disable GLSL shader

			glutIdleFunc(NULL);
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
			isShading = false;

			break;
		case 2:
			exit(0);
			break;
	}
	glutPostRedisplay();
}

void VCTransMenu(GLint transOption) {
	coordinate = 3;
	type = transOption;
	glutPostRedisplay();
}
void LightMenu(GLint transOption) {
	coordinate = 4;
	type = transOption;

	if (type == 10) {
		myLight.on = true;
	}
	else if (type == 11) {
		myLight.on = false;
	}

	glutPostRedisplay();
}


void viewTransforms(GLint x){
	GLfloat theta = (xBegin - x > 0) ? 1 : -1;
	if (type == 1) { //view rotate x
		myCamera.rotate(1.0, 0.0, 0.0, theta*0.5);
	}
	else if (type == 2) { //view rotate y
		myCamera.rotate(0.0, 1.0, 0.0, theta*0.5);
	}
	else if(type == 3) { //view rotate z
		myCamera.rotate(0.0, 0.0, 1.0, theta*0.5);
	}
	else if (type == 4) { //view translate x
		myCamera.translate(theta, 0.0, 0.0);
	}
	else if(type == 5) { //view translate y
		myCamera.translate(0.0, theta, 0.0);
	}
	else if(type == 6){ //view translate z
		myCamera.translate(0.0, 0.0, theta);
	}
	else if(type == 7) {
		myCamera.dnear += theta * .1;
	}
	else if(type == 8){
		myCamera.dfar += theta *.1;
	}
}


/*
void lightTransforms(GLint x) {
	GLfloat theta = (xBegin - x > 0) ? 1 : -1;

	if (type == 1) {
		myLight.rotateOrigin(1, 0, 0, theta * 0.5);
	}

	else if (type == 2) {
		myLight.rotateOrigin(0.0, 1.0, 0.0, theta*0.5);
	}

	else if (type == 3) {
		myLight.rotateOrigin(0.0, 0.0, 1.0, theta*0.5);
	}

	else if (type == 4) {
		myLight.translate(theta*0.02, 0.0, 0.0);
	}

	else if (type == 5) {
		myLight.translate(0.0, theta*0.02, 0.0);
	}

	else if (type == 6) {
		myLight.translate(0.0, 0.0, theta*0.02);
	}

	else if (type == 7) {
		myLight.Increment(theta*0.02,0, 0);
	}

	else if (type == 8) {
		myLight.Increment(0, 0, theta*0.02);

	}
	else if (type == 9) {
		myLight.Increment(0, theta*0.02, 0);
	}


	position[0] = myLight.getMC().mat[0][3];
	position[1] = myLight.getMC().mat[1][3];
	position[2] = myLight.getMC().mat[2][3];
	glLightfv(GL_LIGHT0, GL_POSITION, position);

}*/


/*void move(void){
	GLfloat rx,ry,rz, tx, ty, tz;

	if(a3option == 0) {
		rx = myWorld.list[selected]->getMC().mat[0][1];
		ry = myWorld.list[selected]->getMC().mat[1][1];
		rz = myWorld.list[selected]->getMC().mat[2][1];
		myWorld.list[selected]->rotateMC(rz, ry, rz, 0.1);
	}

	else if (a3option == 1) {
		//sun
		rx = myWorld.list[0]->getMC().mat[0][1];
		ry = myWorld.list[0]->getMC().mat[1][1];
		rz = myWorld.list[0]->getMC().mat[2][1];
		myWorld.list[0]->rotateMC(rx,ry,rz, 0.05);


		// earth self rotation
		rx = myWorld.list[1]->getMC().mat[0][1];
		ry = myWorld.list[1]->getMC().mat[1][1];
		rz = myWorld.list[1]->getMC().mat[2][1];
		myWorld.list[1]->rotateMC(rx,ry,rz, 0.4);

		// earth rotate wrt sun
		tx = myWorld.list[0]->getMC().mat[0][3];
		ty = myWorld.list[0]->getMC().mat[1][3];
		tz = myWorld.list[0]->getMC().mat[2][3];
		myWorld.list[1]->translate(-tx, -ty, -tz);
		myWorld.list[1]->rotateOrigin(rx,ry,rz, 0.1);
		myWorld.list[1]->translate(tx, ty, tz);
	}

	glutPostRedisplay();

}*/
/*
void solarMove(int keepGoing)
{
      mySolar.Sun->rotateMC(0, -1, 0, 5);
      mySolar.Earth->rotateMC(mySolar.Earth->getMC().mat[0][0], mySolar.Earth->getMC().mat[1][0], mySolar.Earth->getMC().mat[2][0], 5);
      mySolar.Earth->rotateRelative(mySolar.Sun->getMC().mat[0][3], mySolar.Sun->getMC().mat[1][3],  mySolar.Sun->getMC().mat[2][3], 0, -1, 0, 5);

      mySolar.Moon->rotateMC(mySolar.Moon->getMC().mat[0][0], mySolar.Moon->getMC().mat[1][0], mySolar.Moon->getMC().mat[2][0], 5);
      mySolar.Moon->rotateRelative(mySolar.Sun->getMC().mat[0][3], mySolar.Sun->getMC().mat[1][3],  mySolar.Sun->getMC().mat[2][3], 0, -1, 0, 5);
      mySolar.Moon->rotateRelative(mySolar.Earth->getMC().mat[0][3], mySolar.Earth->getMC().mat[1][3], mySolar.Earth->getMC().mat[2][3],  0, -1, 0, 5);

     if (keepGoing && a4option == 3) {
    	  glutTimerFunc(40, solarMove, 1);
      }
     glutPostRedisplay();
}*/
