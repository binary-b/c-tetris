#ifndef _STACK_H_
#define _STACK_H_

/*
 * Stack:
 *  - pretty standard implementation of stack
 *    interface
 *  - if non empty stack will be destroyed it will
 *    be assumed that all its children are objects
 *    (delete ()) will be called)
 *  - pop does NOT call delete ()
 *  - pop/peek return NULL if height == 0
 */

#include "macros.h"

extern void *Stack;

long stack_getHeight ( void *stack );
bool stack_push ( void *stack, void *obj );
void *stack_peek ( void *stack );
void *stack_pop ( void *stack );

#endif
