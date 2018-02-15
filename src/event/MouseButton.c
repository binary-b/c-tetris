#include "event/Event.r"
#include "event/MouseEvent.r"
#include "event/MouseEvent.h"

#include "event/MouseButton.h"

struct MouseButton {
	struct MouseEvent _p;
};

static struct Event _MouseButton = {
	sizeof (struct MouseButton),
	MouseEvent_ctor,
	NULL,
	MouseEvent_clone,
	NULL,
	MouseEvent_zoom
};

void *MouseButton = &_MouseButton;
