#ifndef _IGUIOBJ_R_
#define _IGUIOBJ_R_

/*
 * update:
 *  - If the returned value is not needed
 *    by convention function should return
 *    (int) 0
 */

#include "IClass.r"

#define CONT_IGUIOBJ \
	CONT_ICLASS \
	int (*update) ( void *obj ); \
	void (*draw) ( void *obj );

struct IGUIObj {
	CONT_IGUIOBJ
};

#endif
