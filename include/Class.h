#ifndef _CLASS_H_
#define _CLASS_H_

#include <stdlib.h>
#include "macros.h"

void *new ( void *class, ... );
void delete ( void *self );
void *clone ( void *self );
bool differ ( void *obj1, void *obj2 );
size_t sizeOf ( void *self );
const void *typeOf ( void *self );

#endif
