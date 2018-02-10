#include "Class.r"
#include "Class.h"
#include "Object.r"
#include "List.h"

#include "macros.h"
#include "debug.h"

struct ListItem {
	long id;
	void *cont;
	struct ListItem *next;
};

struct List {
	struct Object _p;
	long length;
	long counter;
	struct ListItem *first;
};

static void *_findItem ( struct List *self, long id, struct ListItem **prev ) {
	struct ListItem *item, *_prev;

	if ( !prev ) {
		prev = &_prev;
	}

	*prev = NULL; // change to NULL!
	item = self->first;
	while ( item != NULL && item->id != id ) {
		*prev = item;
		item = item->next;
	}

	return item;
}

static void *_ctor ( void *_self, va_list *app ) {
	struct List *self = _self;

	self->length = 0;
	self->counter = 0;
	self->first = NULL;

	return _self;
}

static void _dtor ( void *_self ) {
	struct List *self = _self;
	while ( self->first ) {
		list_rmItem ( _self, self->first->id );
	}
}

static void *_clone ( void *_self ) {
	return _self;
}

static bool _diff ( void *_1, void *_2 ) {
	return true;
}

long list_getLength ( void *_self ) {
	struct List *self = _self;
	return self->length;
}

long list_addItem ( void *_self, void *obj ) {
	struct List *self = _self;
	struct ListItem *item;

	item = malloc ( sizeof *item );
	if ( !item ) {
		return false;
	}
	item->id = self->counter++;
	item->cont = obj;
	item->next = self->first;

	self->first = item;
	self->length++;

	return item->id;
}
void *list_getItem ( void *_self, long id ) {
	struct List *self = _self;
	struct ListItem *item;

	item = _findItem (self, id, NULL);

	return item ? item->cont : NULL;
}
bool list_rmItem ( void *_self, long id ) {
	struct List *self = _self;
	struct ListItem *item, *prev;

	item = _findItem ( self, id, &prev );

	if ( prev ) {
		prev->next = item->next;
	} else if ( item ) {
		self->first = item->next;
	}
	if ( item ) {
		delete ( item->cont );
		free ( item );
		self->length--;

		return true;
	} else
		return false;
}

void list_apply ( void *_self, void (*f) (int id, void *obj) ) {
	struct List *self = _self;
	struct ListItem *curr = self->first;

	while ( curr != NULL ) {
		f ( curr->id, curr->cont );

		curr = curr->next;
	}
}

struct Class _List = {
	sizeof ( struct List ),
	_ctor,
	_dtor,
	_clone,
	_diff
};

void *List = &_List;
