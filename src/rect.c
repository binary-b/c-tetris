#include "rect.h"
#include "macros.h"

bool rect_cont_point ( Rect r, Pos p ) {
	if ( p.x < r.x || p.y < r.y ||
			p.x > r.x + r.w || p.y > r.y + r.h )
		return false;
	else
		return true;
}
