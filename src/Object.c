#include "Class.r"
#include "Object.r"
#include "Object.h"

struct Class _Object = {
	sizeof ( struct Object ),
	NULL,
	NULL,
	NULL,
	NULL
};

void *Object = &_Object;
