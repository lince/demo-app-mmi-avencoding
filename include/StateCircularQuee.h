/*
 * StateCircularQuee.h
 *
 *  Created on: Aug 25, 2011
 *      Author: caioviel
 */

#ifndef STATECIRCULARQUEE_H_
#define STATECIRCULARQUEE_H_

#define SLEEPTIME 100 /* Milliseconds */
#define QUEE_MAX_SIZE 90

#include "GLPiece.h"
#include "Camera.h"

#include <map>
using namespace std;

#include <cpputil/Thread.h>
#include <cpputil/SimpleException.h>
using namespace cpputil;

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

struct State {
	long timeStamp;
	GLPiece** statePieces;
	Camera* stateCamera;
	int numPieces;
} typedef State;

class StateCircularQuee : public Thread {
private:
	State** circularQuee;
	int begin;
	int end;

	vector<GLPiece*>* targetPieces;
	Camera* targetCamera;

	bool started;
	bool running;

	unsigned long timeclock;

	pthread_mutex_t statesMutex;

public:
	StateCircularQuee();
	virtual ~StateCircularQuee();

	void addTargetPiece(GLPiece* targetPiece);

	void setTargetCamera(Camera* targetCamera);

	virtual void start();

	virtual void run();

	void stop();

	void backTo(unsigned long timeStamp);
	void goBack(unsigned long milisegunds);

private:
	void addState(State* state);
	void cleanQuee();
};

}
}
}
}
}

#endif /* STATECIRCULARQUEE_H_ */
