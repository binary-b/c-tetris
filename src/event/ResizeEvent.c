#include "event/IEvent.r"
#include "event/Event.r"
#include "event/ResizeEvent.h"

struct ResizeEevnt {
	struct Event _p;
};

struct IEvent _ResizeEvent = {
	sizeof (struct ResizeEevnt),
	Event_ctor,
	NULL,
	NULL,
	NULL,
	NULL
};

void *ResizeEvent = &_ResizeEvent;
