#include "event/IEvent.r"
#include "event/Event.r"
#include "event/KeyEvent.h"

struct KeyEvent {
	struct Event _p;
};

struct IEvent _KeyEvent = {
	sizeof (struct KeyEvent),
	Event_ctor,
	NULL,
	NULL,
	NULL,
	NULL
};

void *KeyEvent = &_KeyEvent;
