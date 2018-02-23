#include "event/IEvent.r"
#include "event/MouseEvent.r"
#include "event/MouseEvent.h"

#include "event/MouseMoved.h"

struct MouseMoved {
	struct MouseEvent _p;
};

static struct IEvent _MouseMoved = {
	sizeof (struct MouseMoved),
	MouseEvent_ctor,
	NULL,
	NULL,
	NULL,
	MouseEvent_zoom
};

void *MouseMoved = &_MouseMoved;
