#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "event/Event.r"
#include "Object.r"

#include "event/MouseEvent.r"
#include "event/MouseEvent.h"

#include "Class.h"
#include "gui/View.h"
#include "macros.h"

void *MouseEvent_ctor ( void *_self, va_list *app ) {
	struct MouseEvent *self = _self;
	self->pos = va_arg ( *app, Pos );
	return _self;
}

void *MouseEvent_clone ( void *_self ) {
	size_t size = sizeof ( _self );
	void *new = malloc ( size );
	memcpy ( new, _self, size );

	return new;
}

void MouseEvent_zoom ( void *_self, void *ev ) {
	struct MouseEvent *self = _self;
	Rect r = view_getRect ( _self );

	self->pos.x -= r.x;
	self->pos.y -= r.y;
}

Pos mev_getPos ( void *_self ) {
	struct MouseEvent *self = _self;
	return self->pos;
}

static struct Event _MouseEvent = {
	sizeof ( struct MouseEvent ),
	MouseEvent_ctor,
	NULL,
	MouseEvent_clone,
	NULL,
	MouseEvent_zoom
};

void *MouseEvent = &_MouseEvent;
