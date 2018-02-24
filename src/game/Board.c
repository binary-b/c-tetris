#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "gui/IGUIHandler.r"
#include "gui/View.r"
#include "game/Board.h"

#include "IClass.h"
#include "gui/IGUIObj.h"
#include "gui/View.h"
#include "game/Block.h"
#include "event/ResizeEvent.h"

#include "rect.h"

#include "debug.h"

struct Board {
	struct View _p;
	int width, height;		// of game board
	bool **board;
	void *block;

	// for drawing
	float x1, y1;
	float x2, y2;
	float block_size;
};

static void _compute_drawing ( struct Board *_self );

static void *_ctor ( void *_self, va_list *app ) {
	View_ctor ( _self, app );
	struct Board *self = _self;

	self->width = 10;
	self->height = 14;

	self->board = calloc ( sizeof (bool), self->width * self->height );

	self->block = new ( Block, self, (Pos) {3,0}, al_map_rgb (255,0,0) );

	_compute_drawing ( self );

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

	_compute_drawing ( self );

	float x1 = self->x1;
	float y1 = self->y1;
	float x2 = self->x2;
	float y2 = self->y2;
	float block_size = self->block_size;

	al_draw_filled_rectangle ( x1, y1, x2, y2, al_map_rgb (20, 20, 20) );

	draw ( self->block );

	ALLEGRO_COLOR line_color = al_map_rgb ( 100, 100, 100 );
	/*
	 * draw horizontal lines
	 */
	for ( int i = 0; i <= self->height; i++ ) {
		al_draw_line ( x1, y1 + block_size * i, x2, y1 + block_size * i, line_color, 1 );
	}
	/*
	 * draw vertical lines
	 */
	for ( int i = 0; i <= self->width; i++ ) {
		al_draw_line ( x1 + block_size * i, y1, x1 + block_size * i, y2, line_color, 1 );
	}
}

static void _event ( void *_self, void *ev ) {
	if ( typeOf (ev) == ResizeEvent )
		_compute_drawing ( _self );
}

static void _compute_drawing ( struct Board *_self ) {
	struct Board *self = _self;

	Rect r = view_getRect ( self );
	float x1, y1, w, h;
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
	x1 = (r.w - w) / 2;
	y1 = (r.h - h) / 2;
	x2 = x1 + w;
	y2 = y1 + h;

	self->x1 = x1;
	self->y1 = y1;
	self->x2 = x2;
	self->y2 = y2;
	self->block_size = block_size;

	void *block = self->block;
	block_computePosFloat ( block, (PosFloat) {x1, y1} );
	block_setSize ( block, block_size );
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
