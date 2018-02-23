#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <allegro5/allegro5.h>

#include "macros.h"

extern void *Block;

void block_setBoard ( void *block, void *board );
void *block_getBoard ( void *block );
void block_setPos ( void *block, Pos pos );
Pos block_getPos ( void *block );
void block_setColor ( void *block, ALLEGRO_COLOR color );
ALLEGRO_COLOR block_getColor ( void *block );

void block_rot ( void *block );
void block_move ( void *block );

#endif