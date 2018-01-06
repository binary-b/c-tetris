#include "Class.r"
#include "Object.h"

struct Object {
	void *class;
};

struct Class _Object = {
	sizeof ( struct Object ),
	NULL,
	NULL,
	NULL
};

void *Object = &_Object;
