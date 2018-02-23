#ifndef _ICLASS_R_
#define _ICLASS_R_

#include "macros.h"

#include <stdlib.h>
#include <stdarg.h>

#define CONT_ICLASS \
	size_t size; \
	void * (*ctor) ( void *self, va_list *app ); \
	void (*dtor) ( void *self ); \
	void * (*clone) ( void *self ); \
	bool (*diff) ( void *obj1, void *obj2 );

struct IClass {
	CONT_ICLASS
};

#endif
