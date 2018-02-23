#include "IClass.r"
#include "Object.r"
#include "Object.h"

static void *_ctor ( void *_self, va_list *app ) {
	return _self;
}

struct IClass _Object = {
	sizeof ( struct Object ),
	_ctor,
	NULL,
	NULL,
	NULL
};

void *Object = &_Object;
