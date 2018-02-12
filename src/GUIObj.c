#include "GUIObj.r"
#include "GUIObj.h"

#include <assert.h>
#include "debug.h"

int update ( void *_self ) {
	const struct GUIObj **self = _self;
	int ret = 0;

	assert ( *self );
	if ( (*self)->update ) {
		ret = (*self)->update ( _self );
	}

	return ret;
}

void draw ( void *_self ) {
	const struct GUIObj **self = _self;

	assert ( *self );
	if ( (*self)->draw ) {
		(*self)->draw ( _self );
	}
}
