#ifndef _WINDOW_H_
#define _WINDOW_H_

extern void *Window;

enum win_update {
	WIN_UPDATE_NOTHING,
	WIN_UPDATE_CLOSED
};

void win_addView ( void *self, void *view );
void win_setFlags ( void );

#endif
