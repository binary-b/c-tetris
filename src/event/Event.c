#include <assert.h>

#include "event/Event.r"
#include "event/Event.h"

void event_zoomOnView ( void *_self, void *view ) {
	struct Event **self = _self;

	assert (*self);
	if ( (*self)->zoom )
		(*self)->zoom ( _self, view );
}
