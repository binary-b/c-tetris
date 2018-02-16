#ifndef _CONTAINER_H_
#define _CONTAINER_H_

/*
 * contains another objects,
 * objects should not touch each others
 */

extern void *Container;

void cont_addView ( void *self, void *view );

#endif
