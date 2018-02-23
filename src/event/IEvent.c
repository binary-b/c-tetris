#include <assert.h>

#include "event/IEvent.r"
#include "event/IEvent.h"

void event_zoomOnView ( void *_self, void *view ) {
	struct IEvent **self = _self;

	assert (*self);
	if ( (*self)->zoom )
		(*self)->zoom ( _self, view );
}
