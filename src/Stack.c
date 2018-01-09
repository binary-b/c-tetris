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
		stack_rmTop ( self );
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

bool stack_put ( void *_self, void *obj ) {
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
void *stack_getTop ( void *_self ) {
	struct Stack *self = _self;
	return self->top->obj;
}
void stack_rmTop ( void *_self ) {
	struct Stack *self = _self;
	struct StackItem *item;

	item = self->top;
	self->top = item->prev;
	delete ( item->obj );
	free ( item );

	self->height--;
}

void *Stack = &_Stack;
