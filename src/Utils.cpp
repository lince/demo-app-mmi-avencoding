#include "../include/Utils.h"

typedef unsigned char BYTE;

void drawLineCylinder(float radiusSub, float radiusInf,
		float hight, int slicesH, int slicesV) {

    GLUquadric* p = gluNewQuadric();
    gluQuadricDrawStyle(p,GLU_LINE);
    gluCylinder(p, radiusSub, radiusInf, hight, slicesH, slicesV);
}

void drawSolidCylinder(float radiusSub, float radiusInf,
		float hight, int slicesH, int slicesV) {

    GLUquadric* p = gluNewQuadric();
    gluCylinder(p, radiusSub, radiusInf, hight, slicesH, slicesV);
}

float seno(float angGraus) {
	float rad = (angGraus*M_PI)/180;
	return sin(rad);
}

float cosseno(float angGraus) {
	float rad = (angGraus*M_PI)/180;
	return cos(rad);
}

void paintSkinColor(){
     glColor3f(0.90589,0.76078,0.68235);
}

void paintLightBlueColor(){
	 glColor3f(0.45490,0.78039,0.96471);
}

void paintDarkBlueColor(){
	glColor3f(0.16863,0.13333,0.65490);
}

GLuint loadTextureRAW(string filename) {
  GLuint texture;
  int width, height;
  BYTE* data;
  FILE* file;

  //Open the texture file
  file = fopen( filename.c_str(), "rb" );
  if ( file == NULL ) {
	  cerr<<"loadTextureRAW(string filename)"<<endl;
	  cerr<<"Error trying to open the file '"<<filename<<"'\n\n";
	  //throw exception
  }

  //create the databuffer that will be used to read the file
  width = 256;
  height = 256;
  data = (BYTE*)malloc( width * height * 3);

  //read the file and put the data in a buffer
  fread(data, width * height * 3, 1, file);

  //close the file
  fclose(file);

  //set the texture opened
  glBindTexture( GL_TEXTURE_2D, texture );

  //Map the texture
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );  // constroi mip maps

  //Release the data buffer
  free(data);
  return texture;
}
