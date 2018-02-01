#include "macros.h"
#include "Window.h"

#include <allegro5/allegro.h>

#include "test.h"

bool game_stop = false;

void game_loop ( void );

int main ( int argc, char **argv ) {
	al_init ();

	unit_test ();

	game_loop ();
	
	return 0;
}

void game_loop ( void ) {
	extern bool game_stop;

	void *window = new ( Window, (Rect) {10, 10, 720, 480} );

	while ( !game_stop ) {
	}
}
