#ifndef _MOUSE_BUTTON_R_
#define _MOUSE_BUTTON_R_

#include <stdarg.h>
#include "event/MouseEvent.r"

struct MouseButton {
	struct MouseEvent _p;
	int button;
};

void *MouseButton_ctor ( void *_self, va_list *app );

#endif
