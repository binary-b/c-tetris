#ifndef _IEVENT_R_
#define _IEVENT_R_

#include "IClass.r"

#define CONT_IEVENT \
	CONT_ICLASS \
	void (*zoom) ( void *self, void *view );

struct IEvent {
	CONT_IEVENT
};

void event_zoomOnView ( void *_self, void *view );

#endif
