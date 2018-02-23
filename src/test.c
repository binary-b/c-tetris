#include "test.h"

#include "IClass.h"
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
	test_list ();
	test_stack ();
	test_window ();
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
