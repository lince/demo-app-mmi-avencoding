/*
 * Camera.h
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "GLPiece.h"

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

class Camera {
public:
	Camera(GLPiece* reference);
	void changeTypeUp();
	void changeTypeDown();
	void point();
	~Camera();

	Camera* cloneCamera();
	void recoverCamera(Camera* camera);

private:
	GLPiece* reference;
	enum CameraType {
		CLOSE_REFERENCE,
		DISTANT_REFERENCE,
		WIDE_VIEW,
		FIXED
	};
	CameraType type;
};

}
}
}
}
}

#endif /* CAMERA_H_ */
