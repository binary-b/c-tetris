#include "test.h"

#include <stdio.h>

#include "Class.h"
#include "Object.h"

void run_test ( void ) {
	void *obj = new ( Object );

	printf ( "size of obj = %ld\n", sizeOf (obj) );
}
