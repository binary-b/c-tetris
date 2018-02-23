#include <allegro5/allegro.h>
#include <stdarg.h>
#include <assert.h>

#include "gui/IGUIHandler.r"
#include "gui/View.r"

#include "IClass.h"
#include "gui/IGUIObj.h"
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
	int val;
	bool active;
	void *label;
	void (*f) (void *self);
};

static void *_ctor ( void *_self, va_list *app ) {
	View_ctor ( _self, app );

	struct Button *self = _self;

	self->active = false;
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

	rb.h = rl.h;
	rb.w = rl.w;
	view_setRect ( self, rb );
	rl.x = 0;
	rl.y = 0;
	view_setRect ( label, rl );
}
void *btn_getLabel ( void *_self ) {
	struct Button *self = _self;
	return self->label;
}

static void _draw ( void *_self ) {
	struct Button *self = _self;
	ALLEGRO_COLOR color = al_map_rgb ( 50, 50, 50 );

	if ( self->active ) {
		color = al_map_rgb ( 150, 150, 150 );
	}

	al_clear_to_color ( color );
	if ( self->label )
		draw ( self->label );
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

void btn_setValue ( void *_self, int val ) {
	struct Button *self = _self;
	self->val = val;
}
int btn_getValue ( void *_self ) {
	struct Button *self = _self;
	return self->val;
}

void btn_call ( void *_self ) {
	struct Button *self = _self;
	/*TRACE;*/
	assert ( self->f );
	self->f ( self );
}

struct IGUIHandler _Button =  {
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
