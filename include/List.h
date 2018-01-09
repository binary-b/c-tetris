#ifndef _LIST_H_
#define _LIST_H_

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
 */

extern void *List;

long list_getLength ( void *List );

long list_addItem ( void *List, void *obj );
void *list_getItem ( void *List, long id );
bool list_rmItem ( void *List, long id );

#endif
