/*
 * Body.cpp
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#include "../include/Body.h"
#include "../include/Utils.h"

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

Body::Body(string name, Color** colors) : GLPiece(name) {
	this->setPosition(0, 5.5, 0);
	this->colors = colors;
}

Body::Body() : GLPiece("") {

}

Body::~Body() {
	// TODO Auto-generated destructor stub
	this->deletePieces();
}

void Body::draw() {

	glPushMatrix();
		glTranslatef(posX, posY, posZ);

		//ombro direito
		glPushMatrix();
			colors[1]->paint();
			glTranslatef(2.8, 1.1, 0);
			glutSolidSphere(1.0, 10,10);
		glPopMatrix();

		//ombro esquerdo
		glPushMatrix();
			colors[1]->paint();
			glTranslatef(-2.8, 1.1,0);
			glutSolidSphere(1.0, 10,10);
		glPopMatrix();

		glPushMatrix();
			glPushMatrix();
				//peitoral
				colors[2]->paint();
				glutSolidSphere(2.3, 25,25);
			glPopMatrix();

			glPushMatrix();
				colors[2]->paint();
				glRotatef(-10,1,0,0);
				//glTranslatef(0, 0,0);
				glRotatef(90,1,0,0);
				drawSolidCylinder(2.2,1.5,3);
			glPopMatrix();

			glPushMatrix();
				colors[2]->paint();
				glRotatef(3,1,0,0);
				glTranslatef(0,-2.5,0.6);
				glRotatef(90,1,0,0);
				drawSolidCylinder(1.4,2,1.9);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			colors[1]->paint();
			glScalef(1.1,1,1);
			glTranslatef(0,-5.0,0.3);
			glutSolidSphere(2.0,20,20);
		glPopMatrix();

		glPushMatrix();
			colors[1]->paint();
			glTranslatef(0,-3.7,0.3);
			glRotatef(90,1,0,0);
			drawSolidCylinder(2.0,2.1,0.9);
		glPopMatrix();

	glPopMatrix();
}

void Body::move(int movet) {
	//TODO nothing;
}

GLPiece* Body::cloneState() {
	Body* cBody = new Body();
	this->internalCloneState(cBody);
	return cBody;
}

void Body::recoverState(GLPiece* state) {
	GLPiece::recoverState(state);
	//Body* sBody = static_cast<Body*>(state);
}

}
}
}
}
}
