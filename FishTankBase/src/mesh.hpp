#ifndef CMESH_H
#define CMESH_H

#include <GL/glut.h>
#include "Shape.hpp"
#include <iostream>
#include <fstream>  // C++ file I/O
#include "Point.hpp"
#include "Vector.hpp"

#include <assert.h>

//################## class VertexID ################
//used to define a Mesh
class VertexID{
 public:
  int vertIndex;
  int normIndex;
};

//################# class FACE ##############
//used to define a Mesh
class Face{
 public:
  int nVerts;
  VertexID * vert; // array of vertex and normal indices

  Face(){ nVerts = 0; vert = NULL;}
  ~Face(){delete[] vert; nVerts = 0;}
};

//@$@$@$@$@$@$@$@$@$@ Mesh class @$@$@$@$@$@$@$@$@$
class Mesh:public Shape{
 public:
  enum RenderMode {
    MODE_WIRE = 0,
    MODE_SOLID,
    MODE_WIRE_SOLID
  };

  string meshFileName; // holds file name for this Mesh

  Mesh();
  Mesh(string fname);

  typedef double(FuncPtr)(double);

  void drawEdges();
  void drawFaces();
  virtual void draw();

  void freeMesh();
  int isEmpty();
  void makeEmpty();
  Vector newell4(int indx[]);
  void printMesh();
  void readMesh(string fname);
  void setRenderMode(RenderMode m);
  void setScale(float s);
  void writeMesh(char* fname);

 private:
  int numVerts, numNorms, numFaces;
  Point *pt; // array of points
  Vector *norm; // array of normals
  Face *face; // array of faces
  int lastVertUsed;
  int lastNormUsed;
  int lastFaceUsed;
  float scale;
  RenderMode mode;
}; // end of Mesh class


#endif
