#include "test.h"
#include "debug.h"

#include "Class.h"
#include "List.h"
#include "Object.h"

#include <stdio.h>

void test_list ( void ) {
	test_print_head ( "Testing List class" );

	void *obj;
	long id, id1, id2;
	void *list;

	bool res;

	list = new ( List );

	obj = new ( Object );
	id1 = list_addItem ( list, new (Object) );
	id = list_addItem ( list, obj );
	id2 = list_addItem ( list, new (Object) );

	test_print_res ( "adding 3 items", list_getLength (list) == 3 );

	test_print_res ( "getting last item", list_getItem (list, id2) != NULL );
	test_print_res ( "getting middle item", list_getItem (list, id) == obj );
	test_print_res ( "getting first item", list_getItem (list, id1) != NULL );

	res = list_rmItem ( list, id );

	test_print_res ( "removing middle item", res );
	test_print_res ( "asking for length", list_getLength (list) == 2 );
	test_print_res ( "getting first item", list_getItem (list, id1) != NULL );
	test_print_res ( "getting removed item", list_getItem (list, id) == NULL );
	test_print_res ( "getting last item", list_getItem (list, id2) != NULL );

	delete ( list );
}
