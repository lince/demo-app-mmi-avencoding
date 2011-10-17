/*
 * SimpleScenario.cpp
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#include "../include/SimpleScenario.h"

#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

SimpleScenario::SimpleScenario(string textureSrc) : GLPiece("Scenario") {
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

	glGenTextures( 1, &texture );
	texture = loadTextureRAW(textureSrc);
}

SimpleScenario::~SimpleScenario() {
	glDeleteTextures( 1, &texture );
	deletePieces();
}

void SimpleScenario::draw() {
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, texture );
	glBegin(GL_QUADS);
		glTexCoord2d(0.0,0.0);glVertex3f(-200,-11, -200);  //chao
		glTexCoord2d(0.0,1.0);glVertex3f(-200,-11,200);
		glTexCoord2d(1.0,1.0);glVertex3f(200,-11,200);
		glTexCoord2d(1.0,0.0);glVertex3f(200,-11,-200);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0,0.0);glVertex3f(-200,89, -200);  //teto
		glTexCoord2d(0.0,1.0);glVertex3f(-200,89,200);
		glTexCoord2d(1.0,1.0);glVertex3f(200,89,200);
		glTexCoord2d(1.0,0.0);glVertex3f(200,89,-200);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0,0.0);glVertex3f(-200,-11,-200);   //parede1
		glTexCoord2d(0.0,1.0);glVertex3f(200,-11,-200);
		glTexCoord2d(1.0,1.0);glVertex3f(200,89,-200);
		glTexCoord2d(1.0,0.0);glVertex3f(-200,89,-200);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0,0.0);glVertex3f(200,-11,-200);    //parede2
		glTexCoord2d(0.0,1.0);glVertex3f(200,-11,200);
		glTexCoord2d(1.0,1.0);glVertex3f(200,89,200);
		glTexCoord2d(1.0,0.0);glVertex3f(200,89,-200);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0,0.0);glVertex3f(200,-11,200);     //parede3
		glTexCoord2d(0.0,1.0);glVertex3f(-200,-11,200);
		glTexCoord2d(1.0,1.0);glVertex3f(-200,89,200);
		glTexCoord2d(1.0,0.0);glVertex3f(200,89,200);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2d(0.0,0.0);glVertex3f(-200,-11,200);    //parede4
		glTexCoord2d(0.0,1.0);glVertex3f(-200,-11,-200);
		glTexCoord2d(1.0,1.0);glVertex3f(-200,89,-200);
		glTexCoord2d(1.0,0.0);glVertex3f(-200,89,200);
	glEnd();

	glDisable( GL_TEXTURE_2D );
}

void SimpleScenario::move(int movet) {

}

GLPiece* SimpleScenario::cloneState() {
	SimpleScenario* clone = new SimpleScenario(textureSrc);
	clone->texture = this->texture;
	this->internalCloneState(clone);
	return clone;
}

void SimpleScenario::recoverState(GLPiece* state) {
	GLPiece::recoverState(state);
	SimpleScenario* nState = static_cast<SimpleScenario*>(state);
	this->texture = nState->texture;
}

}
}
}
}
}
