#include <stdlib.h>
#include <string.h>
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

struct Block {
	struct Object _p;
	bool *bitmap;
	Pos pos;
	void *board;

	// for drawing
	PosFloat pos_f;
	float size;
	ALLEGRO_COLOR color;
};

static void *_ctor ( void *_self, va_list *app ) {
	struct Block *self = _self;

	self->bitmap = calloc ( sizeof (bool), BLOCK_BITMAP_SIZE * BLOCK_BITMAP_SIZE );
	self->board = va_arg ( *app, void * );
	self->pos = va_arg ( *app, Pos );
	self->color = va_arg ( *app, ALLEGRO_COLOR );

	self->pos_f = (PosFloat) {0, 0};
	self->size = 0;

	// test
	bool bitmap [] = {
		false, false, false, false,
		false, false, false, true,
		true, true, true, true,
		false, false, false, false,
	};
	memcpy ( self->bitmap, bitmap, sizeof bitmap );;

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
void block_setPos ( void *_self, Pos pos ) {
	struct Block *self = _self;
	self->pos = pos;
}
Pos block_getPos ( void *_self ) {
	struct Block *self = _self;
	return self->pos;
}
void block_setColor ( void *_self, ALLEGRO_COLOR color ) {
	struct Block *self = _self;
	self->color = color;
}
ALLEGRO_COLOR block_getColor ( void *_self ) {
	struct Block *self = _self;
	return self->color;
}

void block_rot ( void *block ) {
}
void block_move ( void *block ) {
}

void block_computePosFloat ( void *_self, PosFloat pos_f ) {
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
