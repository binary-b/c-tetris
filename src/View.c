#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "GUIObj.r"
#include "Object.r"

#include "View.h"

#include "macros.h"
#include "debug.h"

struct View {
	struct Object _p;
	Rect rect;
	void *context;		// either View or Window
};

static void *_ctor ( void *_self, va_list *app ) {
	struct View *self = _self;

	self->rect = va_arg ( *app, Rect );

	return _self;
}
static void _dtor ( void *self ) {
}

static int _update ( void *_self ) {
	TRACEF (( "View.update()" ));
	return 0;
}
static void _draw ( void *_self ) {
	TRACEF (( "View.draw()" ));
	struct View *self = _self;
	Rect r = self->rect;

	TRACEF (( "rect: %d, %d, %d, %d", r.x, r.y, r.w, r.h ));
	al_draw_filled_rectangle ( r.x + 6, r.y + 6, r.x + r.w - 6, r.y + r.h - 6,
		   al_map_rgb (255, 0, 0) );
}

view_setRect ( void *_self, Rect rect ) {
	struct View *self = _self;

	self->rect = rect;
}

struct GUIObj _View = {
	sizeof ( struct View ),
	_ctor,
	_dtor,
	NULL,
	NULL,
	_update,
	_draw
};

void *View = &_View;
