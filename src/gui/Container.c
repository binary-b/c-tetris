#include "gui/GUIHandler.r"
#include "gui/View.r"
#include "gui/Container.h"

#include "Class.h"
#include "gui/GUIObj.h"
#include "List.h"
#include "gui/View.h"
#include "event/MouseEvent.h"
#include "event/MouseMoved.h"

#include "macros.h"
#include "debug.h"

struct Container {
	struct View _p;
	void *views;
};

static void *_ctor ( void *_self, va_list *app ) {
	struct Container *self = _self;

	self->views = new ( List );

	return _self;
}
static void _dtor ( void *_self ) {
	struct Container *self = _self;

	delete ( self->views );
}

void cont_addView ( void *_self, void *view ) {
	struct Container *self = _self;

	list_addItem ( self->views, view );
}

static void _update_view ( int id, void *obj ) {
	update ( obj );
}
static int _update ( void *_self ) {
	struct Container *self = _self;

	list_apply ( self->views, _update_view );

	return 0;
}

static void _draw_view ( int id, void *obj ) {
	view_zoomIn ( obj );
	draw ( obj );
	view_zoomRestore ( obj );
}
static void _draw ( void *_self ) {
	struct Container *self = _self;

	list_apply ( self->views, _draw_view );
}

static void _event ( void *_self, void *ev ) {
	TRACEF (( "some event have been called" ));
	if ( typeOf (ev) == MouseMoved ) {
		Pos pos = mev_getPos ( ev );
		TRACEF (( "mouse moved to pos (%d, %d)", pos.x, pos.y ));
	}
}

struct GUIHandler _Container = {
	sizeof (struct Container),
	_ctor,
	_dtor,
	NULL,
	NULL,
	_update,
	_draw,
	_event
};

void *Container = &_Container;
