#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <allegro5/allegro5.h>

#include "macros.h"

#define BLOCK_BITMAP_SIZE 4

extern void *Block;

enum block_dir {
	BLOCK_NONE,
	BLOCK_DOWN,
	BLOCK_RIGHT,
	BLOCK_LEFT
};

void block_setBoard ( void *block, void *board );
void *block_getBoard ( void *block );
//void block_setPos ( void *block, Pos pos );
//Pos block_getPos ( void *block );
void block_setColor ( void *block, ALLEGRO_COLOR color );
ALLEGRO_COLOR block_getColor ( void *block );
void block_saveOnBoard ( void *block );

void block_rot ( void *block );
bool block_move ( void *block, enum block_dir );

// for drawing
void block_setPosFloat ( void *block, PosFloat pos_f );
PosFloat block_getPosFloat ( void *block );
void block_setSize ( void *block, float size );
float block_getSize ( void *block );


#endif
