#include "Class.r"
#include "Class.h"

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
		p = class->ctor ( p, &ap );
		va_end ( ap );
	}

	return p;
}

void delete ( void *_self ) {
	const struct Class **self = _self;

	if ( (*self)->dtor )
		(*self)->dtor ( self );
	free ( self );
}

void *clone ( void *self ) {
	return NULL;
}

bool differ ( void *obj1, void *obj2 ) {
	return true;
}

size_t sizeOf ( void *_self ) {
	const struct Class **self = _self;

	return (*self)->size;
}
