#ifndef _BOARD_H_
#define _BOARD_H_

extern void *Board;

void board_tick ( void *board );

int board_getWidth ( void *board );
int board_getHeight ( void *board );

void board_setBoardBit ( void *board, int x, int y, bool val );
bool board_getBoardBit ( void *board, int x, int y );

#endif
