#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "Class.h"
#include "GUIObj.h"
#include "Window.h"
#include "View.h"

#include "macros.h"
#include "test.h"
#include "debug.h"

bool game_stop = false;

void game_loop ( void );

int main ( int argc, char **argv ) {
	al_init ();
	al_init_primitives_addon ();

	unit_test ();
	game_loop ();
	
	return 0;
}

void game_loop ( void ) {
	extern bool game_stop;
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_TIMER *timer;

	timer = al_create_timer ( 1 / (double) 1 );
	queue = al_create_event_queue ();
	al_register_event_source ( queue, al_get_timer_event_source (timer) );

	void *window = new ( Window, (Rect) {0, 0, 720, 480} );
	void *view = new ( View, (Rect) {10, 10, 100, 100} );
	win_addView ( window, view );

	al_start_timer ( timer );
	TRACEF (( "window %p", window ));
	while ( !game_stop ) {
		ALLEGRO_EVENT ev;
		al_wait_for_event ( queue, &ev );

		TRACEF (( "window %p", window ));
		if ( update (window) == WIN_UPDATE_CLOSED )
			break;
		TRACEF (( "window %p", window ));
		draw ( window );
		
		al_flip_display ();
	}

	delete ( window );
}
