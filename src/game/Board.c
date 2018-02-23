#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "gui/IGUIHandler.r"
#include "gui/View.r"
#include "game/Board.h"

#include "gui/View.h"
#include "IClass.h"
#include "game/Block.h"

#include "rect.h"

#include "debug.h"

struct Board {
	struct View _p;
	int width, height;		// of game board
	bool **board;
	void *block;
};

static void *_ctor ( void *_self, va_list *app ) {
	View_ctor ( _self, app );
	struct Board *self = _self;

	self->width = 10;
	self->height = 14;

	self->board = calloc ( sizeof (bool), self->width * self->height );

	self->block = new ( Block, self, (Pos) {3,3}, al_map_rgb (255,0,0) );

	return _self;
}

static void _dtor ( void *_self ) {
	struct Board *self = _self;
	free ( self->board );
}

static int _update ( void *_self ) {
	return 0;
}
static void _draw ( void *_self ) {
	struct Board *self = _self;

	Rect r = view_getRect ( self );
	float x, y, w, h;
	float x2, y2;
	float block_size;

	/*
	 * calculate block size
	 */
	block_size = r.w / (float) self->width;
	if ( block_size > r.h / (float) self->height )
		block_size = r.h / (float) self->height;

	/*
	 * compute position of board
	 */
	w = self->width * block_size;
	h = self->height * block_size;
	x = (r.w - w) / 2;
	y = (r.h - h) / 2;
	x2 = x + w;
	y2 = y + h;

	al_draw_filled_rectangle ( x, y, x2, y2, al_map_rgb (20, 20, 20) );
	/*al_draw_rectangle ( x, y, x2, y2, line_color, 2 );*/

	ALLEGRO_COLOR line_color = al_map_rgb ( 100, 100, 100 );
	/*
	 * draw horizontal lines
	 */
	for ( int i = 0; i <= self->height; i++ ) {
		al_draw_line ( x, y + block_size * i, x2, y + block_size * i, line_color, 1 );
	}
	/*
	 * draw vertical lines
	 */
	for ( int i = 0; i <= self->width; i++ ) {
		al_draw_line ( x + block_size * i, y, x + block_size * i, y2, line_color, 1 );
	}
}

static void _event ( void *_self, void *ev ) {
}

struct IGUIHandler _Board = {
	sizeof ( struct Board ),
	_ctor,
	_dtor,
	NULL,
	NULL,
	_update,
	_draw,
	_event,
};

void *Board = &_Board;
