/*
 * Body.h
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#ifndef BODY_H_
#define BODY_H_

#include "GLPiece.h"

namespace br {

namespace ufscar {

namespace lince {

namespace xpta {

namespace demo {

class Body: public br::ufscar::lince::xpta::demo::GLPiece {
public:
	Body(string name, Color** colors);
	virtual ~Body();

	virtual void draw();

	virtual void move(int movet);

	virtual GLPiece* cloneState();

	virtual void recoverState(GLPiece* state);

private:
	Body();

};

}

}

}

}

}

#endif /* BODY_H_ */
