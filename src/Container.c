#include "GUIObj.r"
#include "View.r"
#include "Container.h"

#include "Class.h"
#include "GUIObj.h"
#include "List.h"
#include "View.h"

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

struct GUIObj _Container = {
	sizeof (struct Container),
	_ctor,
	_dtor,
	NULL,
	NULL,
	_update,
	_draw
};

void *Container = &_Container;
