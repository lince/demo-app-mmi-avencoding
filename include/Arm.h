/*
 * Arm.h
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#ifndef ARM_H_
#define ARM_H_

#include "GLPiece.h"

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

class Arm: public GLPiece {
public:
	Arm(string name, Side side, Color** colors);
	virtual ~Arm();
	virtual void draw();
	virtual void move(int movet);
	Side getSide();

	virtual GLPiece* cloneState();

	virtual void recoverState(GLPiece* state);

private:
	Side side;
	float shoulderAng; //angAntebraco;
	float elbowAng; //angBraco;
	MovimentState moveState; //estado;
	int movimentFrame; //movimentoFrame;

private:
	Arm();
	void drawRightHand();
	void drawLeftHand();
};

}
}
}
}
}

#endif /* ARM_H_ */
