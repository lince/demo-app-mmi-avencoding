/*
 * Corpo.h
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#ifndef CORPO_H_
#define CORPO_H_

#include "GLPiece.h"

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

class Puppet: public GLPiece {
public:
	Puppet(string pieceName,
			float x=0.0f, float y=0.0f, float z=0.0f,
			Color** pallet=NULL);

	void setRightArm(GLPiece* rightArm);

	void setLeftArm(GLPiece* leftArm);

	void setRightLeg(GLPiece* rightLeg);

	void setLeftLeg(GLPiece* leftLeg);

	void setHead(GLPiece* head);

	void seBody(GLPiece* body);

	GLPiece* getRightArm();

	GLPiece* getLeftArm();

	GLPiece* getRightLeg();

	GLPiece* getLeftLeg();

	GLPiece* getHead();

	GLPiece* geBody();

	virtual void draw();

	void move();

	virtual void move(int movet);

	void setMoving(int movet);

	virtual ~Puppet();

	virtual GLPiece* cloneState();

	virtual void recoverState(GLPiece* state);

private:
	GLPiece* rightArm;
	GLPiece* leftArm;
	GLPiece* rightLeg;
	GLPiece* leftLeg;
	GLPiece* head;
	GLPiece* body;

	int moving;


	float directionAngle;
	bool isUp;
	int pass;
	float deltaZ;

	Puppet();

public:
	static const int WALKING;
	static const int TURNING_LEFT;
	static const int TURNING_RIGHT;
	static const int STOP;
};

}
}
}
}
}

#endif /* CORPO_H_ */
