#include <stdarg.h>

#include <allegro5/allegro.h>

#include <event/IEvent.r>
#include <event/Event.r>
#include <event/Event.h>

void *Event_ctor ( void *_self, va_list *app ) {
	struct Event *self = _self;

	self->alEvent = va_arg ( *app, ALLEGRO_EVENT * );

	return _self;
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
