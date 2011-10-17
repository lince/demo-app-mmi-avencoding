#include "../include/EventHandler.h"

#include <cpputil/Thread.h>
using namespace cpputil;

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

class EventThread : public Thread {
public:
	EventThread(EventHandler* target, MMIEvent* ev);
	~EventThread();
	virtual void run();

private:
	EventHandler* target;
	MMIEvent* ev;
};

EventHandler::EventHandler(Puppet* puppet, Camera* camera) {
	cerr<<"EventHandler::EventHandler() - Construtor!"<<endl;
	this->puppet = puppet;
	this->camera = camera;

	/*WiiMote* wiiMote = new WiiMote(
			new WiiEventPoster(),
			WiiMote::REPORT_ALL);

	try {
		wiiMote->connect();
	} catch(...) {

	}*/
	//MMIManager::getInstance()->connectWiiMote();

	set<string>* evType = new set<string>();
	evType->insert("key");
	evType->insert("wiiEvent");

	MMIManager::getInstance()->addEventListener(this, evType);
}

EventHandler::~EventHandler() {

}

bool EventHandler::receiveEvent(
		MMIEvent* ev) {

	cerr<<"Evento chegou em EventHandler::userMultimodalEventReceived!\n\n\n";
	new EventThread(this, ev);
	return true;
}

void EventHandler::handleEvent(MMIEvent* ev) {
	string type = ev->getEventType();
	if (type == "key") {
		string id = ((KeyEvent*)ev)->getKeyId();
		cout << "\t\tId da tecla: " << id << endl << endl;
		if (id =="WII_BUTTON_UP") {
			puppet->move(Puppet::WALKING);
		} else if (id =="WII_BUTTON_LEFT") {
			puppet->move(Puppet::TURNING_LEFT);
		} else if (id =="WII_BUTTON_RIGHT") {
			puppet->move(Puppet::TURNING_RIGHT);
		} else if (id =="WII_BUTTON_DOWN") {
			puppet->setMoving(Puppet::STOP);
		} else if (id =="WII_BUTTON_PLUS") {
			camera->changeTypeUp();
		} else if (id =="WII_BUTTON_MINUS") {
			camera->changeTypeDown();
		} else if (id == "UP") {
			puppet->setMoving(Puppet::WALKING);
		} else if (id == "LEFT") {
			puppet->setMoving(Puppet::TURNING_LEFT);
		} else if (id == "RIGHT") {
			puppet->setMoving(Puppet::TURNING_RIGHT);
		} else if (id == "DOWN") {
			puppet->setMoving(Puppet::STOP);
		}
	} else if (type == "wiiEvent") {
		WiiEvent* wii = (WiiEvent*)ev;
		MoveAction move = wii->getMoveAction();
		if (move == ::br::ufscar::lince::mmi::wii::UP) {
			puppet->setMoving(Puppet::WALKING);
		} else if (move == ::br::ufscar::lince::mmi::wii::LEFT) {
			puppet->setMoving(Puppet::TURNING_LEFT);
		} else if (move == ::br::ufscar::lince::mmi::wii::DOWN) {
			puppet->setMoving(Puppet::STOP);
		} else if (move == ::br::ufscar::lince::mmi::wii::RIGHT) {
			puppet->setMoving(Puppet::TURNING_RIGHT);
		}
	}
}

EventThread::EventThread(EventHandler* target,
		MMIEvent* ev) : Thread() {

	this->target = target;
	this->ev = ev;
	Thread::start();
}

EventThread::~EventThread() {

}

void EventThread::run() {
	target->handleEvent(ev);
	delete this;
}

}
}
}
}
}
