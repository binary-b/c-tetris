#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "Class.h"
#include "gui/GUIObj.h"
#include "gui/Window.h"
#include "gui/View.h"
#include "gui/Container.h"
#include "gui/Label.h"
#include "gui/Image.h"
#include "gui/Button.h"

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

static void _button_call ( void *button ) {
	TRACEF (( "Button have been clicked" ));
}
void game_loop ( void ) {
	extern bool game_stop;
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_TIMER *timer;

	void *view, *container;
	void *label;

	timer = al_create_timer ( 1 / (double) 60 );
	queue = al_create_event_queue ();
	al_register_event_source ( queue, al_get_timer_event_source (timer) );

	container = new ( Container );
	void *window = new ( Window, (Rect) {0, 0, 720, 480} );
	view = new ( View, (Rect) {10, 10, 100, 100} );
	cont_addView ( container, view );
	view = new ( Image, (Rect) {400, 400, 100, 100}, "test_image.png" );
	cont_addView ( container, view );

	label = new ( Label, (Rect) {200, 0, 100, 100}, "some example text", 20 );
	view = new ( Button, (Rect) {200, 10, 0, 0}, _button_call );
	btn_setLabel ( view, label );
	cont_addView ( container, view );
	win_addView ( window, container );

	al_start_timer ( timer );
	while ( !game_stop ) {
		ALLEGRO_EVENT ev;
		al_wait_for_event ( queue, &ev );

		if ( update (window) == WIN_UPDATE_CLOSED )
			break;
		al_clear_to_color ( al_map_rgb (0, 0, 0) );
		draw ( window );
		
		al_flip_display ();
	}

	delete ( window );
}
