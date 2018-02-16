#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <stdio.h>

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

static void *_label;
static int _back_reg;
static int _curr_reg;
static char _operator;
static void _button_call ( void *button ) {
	char textBuf [50];
	char *text = textBuf;
	int val = btn_getValue ( button );

	if ( val >= '0' && val <= '9' ) {
		if ( _operator == '=' )
			_operator = '\0', _curr_reg = 0;
		_curr_reg *= 10, _curr_reg += val - '0';
	} else if ( val != '=' ) {
		_operator = val;
		_back_reg = _curr_reg;
		_curr_reg = 0;
	} else if ( val == '=' ) {
		if ( _operator == '+' )
			_curr_reg += _back_reg;
		else if ( _operator == '-' )
			_curr_reg = _back_reg - _curr_reg;
		else if ( _operator == '*' )
			_curr_reg *= _back_reg;
		else if ( _operator == '/' ) {
			if ( _curr_reg != 0 )
				_curr_reg = _back_reg / _curr_reg;
		}

		_operator = '=';
		_back_reg = 0;
	}

	sprintf ( textBuf, "%d", _curr_reg );
	label_setText ( _label, text );
}
void game_loop ( void ) {
	extern bool game_stop;
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_TIMER *timer;

	_curr_reg = 0;
	_back_reg = 0;
	_operator = '\0';

	int h = 50;

	void *button, *label, *container;
	void *window;

	timer = al_create_timer ( 1 / (double) 60 );
	queue = al_create_event_queue ();
	al_register_event_source ( queue, al_get_timer_event_source (timer) );

	container = new ( Container );

	_label = new ( Label, (Rect) {h, h, 11*h, 2*h}, "Some text", h ); 
	cont_addView ( container, _label );
	{	// adding buttons
		{ // 7
			button = new ( Button, (Rect) {h, 4*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '7' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
		{ // 8
			button = new ( Button, (Rect) {3*h, 4*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '8' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
		{ // 9
			button = new ( Button, (Rect) {5*h, 4*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '9' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
		{ // '/' - divide
			button = new ( Button, (Rect) {7*h, 4*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '/' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
		{ // 4
			button = new ( Button, (Rect) {h, 6*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '4' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
		{ // 5
			button = new ( Button, (Rect) {3*h, 6*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '5' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
		{ // 6
			button = new ( Button, (Rect) {5*h, 6*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '6' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
		{ // '*' - multiply
			button = new ( Button, (Rect) {7*h, 6*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '*' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
		{ // 1
			button = new ( Button, (Rect) {h, 8*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '1' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
		{ // 2
			button = new ( Button, (Rect) {3*h, 8*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '2' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
		{ // 3
			button = new ( Button, (Rect) {5*h, 8*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '3' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
		{ // '-' - substract
			button = new ( Button, (Rect) {7*h, 8*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '-' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
		{ // 0
			button = new ( Button, (Rect) {h, 10*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '0' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
		{ // '.' - dot (comma numbers)
			button = new ( Button, (Rect) {3*h, 10*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '.' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
		{ // '=' - is equal
			button = new ( Button, (Rect) {5*h, 10*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '=' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
		{ // '+' - multiply
			button = new ( Button, (Rect) {7*h, 10*h, 2*h, 2*h}, _button_call );
			btn_setValue ( button, '+' );
			char text [2];
			text [0] = btn_getValue (button);
			text [1] = '\0';
			label = new (Label, (Rect) {0, 0, 0, 0}, text, h);
			label_setMinWidth ( label, 2*h - 2 * 10 );
			label_setPadding ( label, 10 );
			btn_setLabel ( button, label );
			cont_addView ( container, button );
		}
	}

	window = new ( Window, (Rect) {0, 0, 13*h, 16*h} );
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
