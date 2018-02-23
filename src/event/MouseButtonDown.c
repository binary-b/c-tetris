#include "event/IEvent.r"
#include "event/MouseButton.r"
#include "event/MouseEvent.r"

#include "event/MouseButtonDown.h"

struct MouseButtonDown {
	struct MouseButton _p;
};

static struct IEvent _MouseButtonDown = {
	sizeof ( struct MouseButtonDown ),
	MouseButton_ctor,
	NULL,
	NULL,
	NULL,
	MouseEvent_zoom
};

void *MouseButtonDown = &_MouseButtonDown;
