#ifndef _GUIOBJ_R_
#define _GUIOBJ_R_

#include "Class.r"

#define CONT_GUIOBJ \
	CONT_CLASS \
	int (*update) ( void *obj ); \
	void (*draw) ( void *obj );

struct GUIObj {
	CONT_GUIOBJ
};

#endif
