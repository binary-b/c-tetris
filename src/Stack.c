#include "Class.r"
#include "Class.h"
#include "Object.r"
#include "Stack.h"

#include <stdlib.h>

struct StackItem {
	struct StackItem *prev;
	void *obj;
};

struct Stack {
	struct Object _p;
	long height;
	struct StackItem *top;
};

void *_ctor ( void *_self, va_list *app ) {
	struct Stack *self = _self;

	self->height = 0;
	self->top = NULL;

	return self;
}

void _dtor ( void *_self ) {
	struct Stack *self = _self;

	while ( self->height > 0 )
		delete ( stack_pop ( self ) );
}

void *_clone ( void *self ) {
	return self;
}

bool _diff ( void *obj1, void *obj2 ) {
	return false;
}

struct Class _Stack = {
	sizeof ( struct Stack ),
	_ctor,
	_dtor,
	_clone,
	_diff
};

long stack_getHeight ( void *_self ) {
	struct Stack *self = _self;

	return self->height;
}

bool stack_push ( void *_self, void *obj ) {
	struct Stack *self = _self;
	struct StackItem *item;
	
	item = malloc ( sizeof *item );
	if ( !item )
		return false;
	item->obj = obj;
	item->prev = self->top;
	self->top = item;

	self->height++;
	
	return true;
}
void *stack_peek ( void *_self ) {
	struct Stack *self = _self;
	if ( self->height < 1 )
		return NULL;
	else
		return self->top->obj;
}
void *stack_pop ( void *_self ) {
	struct Stack *self = _self;
	struct StackItem *item;
	void *obj;

	if ( self->height < 1 )
		return NULL;
	item = self->top;
	self->top = item->prev;
	obj = item->obj;
	free ( item );

	self->height--;

	return obj;
}

void *Stack = &_Stack;
