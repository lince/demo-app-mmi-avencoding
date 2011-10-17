/*
 * GLPiece.cpp
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#include <cpputil/IllegalParameterException.h>
using namespace cpputil;

#include "../include/GLPiece.h"


namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

GLPiece::GLPiece(string pieceName) {
	this->pieceName = pieceName;
	pieces = new vector<GLPiece*>();
}


GLPiece::~GLPiece() {
	deletePieces();
}

void GLPiece::setPosition(float x, float y, float z) {
	this->posX = x;
	this->posY = y;
	this->posZ = z;
}



void GLPiece::setPositionX(float x) {
	this->posX = x;
}



void GLPiece::setPositionY(float y) {
	this->posY = y;
}



void GLPiece::setPositionZ(float z) {
	this->posZ = z;
}



float GLPiece::getPositionX() {
	return posX;
}



float GLPiece::getPositionY() {
	return posY;
}



float GLPiece::getPositionZ() {
	return posZ;
}


string GLPiece::getPieceName() {
	return pieceName;
}

void GLPiece::internalCloneState(GLPiece* clonePiece) {
	if (clonePiece == NULL) {
		throw IllegalParameterException(
				"Passed a NULL GLPiece instance.",
				"br::ufscar::lince::xpta::demo::GLPiece",
				"internalCloneState(GLPiece* )");
	}

	clonePiece->pieceName = this->pieceName;
	clonePiece->setPosition(this->posX, this->posY, this->posZ);
	clonePiece->colors = this->colors;

	for (vector<GLPiece*>::iterator it = pieces->begin();
			it != pieces->end(); it++) {

		GLPiece *innerPiece = *it;
		GLPiece *cloneInnerPiece = innerPiece->cloneState();
		clonePiece->pieces->push_back(cloneInnerPiece);
	}


}

void GLPiece::recoverState(GLPiece* state) {
	if (state == NULL) {
		throw IllegalParameterException(
				"Passed a NULL GLPiece instance.",
				"br::ufscar::lince::xpta::demo::GLPiece",
				"recoverState(GLPiece* )");
	}

	this->setPosition(state->posX, state->posY, state->posZ);
	this->pieceName = state->pieceName;
	this->colors = state->colors;


	vector<GLPiece*>* statePieces = state->pieces;
	vector<GLPiece*>::iterator itState;
	vector<GLPiece*>::iterator itObj;
	for ( itState = statePieces->begin(), itObj = pieces->begin();
			itState != statePieces->end(); itState++, itObj++ ) {

		GLPiece *statePiece = *itState;
		GLPiece *objPiece = *itObj;
		objPiece->recoverState(statePiece);
	}
}

void GLPiece::deletePieces() {
	for (vector<GLPiece*>::iterator it = pieces->begin();
			it != pieces->end(); it++) {

		GLPiece* piece = *it;
		delete piece;
	}
	delete pieces;
}


}
}
}
}
}
