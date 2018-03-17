#include <stdarg.h>

#include <allegro5/allegro.h>

#include <event/IEvent.r>
#include <event/Event.r>
#include <event/Event.h>

#include "debug.h"

void *Event_ctor ( void *_self, va_list *app ) {
	struct Event *self = _self;

	self->alEvent = va_arg ( *app, ALLEGRO_EVENT * );

	return _self;
}

ALLEGRO_EVENT *event_getAlEvent ( void *_self ) {
	struct Event *self = _self;

	return self->alEvent;
}

struct IEvent _Event = {
	sizeof ( struct Event ),
	Event_ctor,
	NULL,
	NULL,
	NULL,
	NULL
};

void *Event = &_Event;
