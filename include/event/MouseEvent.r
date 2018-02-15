#ifndef _MOUSE_EVENT_R_
#define _MOUSE_EVENT_R_

#include <stdarg.h>

#include "Object.r"
#include "macros.h"

struct MouseEvent {
	struct Object _p;
	Pos pos;
};

void *MouseEvent_ctor ( void *self, va_list *app );
void *MouseEvent_clone ( void *self );
void MouseEvent_zoom ( void *self, void *ev );

#endif
