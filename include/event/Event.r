#ifndef _EVENT_R_
#define _EVENT_R_

#include <stdarg.h>

#include <allegro5/allegro.h>

#include "Object.r"

struct Event {
	struct Object _p;
	ALLEGRO_EVENT *alEvent;
};

void *Event_ctor ( void *self, va_list *app );

#endif
