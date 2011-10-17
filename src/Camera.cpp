/*
 * Camera.cpp
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#include "../include/Camera.h"
#include <iostream>
using namespace std;

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

Camera::Camera(GLPiece* nReference) {
	if (nReference == NULL) {
		//throw Exception!
		cerr<<"Camera::Camera(GLPiece* nReference)\n";
		cerr<<"Null Reference informed to Camera.\n\n";
		exit(1);
	}
	reference = nReference;
	type = CLOSE_REFERENCE;
}

Camera::~Camera() {

}

void Camera::changeTypeUp() {
	switch (type) {
		case CLOSE_REFERENCE:
			type = DISTANT_REFERENCE;
			break;
		case DISTANT_REFERENCE:
			type = WIDE_VIEW;
			break;
		case WIDE_VIEW:
			type = FIXED;
			break;
		case FIXED:
			type = CLOSE_REFERENCE;
			break;
	}
}

void Camera::changeTypeDown() {
	switch (type) {
		case CLOSE_REFERENCE:
			type = FIXED;
			break;
		case DISTANT_REFERENCE:
			type = CLOSE_REFERENCE;
			break;
		case WIDE_VIEW:
			type = DISTANT_REFERENCE;
			break;
		case FIXED:
			type = WIDE_VIEW;
			break;
	}
}

void Camera::point() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	switch(type) {
	case CLOSE_REFERENCE:
		gluLookAt(20 + reference->getPositionX(), 20, 20 + reference->getPositionZ(),
				reference->getPositionX(), 3, reference->getPositionZ(),
				0,1,0);
		break;
	case DISTANT_REFERENCE:
		gluLookAt(-40 + reference->getPositionX(), 10, 40 + reference->getPositionZ(),
				reference->getPositionX(), 3, reference->getPositionZ(),
				0,1,0);
		break;
	case WIDE_VIEW:
		gluLookAt(-10 + reference->getPositionX(), 50, 10+ reference->getPositionZ(),
				reference->getPositionX(), 3,reference->getPositionZ(),
				0,1,0);
		break;
	case FIXED:
		gluLookAt(-20, 5 , 30,
				reference->getPositionX(), 4,reference->getPositionZ(),
				0,1,0);
		break;
	}
}

Camera* Camera::cloneCamera() {
	Camera* clone = new Camera(reference);
	clone->type = this->type;
	return clone;
}

void Camera::recoverCamera(Camera* camera) {
	this->type = camera->type;
	this->reference = camera->reference;
}

}
}
}
}
}
