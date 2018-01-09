#include "test.h"

#include "Class.h"
#include "Object.h"
#include "List.h"

#include <stdio.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_BOLD          "\x1b[0;1m"
#define ANSI_RESET         "\x1b[0m"

void unit_test ( void ) {
	/*void *obj = new ( Object );*/

	test_print_head ( "Starting Unit Test" );
	test_print_res ( "some result", true );
	test_print_res ( "some other result", false );

	test_list ();
	/*printf ( "size of obj = %ld\n", sizeOf (obj) );*/

	/*void *list = new ( List );*/

	/*printf ( "length of list = %ld\n", list_getLength (list) );*/
	/*long id = list_addItem ( list, obj );*/
	/*printf ( "id of first item = %ld\n", id );*/
	/*printf ( "length of list = %ld\n", list_getLength (list) );*/
}

void test_print_head ( char *text ) {
	printf ( "\n" ANSI_BOLD "%s\n" ANSI_RESET, text );
}
void test_print_res ( char *text, bool result ) {
	char *color = result ? ANSI_COLOR_GREEN "OK" : ANSI_COLOR_RED "ERROR";
	int length = strlen ( text );

	printf ( "\t%s: ", text );
	while ( length++ < 25 )
		putchar ( ' ' );
	printf ( ANSI_BOLD "%s\n" ANSI_RESET, color );
}
