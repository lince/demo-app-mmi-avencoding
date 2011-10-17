
/*
 * Corpo.cpp
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#include "../include/Puppet.h"

#include "../include/Head.h"
#include "../include/Arm.h"
#include "../include/Leg.h"
#include "../include/Body.h"
#include "../include/Utils.h"

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

const int Puppet::WALKING = 1;
const int Puppet::TURNING_LEFT = 2;
const int Puppet::TURNING_RIGHT = 3;
const int Puppet::STOP = 4;

Puppet::Puppet(string pieceName,
		float x, float y, float z, Color** pallet) : GLPiece(pieceName) {

	if (pallet == NULL) {
		colors = new Color*[3];
		colors[0] = (Color*) Color::SKIN_COLOR;
		colors[1] = (Color*) Color::LIGHTBLUE_COLOR;
		colors[2] = (Color*) Color::DARKBLUE_COLOR;
	} else {
		colors = pallet;
	}

	head = new Head("head", colors);
	pieces->push_back(head);

	body = new Body("body", colors);
	pieces->push_back(body);

	this->setMoving(Puppet::STOP);

	leftArm = new Arm("leftArm", LEFT, colors);
	pieces->push_back(leftArm);
	//Configura o braço

	rightArm = new Arm("rightArm", RIGHT, colors);
	pieces->push_back(rightArm);
	//Configura o braço

	leftLeg = new Leg("leftLeg", LEFT, colors);
	pieces->push_back(leftLeg);
	//Configura o braço

	rightLeg = new Leg("rightLeg", RIGHT, colors);
	pieces->push_back(rightLeg);
	//Configura o braço

	setPosition(x, y, z);

	this->directionAngle = 0.0f;
	this->isUp = true;
	this->pass = 1;
	this->deltaZ = 0;

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    glShadeModel (GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
}

Puppet::~Puppet() {
	deletePieces();
	/*if (head != NULL) {
		delete head;
	}
	if (body != NULL) {
		delete body;
	}
	if (leftArm != NULL) {
		delete leftArm;
	}
	if (rightArm != NULL) {
		delete rightArm;
	}
	if (leftLeg != NULL) {
		delete leftLeg;
	}
	if (rightLeg != NULL) {
		delete rightLeg;
	}*/
}


void Puppet::setHead(GLPiece* head) {
	this->head = head;
}

void Puppet::seBody(GLPiece* body) {
	this->body = body;
}

void Puppet::setRightLeg(GLPiece* rightLeg) {
	this->rightLeg = rightLeg;
}

void Puppet::setLeftLeg(GLPiece* leftLeg) {
	this->leftLeg = leftLeg;
}

void Puppet::setLeftArm(GLPiece* leftArm) {
	this->leftArm = leftArm;
}

void Puppet::setRightArm(GLPiece* rightArm) {
	this->rightArm = rightArm;
}

GLPiece* Puppet::getHead() {
	return head;
}

GLPiece* Puppet::geBody() {
	return body;
}

GLPiece* Puppet::getRightLeg() {
	return rightLeg;
}

GLPiece* Puppet::getLeftLeg() {
	return leftLeg;
}

GLPiece* Puppet::getLeftArm() {
	return leftArm;
}

GLPiece* Puppet::getRightArm() {
	return rightArm;
}

void Puppet::draw() {
	//Desenha e posiciona o corpo
	glPushMatrix();
	glTranslatef(posX,deltaZ,posZ);
	glRotatef(directionAngle,0,1,0);
		head->draw();
		body->draw();
		rightArm->draw();
		leftArm->draw();
		leftLeg->draw();
		rightLeg->draw();
	glPopMatrix();
}

void Puppet::move(int movet) {
	this->moving = movet;
	move();
	this->moving = Puppet::STOP;

	/*if (movet == Puppet::WALKING) {
		leftLeg->move();
		rightLeg->move();
		leftArm->move();
		rightArm->move();

		//Movimento o "sobe e "desse" do corpo
		if (pass > FRAMES_PER_FASE) {
			isUp = !isUp;
			pass = 1;
		} else {
			pass++;
		}
		if (isUp) {
			deltaZ += 0.05f;
		} else {
			deltaZ -= 0.05f;
		}

		//Movimento o corpo pelo cenário
		float temp = 0.4*cosseno(directionAngle);
		if ((posZ + temp) >= -197 && (posZ + temp) <= 197) {
			posZ += temp;
		}
		temp = 0.4*seno(directionAngle);

		if ((posX + temp) >= -197 && (posX + temp) <= 197) {
			posX += temp;
		}
	} else if (movet == Puppet::TURNING_RIGHT) {
		directionAngle -= 2.5;
	} else if (movet == Puppet::TURNING_LEFT) {
		directionAngle += 2.5;
	}*/
}

void Puppet::setMoving(int movet) {
	if (movet == Puppet::TURNING_LEFT &&
			moving == Puppet::TURNING_RIGHT) {
		moving = Puppet::STOP;
	} else if (movet == Puppet::TURNING_RIGHT &&
			moving == Puppet::TURNING_LEFT) {
		moving = Puppet::STOP;
	} else {
		this->moving = movet;
	}
}

void Puppet::move() {
	if (moving == Puppet::WALKING) {
			leftLeg->move();
			rightLeg->move();
			leftArm->move();
			rightArm->move();

			//Movimento o "sobe e "desse" do corpo
			if (pass > FRAMES_PER_FASE) {
				isUp = !isUp;
				pass = 1;
			} else {
				pass++;
			}
			if (isUp) {
				deltaZ += 0.05f;
			} else {
				deltaZ -= 0.05f;
			}

			//Movimento o corpo pelo cenário
			float temp = 0.4*cosseno(directionAngle);
			if ((posZ + temp) >= -197 && (posZ + temp) <= 197) {
				posZ += temp;
			}
			temp = 0.4*seno(directionAngle);

			if ((posX + temp) >= -197 && (posX + temp) <= 197) {
				posX += temp;
			}
		} else if (moving == Puppet::TURNING_RIGHT) {
			directionAngle -= 2.5;
		} else if (moving == Puppet::TURNING_LEFT) {
			directionAngle += 2.5;
		}
}

Puppet::Puppet() : GLPiece("") {

}

GLPiece* Puppet::cloneState() {
	Puppet* cPuppet = new Puppet();
	this->internalCloneState(cPuppet);

	/* copy internal variable */
	cPuppet->directionAngle = this->directionAngle;
	cPuppet->isUp = this->isUp;
	cPuppet->pass = this->pass;
	cPuppet->deltaZ = this->deltaZ;

	/* set specific pieces */
	/*cPuppet->head = cPuppet->pieces->at(0);
	cPuppet->body = cPuppet->pieces->at(1);
	cPuppet->leftArm = cPuppet->pieces->at(2);
	cPuppet->rightArm = cPuppet->pieces->at(3);
	cPuppet->leftLeg = cPuppet->pieces->at(4);
	cPuppet->rightLeg = cPuppet->pieces->at(5);*/

	return cPuppet;
}

void Puppet::recoverState(GLPiece* state) {
	GLPiece::recoverState(state);
	Puppet* sPuppet = static_cast<Puppet*>(state);

	this->directionAngle = sPuppet->directionAngle;
	this->isUp = sPuppet->isUp;
	this->pass = sPuppet->pass;
	this->deltaZ = sPuppet->deltaZ;
}


}
}
}
}
}
