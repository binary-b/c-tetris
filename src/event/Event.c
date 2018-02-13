#include "Class.r"
#include "Object.r"
#include "event/Event.h"

struct Event {
	struct Object _p;
};

void * _ctor ( void *_self, va_list *app ) {
	return _self;
}
void _dtor ( void *_self ) {
}

struct Class _Event = {
	sizeof ( struct Event ),
	_ctor,
	_dtor,
	NULL,
	NULL
};

void *Event = &_Event;
