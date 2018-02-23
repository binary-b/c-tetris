#include "event/IEvent.r"
#include "event/MouseButton.r"
#include "event/MouseEvent.r"

#include "event/MouseButtonUp.h"

struct MouseButtonUp {
	struct MouseButton _p;
};

static struct IEvent _MouseButtonUp = {
	sizeof ( struct MouseButtonUp ),
	MouseButton_ctor,
	NULL,
	NULL,
	NULL,
	MouseEvent_zoom
};

void *MouseButtonUp = &_MouseButtonUp;
