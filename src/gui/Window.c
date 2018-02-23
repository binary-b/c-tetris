#include <stdarg.h>

#include <allegro5/allegro.h>

#include "gui/GUIObj.r"
#include "Object.r"

#include "Class.h"
#include "gui/GUIObj.h"
#include "gui/GUIHandler.h"
#include "gui/Window.h"
#include "Stack.h"
#include "gui/View.h"

#include "event/Event.h"
#include "event/MouseMoved.h"
#include "event/MouseButtonDown.h"
#include "event/MouseButtonUp.h"

#include "macros.h"
#include "debug.h"

struct Window {
	struct Object _p;
	void *views; // stack
	Rect rect;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *queue;
};

void win_setFlags ( void ) {
	al_set_new_display_option ( ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST );
	al_set_new_display_option ( ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST );
}

static void * _ctor ( void *_self, va_list *app ) {
	struct Window *self = _self;
	Rect rect;
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_DISPLAY *display;

	/*
	 * Set display (allegro window) and rect
	 */
	rect = va_arg ( *app, Rect );
	al_set_new_window_position ( rect.x, rect.y );
	display = al_create_display ( rect.w, rect.h );
	al_get_window_position ( display, &rect.x, &rect.y );

	/*
	 * Event queue
	 */
	queue = al_create_event_queue ();
	al_register_event_source ( queue, al_get_display_event_source (display) );
	al_register_event_source ( queue, al_get_mouse_event_source () );

	self->rect = rect;
	self->display = display;
	self->queue = queue;

	self->views = new ( Stack );

	return _self;
}
static void _dtor ( void *_self ) {
	/*TRACEF (( "Window.delete()" ));*/
	struct Window *self = _self;

	al_destroy_event_queue ( self->queue );
	al_destroy_display ( self->display );
}
static void * _clone ( void *_self ) {
	struct Window *self = _self;
	return self;
}

static int _update ( void *_self ) {
	/*TRACEF (( "Window.update()" ));*/
	struct Window *self = _self;
	ALLEGRO_EVENT al_ev;
	void *ev;
	void *view = stack_peek (self->views);

	while ( al_get_next_event (self->queue, &al_ev) ) {
		switch ( al_ev.type ) {
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				return WIN_UPDATE_CLOSED;
			case ALLEGRO_EVENT_MOUSE_AXES:
				ev = new ( MouseMoved, (Pos) {al_ev.mouse.x, al_ev.mouse.y} );
				event ( view, ev );
				delete (ev);
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				ev = new ( MouseButtonDown, (Pos) {al_ev.mouse.x, al_ev.mouse.y}, al_ev.mouse.button );
				event ( view, ev );
				delete (ev);
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				ev = new ( MouseButtonUp, (Pos) {al_ev.mouse.x, al_ev.mouse.y}, al_ev.mouse.button );
				event ( view, ev );
				delete (ev);
				break;
		}
	}

	/*
	 * update top window
	 */
	view = stack_peek (self->views);
	if ( view != NULL )
		update ( view );

	return WIN_UPDATE_NOTHING;
}
static void _draw ( void *_self ) {
	/*TRACEF (( "Window.draw()" ));*/
	struct Window *self = _self;

	void *view = stack_peek (self->views);
	if ( view != NULL )
		draw ( view );
}

void win_addView ( void *_self, void *view ) {
	struct Window *self = _self;
	
	Rect rect = self->rect;
	rect.x = 0, rect.y = 0;
	view_setRect ( view, rect );
	stack_push ( self->views, view );
}

struct GUIObj _Window = {
	sizeof ( struct Window ),
	_ctor,
	_dtor,
	_clone,
	NULL,
	_update,
	_draw
};

void *Window = &_Window;
