#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>

#define TRACE ( printf ( __FILE__ ":%d\n", __LINE__ ) );
#define TRACEF(A) { \
	printf ( __FILE__ ":%d:", __LINE__ ); \
	printf A; \
	putchar ( '\n' ); \
}

#endif
