/*
 * Leg.h
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#ifndef LEG_H_
#define LEG_H_

#include "GLPiece.h"

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

class Leg: public GLPiece {
public:
	Leg(string name, Side side, Color** colors);
	virtual ~Leg();
	virtual void draw();
	virtual void move(int movet);
	Side getSide();

	virtual GLPiece* cloneState();

	virtual void recoverState(GLPiece* state);

protected:
	Side side;
	float thighAng; //angCoxa;
	float shuttleAng; //angCanela;
	MovimentState moveState; // estado;
	int movimentFrame; // movimentoFrame;

private:
	Leg();
};

}
}
}
}
}

#endif /* LEG_H_ */
