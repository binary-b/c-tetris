#include "gui/GUIHandler.r"
#include <assert.h>

#include "gui/GUIHandler.h"

#include "debug.h"

void event ( void *_self, void *ev ) {
	struct GUIHandler **self = _self;

	assert ( self );
	if ( (*self)->event ) {
		TRACE;
		(*self)->event ( _self, ev );
		TRACE;
	}
}
