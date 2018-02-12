#ifndef _GUIOBJ_R_
#define _GUIOBJ_R_

/*
 * update:
 *  - If the returned value is not needed
 *    by convention function should return
 *    (int) 0
 */

#include "Class.r"

#define CONT_GUIOBJ \
	CONT_CLASS \
	int (*update) ( void *obj ); \
	void (*draw) ( void *obj );

struct GUIObj {
	CONT_GUIOBJ
};

#endif
