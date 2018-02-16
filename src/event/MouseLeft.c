#include "event/Event.r"
#include "event/MouseEvent.r"
#include "event/MouseEvent.h"

#include "event/MouseLeft.h"

struct MouseLeft {
	struct MouseEvent _p;
};

static struct Event _MouseLeft = {
	sizeof (struct MouseLeft),
	MouseEvent_ctor,
	NULL,
	NULL,
	NULL,
	MouseEvent_zoom
};

void *MouseLeft = &_MouseLeft;
