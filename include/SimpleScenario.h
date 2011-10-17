/*
 * SimpleScenario.h
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#ifndef SIMPLESCENARIO_H_
#define SIMPLESCENARIO_H_

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "GLPiece.h"
#include "Utils.h"

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

class SimpleScenario: GLPiece {
public:
	SimpleScenario(string textureSrc);
	virtual ~SimpleScenario();
	virtual void draw();
	virtual void move(int movet);

	virtual GLPiece* cloneState();
	virtual void recoverState(GLPiece* state);

private:
	string textureSrc;
	GLuint texture;
};

}

}

}

}

}

#endif /* SIMPLESCENARIO_H_ */
