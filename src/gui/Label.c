#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "gui/View.r"
#include "gui/GUIObj.r"
#include "gui/Label.h"

#include "gui/View.h"

#include "macros.h"
#include "debug.h"

struct Label {
	struct View _p;
	char *text;
	int size;			// the height of the font
	ALLEGRO_FONT *font;
};

static void * _ctor ( void *_self, va_list *app ) {
	p_ctor ( _self, app );

	struct Label *self = _self;
	char *text;
	int size;
	Rect r;

	ALLEGRO_PATH *path;
	ALLEGRO_FONT *font;

	// copy text
	text = strdup ( va_arg (*app, char *) );
	size = va_arg ( *app, int );

	// load font
	path = al_get_standard_path ( ALLEGRO_RESOURCES_PATH );
	al_set_path_filename ( path, "fonts/Overlock/Overlock-Black.ttf" );
	font = al_load_ttf_font ( al_path_cstr (path, ALLEGRO_NATIVE_PATH_SEP), size, 0 );
	self->font = font;
	self->text = text;

	// set rectangle width and height
	r = view_getRect ( self );
	r.w = al_get_text_width ( font, text );
	r.h = al_get_font_line_height ( font );
	view_setRect ( self, r );

	al_destroy_path ( path );
	
	return _self;
}
static void _dtor ( void *_self ) {
	struct Label *self = _self;

	free ( self->text );

	al_destroy_font ( self->font );
}

static int _update ( void *obj ) {
	TRACEF (( "Label.update ()" ));
	return 0;
}
static void _draw ( void *_self ) {
	TRACEF (( "Label.draw ()" ));
	struct Label *self = _self;
	al_draw_text ( self->font, al_map_rgb (255, 255, 0), 0.0, 0.0, 0, self->text );
}

struct GUIObj _Label = {
	sizeof ( struct Label ),
	_ctor,
	_dtor,
	NULL,
	NULL,
	_update,
	_draw
};

void *Label = &_Label;
