#include "GUIObj.r"
#include "GUIObj.h"

#include <assert.h>
#include "debug.h"

int update ( void *_self ) {
	const struct GUIObj **self = _self;
	int ret = 0;

	TRACE;

	assert ( *self );
	if ( (*self)->update ) {
		TRACE;
		ret = (*self)->update ( _self );
	}

	return ret;
}

void draw ( void *_self ) {
	const struct GUIObj **self = _self;

	TRACE;
	assert ( *self );
	if ( (*self)->draw ) {
		TRACE;
		(*self)->draw ( _self );
	}
}
