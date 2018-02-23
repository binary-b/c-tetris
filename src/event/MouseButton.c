#include <stdarg.h>

#include "event/IEvent.r"
#include "event/MouseEvent.r"
#include "event/MouseEvent.h"

#include "event/MouseButton.h"
#include "event/MouseButton.r"

void *MouseButton_ctor ( void *_self, va_list *app ) {
	MouseEvent_ctor ( _self, app );

	struct MouseButton *self = _self;
	self->button = va_arg ( *app, int );

	return _self;
}

int mev_getButton ( void *_self ) {
	struct MouseButton *self = _self;

	return self->button;
}

static struct IEvent _MouseButton = {
	sizeof (struct MouseButton),
	MouseButton_ctor,
	NULL,
	NULL,
	NULL,
	MouseEvent_zoom
};

void *MouseButton = &_MouseButton;
