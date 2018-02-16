#include "event/Event.r"
#include "event/MouseEvent.r"

#include "event/MouseEntered.h"

struct MouseEntered {
	struct MouseEvent _p;
};

static struct Event _MouseEntered = {
	sizeof (struct MouseEntered),
	MouseEvent_ctor,
	NULL,
	NULL,
	NULL,
	MouseEvent_zoom
};

void *MouseEntered = &_MouseEntered;