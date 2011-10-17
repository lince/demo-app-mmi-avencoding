/*
 * Head.h.h
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#ifndef HEAD_H_H_
#define HEAD_H_H_

#include "GLPiece.h"

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

class Head: public GLPiece {
public:
	Head(string name, Color** colors);
	virtual ~Head();

	virtual void draw();

	virtual void move(int movet);

	virtual GLPiece* cloneState();

	virtual void recoverState(GLPiece* state);

private:
	Head();
};

}
}
}
}
}

#endif /* HEAD_H_H_ */
