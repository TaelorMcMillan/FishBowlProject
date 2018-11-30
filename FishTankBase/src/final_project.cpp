
#include <GL/glew.h>
#include <GL/glut.h>
#include "GL/glaux.h" // for reading bmp files

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#include "Menu.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Point.hpp"

//#include "pixmap/RGBpixmap.h"

#include "solar/Solar.hpp"

// global variables
GLint winWidth = 800, winHeight = 800; // windows size spec.
GLint moving = 0; // 0:not mouse moving mode, 1: in mouse down moving mode
GLint xBegin = 0; // global variable to store the first mouse x coordainte
GLint coordinate = 1; // coordinate system option, 1:MC, 2:WC, 3:VC
GLint type = 2;   // transformation type/option
GLint selected = 0; // index of selected object
bool isShading = false; // shading option for a3

World myWorld;
Camera myCamera;
Light myLight;


//for a4p4
//RGBpixmap pix[6];    // make six (empty) pixmaps
bool isTexture = true;

GLuint texture[7];

struct Image {
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
};
typedef struct Image Image;

int ImageLoad(char *filename, Image *image) {
	FILE *file;
	unsigned long size; // size of the image in bytes.
	unsigned long i; // standard counter.
	unsigned short int planes; // number of planes in image (must be 1)
	unsigned short int bpp; // number of bits per pixel (must be 24)

	char temp; // temporary color storage for bgr-rgb conversion.

	// make sure the file is there.
	if ((file = fopen(filename, "rb")) == NULL) {
		printf("File Not Found : %s\n", filename);
		return 0;
	}

	// seek through the bmp header, up to the width/height:

	fseek(file, 18, SEEK_CUR);

	// read the width

	if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", filename);
		return 0;
	}

	// read the height
	if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
		printf("Error reading height from %s.\n", filename);
		return 0;
	}

	size = image->sizeX * image->sizeY * 3;

	if ((fread(&planes, 2, 1, file)) != 1) {
		printf("Error reading planes from %s.\n", filename);
		return 0;
	}

	if (planes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, planes);
		return 0;
	}

	// read the bitsperpixel
	if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s.\n", filename);
		return 0;
	}

	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
	}

	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);

	image->data = (char *) malloc(size);
	if (image->data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;
	}

	if ((i = fread(image->data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}

	for (i = 0; i < size; i += 3) { // reverse all of the colors. (bgr -> rgb)
		temp = image->data[i];
		image->data[i] = image->data[i + 2];
		image->data[i + 2] = temp;
	}
	return 1;
}

Image* loadTexture(char *filename) {
	Image *image1;
	image1 = (Image *) malloc(sizeof(Image));
	if (image1 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	if (!ImageLoad(filename, image1)) {
		exit(1);
	}
	return image1;
}

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0); //change background colour
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//initialize GLSL
	glUseProgram(0);  //disable GLSL shader

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Create two texture
	glGenTextures(10, texture);

	// first texture configure and loading
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	Image* image1 = loadTexture("earth.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image1->data);

	// second texture configure and loading
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	Image* image2 = loadTexture("sun.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image2->sizeX, image2->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image2->data);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	Image* image3 = loadTexture("grid.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image3->sizeX, image3->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image3->data);

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	Image* image4 = loadTexture("draw.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image4->sizeX, image4->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image4->data);

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	Image* image5 = loadTexture("mandrill.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image5->sizeX, image5->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image5->data);

	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	Image* image6 = loadTexture("red.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image6->sizeX, image6->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image6->data);


	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	Image* image7 = loadTexture("wood.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image7->sizeX, image7->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image7->data);

	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	Image* image8 = loadTexture("feye.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image8->sizeX, image8->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image8->data);
	glDisable(GL_TEXTURE_2D);


	//myWorld.list[4] = &mySolar;        // and to world

	myCamera.setDefaultCamera();       // initialize camera
}


void display(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		myCamera.setProjectionMatrix();
		myWorld.drawWorld();
		glFlush();
		glutSwapBuffers();

}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

void mouseAction(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		moving = 1;
		xBegin = x;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		moving = 0;
	}
	glutPostRedisplay();
}

void mouseMotion(GLint x, GLint y) {
	if (moving) {

		if(coordinate == 3){ //view transformations
			viewTransforms(x);
		}
/*		else if(coordinate == 4){ //light transformations
			lightTransforms(x);
		}*/
		glutPostRedisplay();
	}
}

// the main function
int main(int argc, char** argv) {
	setvbuf(stdout, NULL, _IONBF, 0);  //used for prompt Eclipse console output
	setvbuf(stderr, NULL, _IONBF, 0);
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false);  //used to hide console

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Fish Tank");

	glewInit(); // for GSLS

	menu();
	init();
	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 0;
}

