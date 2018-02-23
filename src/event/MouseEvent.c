#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "event/IEvent.r"
#include "Object.r"

#include "event/MouseEvent.r"
#include "event/MouseEvent.h"

#include "IClass.h"
#include "gui/View.h"

#include "macros.h"

void *MouseEvent_ctor ( void *_self, va_list *app ) {
	struct MouseEvent *self = _self;
	self->pos = va_arg ( *app, Pos );
	return _self;
}

void MouseEvent_zoom ( void *_self, void *view ) {
	struct MouseEvent *self = _self;
	Rect r = view_getRect ( view );

	self->pos.x -= r.x;
	self->pos.y -= r.y;
}

Pos mev_getPos ( void *_self ) {
	struct MouseEvent *self = _self;
	return self->pos;
}

static struct IEvent _MouseEvent = {
	sizeof ( struct MouseEvent ),
	MouseEvent_ctor,
	NULL,
	NULL,
	NULL,
	MouseEvent_zoom
};

void *MouseEvent = &_MouseEvent;
