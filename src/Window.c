#include "GUIObj.r"
#include "Object.r"

#include "Window.h"

#include "macros.h"
#include "debug.h"

#include <stdarg.h>

#include <allegro5/allegro.h>

struct Window {
	struct Object _p;
	void *views; // stack
	Rect rect;
	ALLEGRO_DISPLAY *display;
};

static void * _ctor ( void *_self, va_list *app ) {
	struct Window *self = _self;

	self->rect = va_arg ( *app, Rect );
	self->display = al_create_display ( self->rect.w, self->rect.h );

	return _self;
}
static void _dtor ( void *_self ) {
	struct Window *self = _self;

	al_destroy_display ( self->display );
}
static void * _clone ( void *_self ) {
	struct Window *self = _self;
}
static bool _diff ( void *obj1, void *obj2 ) {
	return false;
}

static void _draw ( void *_self ) {
	struct Window *self = _self;
	TRACE;
	printf ( "Window: my rect = (%d, %d, %d, %d)\n", self->rect.x, self->rect.y, self->rect.w, self->rect.h );
}
static int _update ( void *_self ) {
	struct Window *self = _self;
	TRACE;

	return 0;
}

struct GUIObj _Window = {
	sizeof ( struct Window ),
	_ctor,
	_dtor,
	_clone,
	_diff,
	_draw,
	_update
};

void *Window = &_Window;
