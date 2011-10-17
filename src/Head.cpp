/*
 * Head.h.cpp
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#include "../include/Head.h"
#include "../include/Utils.h"

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

Head::Head(string name, Color** colors) : GLPiece(name) {
	this->setPosition(0, 10, 0);
	this->colors = colors;
}

Head::Head() : GLPiece("") {

}


Head::~Head() {
	// TODO Auto-generated destructor stub
	this->deletePieces();
}

void Head::draw() {
	//pescoco
	glPushMatrix();
	colors[2]->paint();
	glTranslatef(posX, posY-3, posZ);
	glRotatef(270,1,0,0);
	drawSolidCylinder(0.6,0.9,2.5);
	glPopMatrix();

	//cabeca
	glPushMatrix();
	colors[0]->paint();
	glTranslatef(posX, posY, posZ);
	glutSolidSphere(2, 25,25);
	glPopMatrix();

	//chapeu
	glPushMatrix();
		colors[1]->paint();
		glTranslatef(posX, posY, posZ);
		glRotatef(-30,1,0,0);
		glPushMatrix();
			glRotatef(270,1,0,0);
			drawSolidCylinder(2.2,1.9,1.8);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 1.7, 0);
			glRotatef(270,1,0,0);
			drawSolidCylinder(1.9,0,0.4);
		glPopMatrix();
	glPopMatrix();

	//olhos direito
	glPushMatrix();
	colors[1]->paint();
	glTranslatef(posX+1, posY, posZ+1.6);
	glutSolidSphere(0.3, 10,10);
	glPopMatrix();

	//olhos esquerdo
	glPushMatrix();
	colors[1]->paint();
	glTranslatef(posX-1, posY, posZ+1.6);
	glutSolidSphere(0.3, 10,10);
	glPopMatrix();
}

void Head::move(int movet) {
	//TODO nothing;
}

GLPiece* Head::cloneState() {
	Head* cHead = new Head();
	this->internalCloneState(cHead);
	return cHead;
}

void Head::recoverState(GLPiece* state) {
	GLPiece::recoverState(state);
//	Head* sHead = static_cast<Head*>(state);
}

}
}
}
}
}
