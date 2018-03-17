#include <stdlib.h>
#include <stdarg.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "gui/IGUIHandler.r"
#include "Object.r"
#include "game/Block.h"
#include "game/Board.h"

#include "gui/View.h"
#include "IClass.h"

#include "macros.h"
#include "debug.h"

/*
 * List of blocks
 *
 * The first BLACK_BITMAP_SIZE ^ 2 values describe
 * the block bitmap.
 * The last one is a field. If its value is true
 * than the whole blocks mid-point is (1.5, 1.5) instead
 * of (2, 2)
 */
bool block_bitmaps [][BLOCK_BITMAP_SIZE * BLOCK_BITMAP_SIZE + 1] = {
	{
		false, false, false, false,
		true , false, false, false,
		true , true , true , true ,
		false, false, false, false,
		false
	},
	{
		false, false, false, false,
		false, false, false, true ,
		true , true , true , true ,
		false, false, false, false,
		false
	},
	{
		true , false, false, false, 
		true , true , true , false, 
		false, false, false, false, 
		false, false, false, false,
		true
	},
	{
		false, false, true , false, 
		true , true , true , false, 
		false, false, false, false, 
		false, false, false, false,
		true
	},
	{
		false, false, false, false,
		false, true , true , false,
		false, true , true , false,
		false, false, false, false,
		false
	},
	{
		false, true , false, false,
		true , true , true , false,
		false, false, false, false,
		false, false, false, false,
		true
	},
	{
		true , false, false, false,
		true , false, false, false,
		true , true , true , false,
		false, false, false, false,
		true
	},
	{
		false, false, false, false,
		false, true , false, false,
		false, true , true , false,
		false, false, false, false,
		false
	},
	{
		true , true , true , false,
		true , false, true , false,
		false, false, false, false,
		false, false, false, false,
		true
	},
	{
		false, false, false, false,
		false, true , true , false,
		false, false, false, false,
		false, false, false, false,
		false
	},
	{
		false, false, false, false,
		true , true , true , false,
		false, false, false, false,
		false, false, false, false,
		true
	},
	{
		false, false, false, false,
		true , true , true , true ,
		false, false, false, false,
		false, false, false, false,
		false
	},
	{
		false, true , false, false,
		false, true , true , false,
		false, false, true , false,
		false, false, false, false,
		true
	},
	{
		false, false, true , false,
		false, true , true , false,
		false, true , false, false,
		false, false, false, false,
		true
	}
};

struct Block {
	struct Object _p;
	bool *bitmap;
	Pos pos;
	void *board;

	// auto values (position of block)
	// x_1 is the position of left-most
	// bit in the block and so on
	int x_1, x_2;
	int y_1, y_2;

	// for drawing
	PosFloat pos_f;
	float size;
	ALLEGRO_COLOR color;
};

static void _compute_pos ( struct Block *self ) {
	int x_1 = BLOCK_BITMAP_SIZE;
	int y_1 = BLOCK_BITMAP_SIZE;
	int x_2 = 0;
	int y_2 = 0;

	for ( int x = 0; x < BLOCK_BITMAP_SIZE; x++ )
		for ( int y = 0; y < BLOCK_BITMAP_SIZE; y++ )
			if ( self->bitmap [x + y*BLOCK_BITMAP_SIZE] ) {
				if ( x_1 > x )
					x_1 = x;
				if ( x_2 < x  )
					x_2 = x;

				if ( y_1 > y )
					y_1 = y;
				if ( y_2 < y )
					y_2 = y;
			}

	self->x_1 = x_1 + self->pos.x;
	self->x_2 = x_2 + self->pos.x;
	self->y_1 = y_1 + self->pos.y;
	self->y_2 = y_2 + self->pos.y;
}

static bool _validate_pos ( struct Block *self ) {
	int width_board = board_getWidth ( self->board ) - 1;
	int height_board = board_getHeight ( self->board ) - 1;

	if ( self->x_1 < 0 || self->x_2 > width_board || self->y_2 > height_board )
		return false;

	for ( int x = 0; x < BLOCK_BITMAP_SIZE; x++ )
		for ( int y = 0; y < BLOCK_BITMAP_SIZE; y++ )
			if ( self->bitmap [x + y * BLOCK_BITMAP_SIZE]
					&& board_getBoardBit (self->board, x + self->pos.x, y + self->pos.y) )
				return false;

	return true;
}

static void *_ctor ( void *_self, va_list *app ) {
	struct Block *self = _self;

	self->bitmap = calloc ( sizeof (bool), BLOCK_BITMAP_SIZE * BLOCK_BITMAP_SIZE );
	self->board = va_arg ( *app, void * );
	self->pos = va_arg ( *app, Pos );
	self->color = va_arg ( *app, ALLEGRO_COLOR );

	self->pos_f = (PosFloat) {0, 0};
	self->size = 0;

	// test
	memcpy ( self->bitmap, block_bitmaps [rand () % 14], sizeof block_bitmaps[0] );;

	_compute_pos ( self );

	return _self;
}

static void _dtor ( void *_self ) {
	struct Block *self = _self;

	free ( self->bitmap );
}

static int _update ( void *_self ) {
	return 0;
}
static void _draw ( void *_self ) {
	struct Block *self = _self;

	float size = self->size;
	float x0 = self->pos_f.x + size*self->pos.x;
	float y0 = self->pos_f.y + size*self->pos.y;

	for ( int x = 0; x < BLOCK_BITMAP_SIZE; x++ )
		for ( int y = 0; y < BLOCK_BITMAP_SIZE; y++ ) {
			if ( self->bitmap [x + y*BLOCK_BITMAP_SIZE] ) {

				float x1 = x0 + size*x;
				float y1 = y0 + size*y;
				float x2 = x1 + size;
				float y2 = y1 + size;

				al_draw_filled_rectangle ( x1, y1, x2, y2, self->color );
			}
		}
}

static void _event ( void *_self, void *ev ) {
}

void *block_getBoard ( void *_self ) {
	struct Block *self = _self;
	return self->board;
}
/*
 *void block_setPos ( void *_self, Pos pos ) {
 *    struct Block *self = _self;
 *    self->pos = pos;
 *}
 *Pos block_getPos ( void *_self ) {
 *    struct Block *self = _self;
 *    return self->pos;
 *}
 */
void block_setColor ( void *_self, ALLEGRO_COLOR color ) {
	struct Block *self = _self;
	self->color = color;
}
ALLEGRO_COLOR block_getColor ( void *_self ) {
	struct Block *self = _self;
	return self->color;
}

void block_saveOnBoard ( void *_self ) {
	struct Block *self = _self;

	for ( int x = 0; x < BLOCK_BITMAP_SIZE; x++ )
		for ( int y = 0; y < BLOCK_BITMAP_SIZE; y++ )
			if ( self->bitmap [x + y * BLOCK_BITMAP_SIZE] ) {
				board_setBoardBit ( self->board, x + self->pos.x, y + self->pos.y, true );
			}
}

void block_rot ( void *_self ) {
	struct Block *self = _self;
	bool old_bitmap [BLOCK_BITMAP_SIZE * BLOCK_BITMAP_SIZE];
	bool *bitmap = self->bitmap;

	int size = 4;
	if ( self->bitmap[BLOCK_BITMAP_SIZE * BLOCK_BITMAP_SIZE] )
		size = 3;

	memcpy ( old_bitmap, bitmap, sizeof old_bitmap );


	for ( int x = 0; x < size; x++ )
		for ( int y = 0; y < size; y++ )
			bitmap [(size-y-1) + x*BLOCK_BITMAP_SIZE] =
				old_bitmap [x + y*BLOCK_BITMAP_SIZE];

	_compute_pos ( self );

	if ( !_validate_pos (self) ) {
		memcpy ( bitmap, old_bitmap, sizeof old_bitmap );
		_compute_pos ( self );
	}

}
bool block_move ( void *_self, enum block_dir direction ) {
	struct Block *self = _self;

	Pos start_pos = self->pos;

	if ( direction == BLOCK_DOWN )
		self->pos.y += 1;
	else if ( direction == BLOCK_RIGHT )
		self->pos.x += 1;
	else if ( direction == BLOCK_LEFT )
		self->pos.x -= 1;

	_compute_pos ( self );

	if ( !_validate_pos (self) ) {
		self->pos = start_pos;
		_compute_pos ( self );
		return false;
	}

	return true;
}

void block_setPosFloat ( void *_self, PosFloat pos_f ) {
	struct Block *self = _self;
	self->pos_f = pos_f;
}

PosFloat block_getPosFloat ( void *_self ) {
	struct Block *self = _self;
	return self->pos_f;
}
void block_setSize ( void *_self, float size ) {
	struct Block *self = _self;
	self->size = size;
}
float block_getSize ( void *_self ) {
	struct Block *self = _self;
	return self->size;
}

struct IGUIHandler _Block = {
	sizeof ( struct Block ),
	_ctor,
	_dtor,
	NULL,
	NULL,
	_update,
	_draw,
	_event
};

void *Block = &_Block;
