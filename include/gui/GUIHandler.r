#ifndef _GUIHANDLER_R_
#define _GUIHANDLER_R_

#include "gui/GUIObj.r"

#define CONT_GUIHANDLER \
	CONT_GUIOBJ \
	void (*event) ( void *view, void *ev );

struct GUIHandler {
	CONT_GUIHANDLER
};

#endif
