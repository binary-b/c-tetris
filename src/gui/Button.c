#include <allegro5/allegro.h>
#include <stdarg.h>
#include <assert.h>

#include "gui/GUIHandler.r"
#include "gui/View.r"

#include "Class.h"
#include "gui/GUIObj.h"
#include "gui/Button.h"
#include "gui/View.h"
#include "event/MouseEntered.h"
#include "event/MouseLeft.h"
#include "event/MouseButton.h"
#include "event/MouseButtonUp.h"
#include "event/MouseButtonDown.h"

#include "macros.h"
#include "debug.h"

struct Button {
	struct View _p;
	bool active;
	int padding;
	void *label;
	void (*f) (void *self);
};

static void *_ctor ( void *_self, va_list *app ) {
	View_ctor ( _self, app );

	struct Button *self = _self;

	self->active = false;
	self->padding = 10;
	self->label = NULL;
	self->f = va_arg ( *app, void (*) (void *self) );

	return _self;
}

void btn_setLabel ( void *_self, void *label ) {
	struct Button *self = _self;
	Rect rl, rb;

	self->label = label;
	rl = view_getRect ( label );
	rb = view_getRect ( self );

	rb.w = rl.w + 2 * self->padding;
	rb.h = rl.h + 2 * self->padding;
	view_setRect ( self, rb );

	rl.x = self->padding;
	rl.y = self->padding;
	view_setRect ( label, rl );
}
void *btn_getLabel ( void *_self ) {
	struct Button *self = _self;
	return self->label;
}

static void _draw ( void *_self ) {
	struct Button *self = _self;
	ALLEGRO_COLOR color = al_map_rgb ( 255, 0, 0 );

	if ( self->active ) {
		color = al_map_rgb ( 0, 255, 0 );
	}

	al_clear_to_color ( color );
	if ( self->label ) {
		view_zoomIn ( self->label );
		draw ( self->label );
		view_zoomRestore ( self->label );
	}
}

static void _event ( void *_self, void *ev ) {
	struct Button *self = _self;

	if ( typeOf (ev) == MouseEntered )
		self->active = true;
	else if ( typeOf (ev) == MouseLeft )
		self->active = false;
	else if ( typeOf (ev) == MouseButtonDown )
		btn_call (self);
}

void btn_call ( void *_self ) {
	struct Button *self = _self;
	assert ( self->f );
	self->f ( self );
}

struct GUIHandler _Button =  {
	sizeof ( struct Button ),
	_ctor,
	NULL,
	NULL,
	NULL,
	NULL,
	_draw,
	_event
};

void *Button = &_Button;
