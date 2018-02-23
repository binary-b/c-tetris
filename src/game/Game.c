#include <allegro5/allegro5.h>

#include "gui/GUIHandler.r"
#include "gui/View.r"
#include "game/Game.h"

#include "Class.h"
#include "gui/GUIObj.h"
#include "gui/View.h"

#include "game/Board.h"

#include "debug.h"

struct Game {
	struct View _p;
	void *board;
};

static void *_ctor ( void *_self, va_list *app ) {
	View_ctor ( _self, app );
	struct Game *self = _self;

	self->board = new ( Board, view_getRect (self) );

	return _self;
}

static void _dtor ( void *_self ) {
}

static int _update ( void *_self ) {
	return 0;
}
static void _draw ( void *_self ) {
	struct Game *self = _self;

	Rect r = view_getRect ( self );
	r.x += 20;
	r.y += 10;
	r.w -= 40;
	r.h -= 10;
	view_setRect ( self->board, r );

	view_zoomIn ( self->board );
	draw ( self->board );
	view_zoomRestore ( self->board );
}

static void _event ( void *_self, void *ev ) {
}

struct GUIHandler _Game = {
	sizeof ( struct Game ),
	_ctor,
	_dtor,
	NULL,
	NULL,
	_update,
	_draw,
	_event,
};

void *Game = &_Game;
