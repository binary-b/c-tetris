#ifndef _STACK_H_
#define _STACK_H_

#include "macros.h"

extern void *Stack;

long stack_getHeight ( void *stack );
bool stack_put ( void *stack, void *obj );
void *stack_getTop ( void *stack );
void stack_rmTop ( void *stack );

#endif
