#ifndef _GUIOBJ_H_
#define _GUIOBJ_H_

#include "Class.r"

#define CONT_GUIOBJ \
	CONT_CLASS \
	void (*draw) ( void *obj ); \
	int (*update) ( void *obj );

struct GUIObj {
	CONT_GUIOBJ
};

#endif
