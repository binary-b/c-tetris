#ifndef _IGUIHANDLER_R_
#define _IGUIHANDLER_R_

#include "gui/IGUIObj.r"

#define CONT_IGUIHANDLER \
	CONT_IGUIOBJ \
	void (*event) ( void *view, void *ev );

struct IGUIHandler {
	CONT_IGUIHANDLER
};

#endif
