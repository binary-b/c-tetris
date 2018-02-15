#include "Class.r"
#include "Class.h"

#include "debug.h"

#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

void *new ( void *_class, ... ) {
	struct Class *class = _class;
	void *p = malloc ( class->size );

	assert ( p );
	*(const struct Class**) p = class;

	if ( class->ctor ) {
		va_list ap;
		va_start ( ap, _class );
		p = class->ctor ( p, &ap );
		va_end ( ap );
	}

	return p;
}

void delete ( void *_self ) {
	const struct Class **self = _self;

	assert ( self );
	if ( (*self)->dtor ) {
		(*self)->dtor ( _self );
	}
	free ( self );
}

void *clone ( void *_self ) {
	const struct Class **self = _self;

	assert ( self );
	if ( (*self)->clone )
		return (*self)->clone ( _self );
	return NULL;
}

bool differ ( void *obj1, void *obj2 ) {
	return true;
}

size_t sizeOf ( void *_self ) {
	const struct Class **self = _self;

	return (*self)->size;
}

const void *typeOf ( void *_self ) {
	const struct Class **self = _self;
	return *self;
}
