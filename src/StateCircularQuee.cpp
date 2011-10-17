/*
 * StateCircularQuee.cpp
 *
 *  Created on: Aug 25, 2011
 *      Author: caioviel
 */

#include "../include/StateCircularQuee.h"

#include <cassert>
#include <ctime>
#include <cmath>
using namespace std;

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

void deleteState(State* state) {
	/*assert(state);
	delete state->stateCamera;
	for (int i = 0; i < state->numPieces; i++) {
		delete state->statePieces[i];
	}
	delete state->statePieces;
	delete state;*/
}

State* instanceState(int numPieces) {
	State* state = new State();
	state->numPieces = numPieces;
	state->statePieces = new GLPiece*[numPieces];
	return state;
}

StateCircularQuee::StateCircularQuee() : Thread() {
	circularQuee = new State*[QUEE_MAX_SIZE];
	begin = 0;
	end = 0;
	targetPieces = new vector<GLPiece*>();
	targetCamera = NULL;
	started = false;
	timeclock = 0;

	pthread_mutex_init(&statesMutex, NULL);
}

StateCircularQuee::~StateCircularQuee() {
	delete targetPieces;
	pthread_mutex_lock(&statesMutex);
	cleanQuee();
	delete circularQuee;
	pthread_mutex_unlock(&statesMutex);
	pthread_mutex_destroy(&statesMutex);
}

void StateCircularQuee::addTargetPiece(GLPiece* targetPiece) {
	if (started) {
		throw SimpleException("CirculaStateQuee was already initiated",
				"br::ufscar::lince::xpta::demo::StateCircularQuee",
				"addTargetPiece(GLPiece* )");
	}
	assert(targetPiece);
	pthread_mutex_lock(&statesMutex);
	targetPieces->push_back(targetPiece);
	pthread_mutex_unlock(&statesMutex);
}

void StateCircularQuee::setTargetCamera(Camera* targetCamera) {
	if (started) {
		throw SimpleException("CirculaStateQuee was already initiated",
				"br::ufscar::lince::xpta::demo::StateCircularQuee",
				"setTargetCamera(Camera* )");
	}
	assert(targetCamera);
	pthread_mutex_lock(&statesMutex);
	this->targetCamera = targetCamera;
	pthread_mutex_unlock(&statesMutex);
}

void StateCircularQuee::start() {
	if (started) {
		throw SimpleException("CirculaStateQuee was already initiated",
				"br::ufscar::lince::xpta::demo::StateCircularQuee",
				"start(Camera* )");
	}
	started = true;
	running = true;
	Thread::start();
}

void StateCircularQuee::run() {
	int numPieces = targetPieces->size();
	long clocksPerMillisegund = (CLOCKS_PER_SEC)/1000;
	long referenceTime = clock()/clocksPerMillisegund;
	timeclock = 0;
	while (running) {
		State* state = instanceState(numPieces);

		for (int i = 0; i < numPieces; i++) {
			GLPiece* targetPiece = targetPieces->at(i);
			state->statePieces[i] = targetPiece->cloneState();
		}
		state->stateCamera = targetCamera->cloneCamera();
		state->timeStamp = timeclock;
		addState(state);

		usleep(SLEEPTIME);
		timeclock = clock()/clocksPerMillisegund - referenceTime;
	}
}

void StateCircularQuee::addState(State* state) {
	pthread_mutex_lock(&statesMutex);
	State* toDeleteState = circularQuee[end];
	if (toDeleteState != NULL) {
		deleteState(toDeleteState);
	}
	circularQuee[end++] = state;
	if (end >= QUEE_MAX_SIZE) {
		end = 0;
	}

	if (begin == end) {
		begin++;
	}

	if (begin >= QUEE_MAX_SIZE) {
		begin = 0;
	}
	pthread_mutex_unlock(&statesMutex);
}

void StateCircularQuee::backTo(unsigned long timeStamp) {
	pthread_mutex_lock(&statesMutex);
	if (begin == end) {
		return; /* There is no state in this quee */
	}
	int nearestState = begin;
	unsigned long timeDiference = abs(timeStamp - circularQuee[begin]->timeStamp);

	for (int i = begin; i != end; i++) {
		if (i >= QUEE_MAX_SIZE) {
			i = 0;
		}

		int nTimeDiference = abs(timeStamp - circularQuee[i]->timeStamp);

		if (nTimeDiference < timeDiference) {
			timeDiference = nTimeDiference;
			nearestState = i;
		}
	}
	State* state = circularQuee[nearestState];
	targetCamera->recoverCamera(state->stateCamera);

	for (int i = 0; i < state->numPieces; i++) {
		GLPiece* targetPiece = targetPieces->at(i);
		targetPiece->recoverState( state->statePieces[i] );
		state->statePieces[i] = targetPiece->cloneState();
	}

	cleanQuee();
	begin = end = 0;
	pthread_mutex_unlock(&statesMutex);
}

void StateCircularQuee::goBack(unsigned long milisegunds) {
	unsigned long timestamp = timeclock - milisegunds;
	backTo(timestamp);
}

void StateCircularQuee::stop() {
	if (started) {
		throw SimpleException("CirculaStateQuee was already initiated",
				"br::ufscar::lince::xpta::demo::StateCircularQuee",
				"stop()");
	}
	running = false;
}

void StateCircularQuee::cleanQuee() {
	for (int i = begin; i != end; i++) {
		if (i >= QUEE_MAX_SIZE) {
			i = 0;
		}
		delete circularQuee[i];
	}
}

}
}
}
}
}
