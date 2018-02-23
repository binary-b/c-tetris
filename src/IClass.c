#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

#include "IClass.r"
#include "IClass.h"

#include "debug.h"

void *new ( void *_class, ... ) {
	struct IClass *class = _class;
	void *p = malloc ( class->size );

	assert ( p );
	*(const struct IClass**) p = class;

	if ( class->ctor ) {
		va_list ap;
		va_start ( ap, _class );
		p = class->ctor ( p, &ap );
		va_end ( ap );
	}

	return p;
}

void delete ( void *_self ) {
	const struct IClass **self = _self;

	if ( !self )
		return;
	if ( (*self)->dtor ) {
		(*self)->dtor ( _self );
	}
	free ( self );
}

void *clone ( void *_self ) {
	const struct IClass **self = _self;
	void *ret;

	assert ( self );
	if ( (*self)->clone )
		return (*self)->clone ( _self );
	else {
		ret = malloc ( (*self)->size );
		if ( ret != NULL )
			memcpy ( ret, _self, (*self)->size );
	}

	return ret;
}

bool differ ( void *obj1, void *obj2 ) {
	return true;
}

size_t sizeOf ( void *_self ) {
	const struct IClass **self = _self;

	return (*self)->size;
}

const void *typeOf ( void *_self ) {
	const struct IClass **self = _self;
	return *self;
}
