/*
 * Util.h
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#ifndef GLPIECE_H_
#define GLPIECE_H_

const int FRAMES_PER_FASE = 9;

#include <string>
#include <vector>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "Color.h"

using namespace std;

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

enum Side {
	RIGHT,
	LEFT
};

enum MovimentState {
	STOPPED,
	RISING_FRONT,
	DOWN_FRONT,
	RISING_BACK,
	DOWN_BACK,
};

class GLPiece {
public:
	GLPiece(string pieceName);
	virtual ~GLPiece();
	virtual void draw()=0;
	virtual void setPosition(float x, float y, float z);
	virtual void setPositionX(float x);
	virtual void setPositionY(float y);
	virtual void setPositionZ(float z);
	virtual float getPositionX();
	virtual float getPositionY();
	virtual float getPositionZ();
	virtual string getPieceName();
	virtual void move(int movet=-1)=0;
	virtual GLPiece* cloneState() = 0;
	virtual void recoverState(GLPiece* state);

	static const int GENERIC_MOVE = -1;

protected:
	string pieceName;
	float posX, posY, posZ;
	Color** colors;
	vector<GLPiece*>* pieces;

	void deletePieces();
	void internalCloneState(GLPiece* clonePiece);
};

}
}
}
}
}

#endif /* GLPIECE_H_ */
