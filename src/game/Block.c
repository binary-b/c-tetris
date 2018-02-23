#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "gui/GUIObj.r"
#include "Object.r"
#include "game/Board.h"

#include "gui/View.h"
#include "Class.h"

#include "macros.h"
#include "debug.h"

struct Block {
	struct Object _p;
	bool *bitmap;
	Pos pos;
	ALLEGRO_COLOR color;
	void *board;
};

static void *_ctor ( void *_self, va_list *app ) {
	struct Block *self = _self;

	self->bitmap = calloc ( sizeof (bool), 4 * 4 );
	self->board = va_arg ( *app, void * );
	self->pos = va_arg ( *app, Pos );
	self->color = va_arg ( *app, ALLEGRO_COLOR );

	// test
	bool bitmap [] = {
		false, false, false, false,
		false, false, false, true,
		true, true, true, true,
		false, false, false, false,
	};
	memcpy ( self->bitmap, bitmap, sizeof *(self->bitmap) );;

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

struct GUIObj _Block = {
	sizeof ( struct Block ),
	_ctor,
	_dtor,
	NULL,
	NULL,
	_update,
	_draw
};

void *Block = &_Block;
