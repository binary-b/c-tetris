#include "gui/IGUIObj.r"
#include "gui/IGUIObj.h"

#include <assert.h>
#include "debug.h"

int update ( void *_self ) {
	const struct IGUIObj **self = _self;
	int ret = 0;

	assert ( *self );
	if ( (*self)->update ) {
		ret = (*self)->update ( _self );
	}

	return ret;
}

void draw ( void *_self ) {
	const struct IGUIObj **self = _self;

	assert ( *self );
	if ( (*self)->draw ) {
		(*self)->draw ( _self );
	}
}
