#ifndef _RECT_H_
#define _RECT_H_

#include "macros.h"

typedef struct {
	int x, y;
	int w, h;
} Rect;

bool rect_cont_point ( Rect rect, Pos pos );

#endif
