#include "gui/GUIHandler.r"
#include "gui/View.r"
#include "gui/Container.h"

#include "Class.h"
#include "gui/GUIObj.h"
#include "gui/GUIHandler.h"
#include "List.h"
#include "gui/View.h"

#include "event/Event.h"
#include "event/MouseEvent.h"
#include "event/MouseMoved.h"
#include "event/MouseEntered.h"
#include "event/MouseLeft.h"
#include "event/MouseButton.h"
#include "event/MouseButtonUp.h"
#include "event/MouseButtonDown.h"

#include "macros.h"
#include "rect.h"
#include "debug.h"

struct Container {
	struct View _p;
	void *views;
	void *actView;
};

static void *_ctor ( void *_self, va_list *app ) {
	struct Container *self = _self;

	self->views = new ( List );
	self->actView = NULL;

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

static struct Container *_event_self;
static void *_event_ev;
static void _event_view ( int id, void *view ) {
	Rect rect = view_getRect ( view );
	Pos pos = mev_getPos ( _event_ev );
	void *ev = NULL;

	if ( rect_cont_point ( rect, pos ) ) {
		/*TRACEF (( "Mouse over some view" ));*/
		if ( view == _event_self->actView ) {
 			ev = clone ( _event_ev );
			event_zoomOnView (ev, view);
			event ( view, ev );
		} else {
			_event_self->actView = view;

			ev = new ( MouseEntered, pos );
			event_zoomOnView (ev, view);
			event ( view, ev );
			
		}
	} else if ( view == _event_self->actView ) {
		ev = new ( MouseLeft, pos );
		event_zoomOnView (ev, view);
		event ( view, ev );
		_event_self->actView = NULL;
	}

	delete ( ev );
}
static void _event ( void *_self, void *ev ) {
	struct Container *self = _self;

	if ( typeOf (ev) == MouseMoved ) {
		_event_ev = ev;
		_event_self = self;
		list_apply ( self->views, _event_view );
	} else if ( typeOf (ev) == MouseButtonUp ||
			typeOf (ev) == MouseButtonDown ) {
		event_zoomOnView ( ev, self->actView );
		event ( self->actView, ev );
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
