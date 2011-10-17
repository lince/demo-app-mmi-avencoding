#ifndef UTIL_H_
#define UTIL_H_

#include <GL/glu.h>
#include <cmath>
#include <string>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;

void drawLineCylinder(float radiusSub, float radiusInf,
		float hight, int slicesH=20, int slicesV=20);

void drawSolidCylinder(float radiusSub, float radiusInf,
		float hight, int slicesH=20, int slicesV=20);

float seno(float angGraus);

float cosseno(float angGraus);

//void paintSkinColor();

//void paintLightBlueColor();

//void paintDarkBlueColor();

GLuint loadTextureRAW(string filename);

#endif /* UTIL_H_ */
