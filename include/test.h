#ifndef _TEST_H_
#define _TEST_H_

#include "macros.h"

void unit_test ( void );

void test_print_head ( char *text );
void test_print_res ( char *text, bool result );

// tests
void test_list ( void );
void test_stack ( void );
void test_window ( void );

#endif
