#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include <mmi/MMIEventListener.h>
#include <mmi/MMIManager.h>
#include <mmi/MMIEvent.h>
#include <mmi/KeyEvent.h>
using namespace br::ufscar::lince::mmi;

#include <mmi/wii/WiiEvent.h>
using namespace br::ufscar::lince::mmi::wii;

#include "Puppet.h"
#include "Camera.h"

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

class EventHandler : public MMIEventListener {
public:
	EventHandler(Puppet* target, Camera* camera);
	~EventHandler();

	bool receiveEvent(
			MMIEvent* ev);

	void handleEvent(MMIEvent* ev);

private:
	Puppet* puppet;
	Camera* camera;
};


}
}
}
}
}

#endif /*EVENTHANDLER_H_*/
