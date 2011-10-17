/*
 * Leg.cpp
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#include "../include/Leg.h"
#include "../include/Utils.h"

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

Leg::Leg(string name, Side nSide, Color** colors) : GLPiece(name) {
	this->side = nSide;
	this->colors = colors;
	if (side == LEFT) {
		setPosition(1.5, 0.5, 0.5);
		this->moveState = DOWN_FRONT;
		this->thighAng = -30.f;
		this->shuttleAng = -30.f;
		this->movimentFrame = 1;
	} else if (side == RIGHT) {
		setPosition(-1.5, 0.5, 0.5);
		this->moveState = RISING_BACK;
		this->thighAng = +30.f;
		this->shuttleAng = +30.f;
		this->movimentFrame = 1;
	}
}

Leg::Leg() : GLPiece("") {

}

Leg::~Leg() {
	this->deletePieces();
}
void Leg::draw() {
	glPushMatrix();
		glTranslatef(posX, posY, posZ);

		//coxa
		glPushMatrix();
		glRotatef(thighAng,1,0,0);
		glRotatef(90,1,0,0);
			glPushMatrix();
				colors[2]->paint();
				drawSolidCylinder(0.6,0.7, 5.9);
			glPopMatrix();
			glPushMatrix();
				colors[1]->paint();
				if(side == RIGHT) {
					glTranslatef(0.3,0,0);
					glRotatef(-5,0,1,0.2);
				} else { //LEFT
					glTranslatef(-0.3,0,0);
					glRotatef(5,0,1,0.2);

				}
				glRotatef(3, 1, 0, 0);
				drawSolidCylinder(1.0,1.6, 5.5);
			glPopMatrix();
		glPopMatrix();

		//joelho
		glPushMatrix();
		colors[1]->paint();
		glTranslatef(0, -6.5*cosseno(thighAng),-6.5*seno(thighAng));
		glutSolidSphere(0.99, 10,10);
		glPopMatrix();

		//canela
		glPushMatrix();
			glTranslatef(0, -6.5*cosseno(thighAng),-6.5*seno(thighAng));
			glRotatef(shuttleAng, 1,0,0);
			//canela
			glPushMatrix();
				colors[1]->paint();
				glRotatef(90,1,0,0);
				drawSolidCylinder(0.95, 1.6, 5);
			glPopMatrix();
			//pe�
			glPushMatrix();
				colors[2]->paint();
				glTranslatef(0, -5, 1);
				glScalef(2,1,3);
				glutSolidCube(1);
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();

}
void Leg::move(int movet) {
	if (movimentFrame > FRAMES_PER_FASE) {
		switch (moveState) {
		case RISING_FRONT:
			moveState = DOWN_FRONT;
			break;
		case DOWN_FRONT:
			moveState = DOWN_BACK;
			break;
		case RISING_BACK:
			moveState = RISING_FRONT;
			break;
		case DOWN_BACK:
			moveState = RISING_BACK;
			break;
		}
		movimentFrame = 1;
	} else {
		movimentFrame++;
	}

	switch (moveState) {
	case RISING_FRONT:
		this->thighAng -= 1.5f;
		this->shuttleAng -= 10.5;
		break;
	case DOWN_FRONT:
		this->thighAng += 3.0f;
		this->shuttleAng += 3.0f;
		break;
	case RISING_BACK:
		this->thighAng -= 4.5f;
		this->shuttleAng += 4.5f;
		break;
	case DOWN_BACK:
		this->thighAng += 3.0f;
		this->shuttleAng += 3.0f;
		break;
	}
}

Side Leg::getSide() {
	return this->side;
}

GLPiece* Leg::cloneState() {
	Leg* cLeg = new Leg();
	this->internalCloneState(cLeg);

	/* copy internal variable */
	cLeg->side = this->side;
	cLeg->thighAng = this->thighAng;
	cLeg->shuttleAng = this->shuttleAng;
	cLeg->moveState = this->moveState;
	cLeg->movimentFrame = this->movimentFrame;

	return cLeg;
}

void Leg::recoverState(GLPiece* state) {
	GLPiece::recoverState(state);
	Leg* sLeg = static_cast<Leg*>(state);

	this->side = sLeg->side;
	this->thighAng = sLeg->thighAng;
	this->shuttleAng = sLeg->shuttleAng;
	this->moveState = sLeg->moveState;
	this->movimentFrame = sLeg->movimentFrame;
}


}
}
}
}
}
