/*
 * Arm.cpp
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#include "../include/Arm.h"
#include "../include/Utils.h"

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

Arm::Arm(string name, Side nSide, Color** colors) : GLPiece (name){
	this->side = nSide;
	this->colors = colors;
	if (side == RIGHT) {
		setPosition(-3, 5.9, 0);
		this->shoulderAng = 20.;
		this->elbowAng = 0.0;
		this->movimentFrame = 1;
		this->moveState = RISING_BACK;
	} else if (side == LEFT) {
		setPosition(3.0, 5.9, 0);
		this->shoulderAng = -10;
		this->elbowAng = -45;
		this->movimentFrame = 1;
		this->moveState = DOWN_FRONT;
	}
}

Arm::Arm() : GLPiece ("") {

}


Arm::~Arm() {
	this->deletePieces();
}

void Arm::draw() {
	glPushMatrix();

		glTranslatef(posX, posY, posZ);
		glRotatef(shoulderAng, 1,0,0);
		glPushMatrix();
			if (side == RIGHT) {
				glRotatef(-25, 0,0,1);
			} else { //LEFT
				glRotatef(25, 0,0,1);
			}

			glPushMatrix();
				glRotatef(90,1,0,0);
				glPushMatrix();
					colors[1]->paint();
					drawSolidCylinder(0.45,0.45,2.2);
				glPopMatrix(); //cilindro 1
				glPushMatrix();
					colors[2]->paint();
					drawSolidCylinder(0.7,0.7,1.4); //fim cilindro
				glPopMatrix();//fim cilindro
			glPopMatrix(); //rotação de 90
		glPushMatrix();
			if (side == RIGHT) {
				glTranslatef(0.2, -2.9, 0);
				glRotatef(20,0,0,1);
			} else { //LEFT
				glTranslatef(-0.2, -2.9, 0);
				glRotatef(-20,0,0,1);
			}
			glPushMatrix();
				colors[1]->paint();
				glutSolidSphere(1.0,20,20);
			glPopMatrix();

			glPushMatrix();
				glRotatef(elbowAng, 1,0,0);

				glPushMatrix();
					glRotatef(90,1,0,0);
					colors[1]->paint();
					drawSolidCylinder(1.0,1.4,3.2);
				glPopMatrix();
				if (side == RIGHT) {
					this->drawRightHand();
				} else { //LEFT
					this->drawLeftHand();
				}
			glPopMatrix(); //mao
			glPopMatrix(); //mao

	glPopMatrix(); //rotação do braço

	glPopMatrix(); //fecha braço

}

void Arm::drawRightHand() {
	glPushMatrix();
		glTranslatef(0,-3.2 ,0);
			glPushMatrix();
				glRotatef(90,1,0,0);
				drawSolidCylinder(1.4, 1.1, 0.3);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,-0.3 ,0);
				glRotatef(90,1,0,0);
				drawSolidCylinder(1.1, 0.9, 0.7);
			glPopMatrix();
			glPushMatrix();
				glColor3f(1,0,0);            //anel vermelho
				glTranslatef(0,-1 ,0);
				glRotatef(90,1,0,0);
				glutSolidTorus(0.3, 0.55, 20, 20);
			glPopMatrix();
		glPopMatrix();
}

void Arm::drawLeftHand() {
	glPushMatrix();

			glPushMatrix();
				glTranslatef(0,-3.8 ,0);
				glPushMatrix();
					glTranslatef(0,1 ,0);
					glRotatef(90,1,0,0);
					drawSolidCylinder(1.0, 1.1, 1.5);
				glPopMatrix();
				glutSolidSphere(1,20,20);
			glPopMatrix();

			glPushMatrix();
				glRotatef(-10,0,0,1);
				glTranslatef(+1.0,-4.4,0);

				glPushMatrix();
					glTranslatef(0,0,0.5);
					glRotatef(90,1,0,0);
					drawSolidCylinder(0.4,0.28,1.1);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(0,0,0.2);
					glRotatef(90,1,0,0);
					drawSolidCylinder(0.4,0.28,1.3);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(0,0,-0.1);
					glRotatef(90,1,0,0);
					drawSolidCylinder(0.4,0.28,1.1);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(0,0,-0.4);
					glRotatef(90,1,0,0);
					drawSolidCylinder(0.4,0.28,0.9);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.5, -4.6 ,0.6);
				glRotatef(90,1,0,0);
				drawSolidCylinder(0.45,0.35,0.75);
			glPopMatrix();

		glPopMatrix();
}

void Arm::move(int movet) {
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
			shoulderAng -= 1.0f;
			elbowAng -= 3.0;
			break;
		case DOWN_FRONT:
			shoulderAng += 1.0f;
			elbowAng += 3.0;
			break;
		case RISING_BACK:
			shoulderAng -= 2.0f;
			elbowAng -= 2.0f;
			break;
		case DOWN_BACK:
			shoulderAng += 2.0f;
			elbowAng += 2.0;
			break;
	}

}

Side Arm::getSide() {
	return this->side;
}

GLPiece* Arm::cloneState() {
	Arm* cArm = new Arm();
	this->internalCloneState(cArm);

	/* copy internal variable */
	cArm->side = this->side;
	cArm->shoulderAng = this->shoulderAng;
	cArm->elbowAng = this->elbowAng;
	cArm->moveState = this->moveState;
	cArm->movimentFrame = this->movimentFrame;

	return cArm;
}

void Arm::recoverState(GLPiece* state) {
	GLPiece::recoverState(state);
	Arm* sArm = static_cast<Arm*>(state);

	this->side = sArm->side;
	this->shoulderAng = sArm->shoulderAng;
	this->elbowAng = sArm->elbowAng;
	this->moveState = sArm->moveState;
	this->movimentFrame = sArm->movimentFrame;
}

}
}
}
}
}
