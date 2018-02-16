#ifndef _EVENT_R_
#define _EVENT_R_

#include "Class.r"

#define CONT_EVENT \
	CONT_CLASS \
	void (*zoom) ( void *self, void *view );

struct Event {
	CONT_EVENT
};

void event_zoomOnView ( void *_self, void *view );

#endif
