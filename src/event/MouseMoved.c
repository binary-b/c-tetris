#include "event/Event.r"
#include "event/MouseEvent.r"
#include "event/MouseEvent.h"

#include "event/MouseMoved.h"

struct MouseMoved {
	struct MouseEvent _p;
};

static struct Event _MouseMoved = {
	sizeof (struct MouseMoved),
	MouseEvent_ctor,
	NULL,
	MouseEvent_clone,
	NULL,
	MouseEvent_zoom
};

void *MouseMoved = &_MouseMoved;
