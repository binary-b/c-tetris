#ifndef _VIEW_R_
#define _VIEW_R_

#include <allegro5/allegro.h>

#include "Object.r"
#include "macros.h"

struct View {
	struct Object _p;
	Rect rect;
	bool resizable;
	void *context;		// either View or Window
	ALLEGRO_BITMAP *savedBitmap;	// used by zoom functions
};

#endif
