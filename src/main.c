#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "Class.h"
#include "GUIObj.h"
#include "Window.h"
#include "View.h"
#include "Container.h"
#include "Label.h"
#include "Image.h"

#include "macros.h"
#include "test.h"
#include "debug.h"

bool game_stop = false;

void game_loop ( void );

int main ( int argc, char **argv ) {
	al_init ();
	al_init_primitives_addon ();
	al_init_font_addon ();
	al_init_ttf_addon ();
	al_init_image_addon ();

	al_install_mouse ();
	al_install_keyboard ();

	unit_test ();
	game_loop ();
	
	return 0;
}

void game_loop ( void ) {
	extern bool game_stop;
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_TIMER *timer;

	void *view, *container;

	timer = al_create_timer ( 1 / (double) 1 );
	queue = al_create_event_queue ();
	al_register_event_source ( queue, al_get_timer_event_source (timer) );

	container = new ( Container );
	void *window = new ( Window, (Rect) {0, 0, 720, 480} );
	view = new ( View, (Rect) {10, 10, 100, 100} );
	cont_addView ( container, view );
	view = new ( Image, (Rect) {400, 400, 100, 100}, "test_image.png" );
	cont_addView ( container, view );
	view = new ( Label, (Rect) {200, 0, 100, 100}, "some example text", 20 );
	cont_addView ( container, view );
	win_addView ( window, container );

	al_start_timer ( timer );
	while ( !game_stop ) {
		ALLEGRO_EVENT ev;
		al_wait_for_event ( queue, &ev );

		if ( update (window) == WIN_UPDATE_CLOSED )
			break;
		draw ( window );
		
		al_flip_display ();
	}

	delete ( window );
}
