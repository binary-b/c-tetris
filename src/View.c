#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "GUIHandler.r"
#include "Object.r"

#include "View.h"
#include "View.r"

#include "macros.h"
#include "debug.h"

static void *_ctor ( void *_self, va_list *app ) {
	struct View *self = _self;

	self->rect = va_arg ( *app, Rect );
	self->resizable = false;

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

	al_draw_filled_rectangle ( 6, 6, r.w - 6, r.h - 6,
		   al_map_rgb (255, 0, 0) );
}

static void _event ( void *_self, void *ev ) {
	TRACEF ( "some event have been called" );
}

void view_zoomIn ( void *_self ) {
	struct View *self = _self;
	ALLEGRO_BITMAP *bitmap;
	Rect r = self->rect;

	bitmap = al_get_target_bitmap ();
	self->savedBitmap = bitmap;
	al_set_target_bitmap ( al_create_sub_bitmap (bitmap, r.x, r.y, r.w, r.h) );
}
void view_zoomRestore ( void *_self ) {
	struct View *self = _self;
	ALLEGRO_BITMAP *bitmap;
	
	bitmap = al_get_target_bitmap ();
	al_set_target_bitmap ( self->savedBitmap );
	al_destroy_bitmap ( bitmap );
}

void view_setRect ( void *_self, Rect rect ) {
	struct View *self = _self;

	self->rect = rect;
}
Rect view_getRect ( void *_self ) {
	struct View *self = _self;

	return self->rect;
}
void view_setRezisable ( void *_self, bool resizable ) {
	struct View *self = _self;

	self->resizable = resizable;
}
bool view_isRezisable ( void *_self ) {
	struct View *self = _self;

	return self->resizable;
}

void *(*p_ctor) ( void *, va_list *app ) = _ctor;

struct GUIHandler _View = {
	sizeof ( struct View ),
	_ctor,
	_dtor,
	NULL,
	NULL,
	_update,
	_draw,
	_event
};

void *View = &_View;
