#include <string.h>
#include <stdarg.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <View.r>
#include <GUIObj.r>
#include <Label.h>

#include <View.h>

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
	ALLEGRO_PATH *path;
	ALLEGRO_FONT *font;
	int size;
	Rect r;

	text = strdup ( va_arg (*app, char *) );
	size = va_arg ( *app, int );

	path = al_get_standard_path ( ALLEGRO_RESOURCES_PATH );
	al_append_path_component ( path, "fonts/Overlock/" );
	al_set_path_filename ( path, "Overlock-Black.ttf" );
	TRACEF (( "%s", al_path_cstr (path, ALLEGRO_NATIVE_PATH_SEP) ));
	font = al_load_ttf_font ( al_path_cstr (path, ALLEGRO_NATIVE_PATH_SEP), size, 0 );
	self->font = font;
	self->text = text;

	r = view_getRect ( self );
	r.w = al_get_text_width ( font, text );
	r.h = al_get_font_line_height ( font );
	view_setRect ( self, r );
	TRACEF (( "x=%d, y=%d, w=%d, h=%d", r.x, r.y, r.w, r.h ));
	r = view_getRect ( self );
	TRACEF (( "x=%d, y=%d, w=%d, h=%d", r.x, r.y, r.w, r.h ));
	
	return _self;
}
static void _dtor ( void *_self ) {
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
