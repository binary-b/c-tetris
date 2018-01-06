#ifndef _CLASS_R_
#define _CLASS_R_

#include "macros.h"

#include <stdlib.h>
#include <stdarg.h>

struct Class {
	size_t size;
	void * (*ctor) ( void *self, va_list *app );
	void (*dtor) ( void *self );
	void * (*clone) ( void *self );
	bool (*differ) ( void *obj1, void *obj2 );
};

#endif
