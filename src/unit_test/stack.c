#include "test.h"
#include "debug.h"

#include "Class.h"
#include "Stack.h"
#include "Object.h"

void test_stack ( void ) {
	test_print_head ( "Testing Stack class" );

	void *stack;
	void *obj1, *obj2, *obj3;

	stack = new ( Stack );
	obj1 = new ( Object );
	obj2 = new ( Object );
	obj3 = new ( Object );

	test_print_res ( "Putting first element", stack_put (stack, obj1) );
	test_print_res ( "Getting top element", stack_getTop (stack) == obj1 );
	test_print_res ( "Putting second element", stack_put (stack, obj2) );
	stack_rmTop (stack);
	test_print_res ( "Removing top element and checking height", stack_getHeight (stack) == 1 );
	test_print_res ( "Getting top element", stack_getTop (stack) == obj1 );
	test_print_res ( "Putting third element", stack_put (stack, obj3) );
	test_print_res ( "Getting top element", stack_getTop (stack) == obj3 );
	test_print_res ( "Checking height", stack_getHeight (stack) == 2 );

	delete ( stack );
}
