#ifndef _LIST_H_
#define _LIST_H_

#include <stdarg.h>

#include "macros.h"

/*
 * List:
 *  - the order of items can change
 *
 * addItem:
 * 	- returns id of new item
 *
 * getItem:
 *  - returns item of given id
 *  - if item don't exists NULL will be returned
 *
 * rmItem:
 * 	- calls delete() on item of given id
 * 	- if item didn't exist false will be returned,
 * 	  otherwise true
 *
 * apply:
 *  - calls function f on every object in list
 *  - designed to call an intermediate function
 */

extern void *List;

long list_getLength ( void *List );

long list_addItem ( void *self, void *obj );
void *list_getItem ( void *self, long id );
bool list_rmItem ( void *self, long id );

void list_apply ( void *self, void (*f) (int id, void *obj) );

#endif
