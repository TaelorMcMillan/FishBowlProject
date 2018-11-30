/*
 *  file: menu.hpp
 *  author: HBF
 *  date: 2018/09/18
 */

#ifndef MENU_HPP_
#define MENU_HPP_



#include <GL/glew.h>
#include <GL/glut.h>
#include "GL/glaux.h" // for reading bmp files


#include "World.hpp"
#include "Camera.hpp"
#include "solar/Solar.hpp"
#include "pebble.hpp"
void menu();
void MCTransMenu(GLint transOption);
void WCTransMenu(GLint transOption);
void mainMenu(GLint option);
void VCTransMenu(GLint transOption);
void ObjSubMenu(GLint objectOption);
void LightMenu(GLint objectOption);
void A3Menu(GLint objectOption);
void A4Menu(GLint objectOption);
void RotationMenu(GLint option);

void move();
void solarMove(int keepGoing);
void modelTransforms(GLint);
void worldTransforms(GLint);
void viewTransforms(GLint);
void lightTransforms(GLint x);

#endif
