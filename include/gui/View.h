#ifndef _VIEW_H_
#define _VIEW_H_

/*
 * View:
 *  - Abstract super class for objects displayable in Window
 *
 * getRect:
 * setRect:
 *  - value in rect contain RELATIVE position to it's
 *    parent
 *  - there mostly no reason to call this functions in
 *    draw and update functions (see more bellow)
 *
 * zoomIn:
 * 	- The function zooms current canvas on rect.
 * 	  Should be followed by zoomRestore function (after
 * 	  draw call)
 *
 * zoomRestore:
 *  - Restores the canvas to initial state (before zoomIn
 *    call. If zoomIn have not been called before, the behavior
 *    is not defined.
 *
 * draw:
 *  - The drawable area for al_draw_* functions should
 *    be zoomed on rect.
 *    It's because typically view_zoomOn will be called
 *    before.
 */

#include "macros.h"
#include "rect.h"

extern void *View;

void view_zoomIn ( void *self );
void view_zoomRestore ( void *self );

void view_setRect ( void *self, Rect rect );
Rect view_getRect ( void *self );
void view_setRezisable ( void *self, bool resizable );
bool view_isRezisable ( void *self );

#endif
