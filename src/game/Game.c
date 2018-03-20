#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro5.h>

#include "gui/IGUIHandler.r"
#include "gui/View.r"
#include "game/Game.h"

#include "IClass.h"
#include "gui/IGUIObj.h"
#include "gui/IGUIHandler.h"
#include "gui/View.h"

#include "event/ResizeEvent.h"
#include "event/KeyEvent.h"

#include "game/Board.h"

#include "debug.h"

struct Game {
	struct View _p;
	void *board;

	// timer
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *queue;
};

static void *_ctor ( void *_self, va_list *app ) {
	View_ctor ( _self, app );
	struct Game *self = _self;

	Rect r = view_getRect (self);
	r.w = r.w * 10 / 8;
	self->board = new ( Board, r );

	self->timer = al_create_timer ( 1 / (double) 60 );
	self->queue = al_create_event_queue ();
	al_register_event_source ( self->queue, al_get_timer_event_source (self->timer) );

	al_start_timer ( self->timer );

	// set random seed for the game
	srand ( time (0) );

	return _self;
}

static void _dtor ( void *_self ) {
	struct Game *self = _self;

	delete ( self->board );
	al_destroy_event_queue ( self->queue );
	al_destroy_timer ( self->timer );
}

static int _update ( void *_self ) {
	struct Game *self = _self;
	ALLEGRO_EVENT al_ev;

	while ( al_get_next_event (self->queue, &al_ev) ) {
		if ( al_ev.type == ALLEGRO_EVENT_TIMER ) {
			board_tick ( self->board );
		}
	}
	return 0;
}
static void _draw ( void *_self ) {
	struct Game *self = _self;

	view_zoomIn ( self->board );
	draw ( self->board );
	view_zoomRestore ( self->board );
}

static void _event ( void *_self, void *ev ) {
	struct Game *self = _self;

	if ( typeOf (ev) == ResizeEvent ) {
		Rect r = view_getRect ( self );
		/*r.x += 20;*/
		/*r.y += 10;*/
		/*r.w -= 40;*/
		/*r.h -= 10;*/
		/*r.w = r.w * 8 / 10;*/
		view_setRect ( self->board, r );
	} else if ( typeOf (ev) == KeyEvent ) {
		event ( self->board, ev );
	}
}

struct IGUIHandler _Game = {
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
