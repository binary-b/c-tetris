#include "gui/IGUIHandler.r"
#include <assert.h>

#include "gui/IGUIHandler.h"

void event ( void *_self, void *ev ) {
	struct IGUIHandler **self = _self;

	assert ( self );
	if ( (*self)->event ) {
		(*self)->event ( _self, ev );
	}
}
