#include <string.h>
#include <assert.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "gui/IGUIHandler.r"
#include "gui/View.r"
#include "game/Board.h"

#include "IClass.h"
#include "gui/IGUIObj.h"
#include "gui/View.h"
#include "game/Block.h"

#include "event/Event.h"
#include "event/KeyEvent.h"
#include "event/ResizeEvent.h"

#include "rect.h"

#include "debug.h"

struct Board {
	struct View _p;
	int width, height;		// of game board
	bool *board;
	void *block;

	// for user input
	bool fast;				// if true block should move faster
	enum block_dir direction;
	

	// for drawing
	float x1, y1;
	float x2, y2;
	float block_size;
};

static void _compute_drawing ( struct Board *self ) {
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
	block_setPosFloat ( block, (PosFloat) {x1, y1} );
	block_setSize ( block, block_size );
}
static void _clearFullRows ( struct Board *self ) {
	int rows_removed = 0;
	int height = self->height;
	int width = self->width;

	for ( int y = 0; y < height; y++ ) {
		int x;
		for ( x = 0; x < width; x++ )
			if ( !self->board [x + y * width] )
				break;

		// the loop has not been breaken
		if ( x == width ) {
			memmove ( self->board + width, self->board, y * width * sizeof self->board[0] );
			memset ( self->board, 0, width * sizeof self->board[0] );
			rows_removed++;
		}
	}
}
static void _newBlock ( struct Board *self ) {
	block_saveOnBoard ( self->block );

	delete ( self->block );
	self->block = new ( Block, self, (Pos) {(self->width - BLOCK_BITMAP_SIZE) / 2,0}, al_map_rgb (255,0,0) );

	_clearFullRows ( self );

	self->fast = false;
}

static void *_ctor ( void *_self, va_list *app ) {
	View_ctor ( _self, app );
	struct Board *self = _self;

	self->width = 13;
	self->height = 25;
	self->fast = false;
	self->direction = BLOCK_NONE;

	self->board = calloc ( self->width * self->height, sizeof self->board[0] );
	self->block = new ( Block, self, (Pos) {(self->width - BLOCK_BITMAP_SIZE) / 2,0}, al_map_rgb (255,0,0) );

	_compute_drawing ( self );

	return _self;
}

static void _dtor ( void *_self ) {
	struct Board *self = _self;
	free ( self->board );
}

void board_tick ( void *_self ) {
	struct Board *self = _self;

	static int tick = 0;
	static int tick_hor = 100;	// for horizontal movement

	if ( tick++ > 22 || (tick > 1 && self->fast) ) {
		if ( !block_move ( self->block, BLOCK_DOWN ) )
			_newBlock ( self );
		tick = 0;
	}
	if ( self->direction == BLOCK_NONE ) {
		tick_hor = 100;
	} else if ( tick_hor++ > 5 ) {
		block_move ( self->block, self->direction );
		tick_hor = 0;
	}
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

	/*
	 * draw all blocks on board
	 */
	for ( int x = 0; x < self->width; x++ )
		for ( int y = 0; y < self->height; y++ )
			if ( self->board [x + y * self->width] ) {
				int x_f = x1 + block_size * x;
				int y_f = y1 + block_size * y;
				al_draw_filled_rectangle ( x_f, y_f, x_f + block_size, y_f + block_size,
						al_map_rgb (255, 255, 255) );
			}

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
	struct Board *self = _self;

	if ( typeOf (ev) == ResizeEvent )
		_compute_drawing ( _self );
	else if ( typeOf (ev) == KeyEvent ) {
		ALLEGRO_EVENT *al_ev = event_getAlEvent ( ev );
		assert ( al_ev != NULL );
		if ( al_ev->type == ALLEGRO_EVENT_KEY_DOWN ) {
			int key = al_ev->keyboard.keycode;
			switch ( key ) {
				case ALLEGRO_KEY_LEFT:
					self->direction = BLOCK_LEFT;
					break;
				case ALLEGRO_KEY_RIGHT:
					self->direction = BLOCK_RIGHT;
					break;
				case ALLEGRO_KEY_ENTER:
				case ALLEGRO_KEY_SPACE:
					block_rot ( self->block );
					break;
				case ALLEGRO_KEY_DOWN:
					self->fast = true;
					break;
			}

			/*block_move ( self->block, direction );*/
		} else if ( al_ev->type == ALLEGRO_EVENT_KEY_UP ) {
			int key = al_ev->keyboard.keycode;
			switch ( key ) {
				case ALLEGRO_KEY_LEFT:
					if ( self->direction == BLOCK_LEFT )
						self->direction = BLOCK_NONE;
					break;
				case ALLEGRO_KEY_RIGHT:
					if ( self->direction == BLOCK_RIGHT )
						self->direction = BLOCK_NONE;
					break;
				case ALLEGRO_KEY_DOWN:
					self->fast = false;
					break;
			}
		}
	}
}

int board_getWidth ( void *_self ) {
	struct Board *self = _self;
	return self->width;
}
int board_getHeight ( void *_self ) {
	struct Board *self = _self;
	return self->height;
}

void board_setBoardBit ( void *_self, int x, int y, bool val ) {
	struct Board *self = _self;
	self->board [x + y * self->width] = val;
}
bool board_getBoardBit ( void *_self, int x, int y ) {
	struct Board *self = _self;
	return self->board [x + y * self->width];
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
