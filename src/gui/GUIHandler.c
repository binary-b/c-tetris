#include "gui/GUIHandler.r"
#include <assert.h>

#include "gui/GUIHandler.h"

void event ( void *_self, void *ev ) {
	struct GUIHandler **self = _self;

	assert ( self );
	if ( (*self)->event ) {
		(*self)->event ( _self, ev );
	}
}
