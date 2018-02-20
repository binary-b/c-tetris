#ifndef _CLASS_H_
#define _CLASS_H_

#include <stdlib.h>
#include "macros.h"

/*
 * Class:
 *   - class descriptor
 *
 * new:
 *   - creates new Object
 *
 * delete:
 *   - when called on NULL does nothing
 *
 * clone:
 *   - when object does not implement clonning itself,
 *     the function clones only automatically allocated
 *     resources (as with new ())
 *
 * differ:
 *   - not used
 *
 * sizeOf:
 *   - size of automatically allocated object
 *
 * typeOf:
 *   - returns pointer to Class descriptor
 */

void *new ( void *class, ... );
void delete ( void *self );
void *clone ( void *self );
bool differ ( void *obj1, void *obj2 );
size_t sizeOf ( void *self );
const void *typeOf ( void *self );

#endif
