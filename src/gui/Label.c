#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "gui/View.r"
#include "gui/GUIHandler.r"
#include "gui/Label.h"

#include "gui/View.h"

#include "macros.h"
#include "debug.h"

struct Label {
	struct View _p;
	char *text;
	int size;			// the height of the font
	ALLEGRO_FONT *font;
	int minWidth;
	int padding;
};

static void _compSize ( void *_self ) {
	struct Label *self = _self;
	Rect r;

	/*TRACEF (( "padding=%d, minWidth=%d", self->padding, self->minWidth ));*/
	// set rectangle width and height
	r = view_getRect ( self );
	r.w = al_get_text_width ( self->font, self->text ) + 2 *self->padding;
	r.w = r.w < self->minWidth ? self->minWidth : r.w;
	r.h = al_get_font_line_height ( self->font ) + 2 * self->padding;
	view_setRect ( self, r );
}

static void * _ctor ( void *_self, va_list *app ) {
	View_ctor ( _self, app );

	struct Label *self = _self;
	char *text;
	int size;

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

	self->minWidth = 0;
	self->padding = 10;

	_compSize ( self );

	al_destroy_path ( path );
	
	return _self;
}
static void _dtor ( void *_self ) {
	struct Label *self = _self;

	free ( self->text );

	al_destroy_font ( self->font );
}

static int _update ( void *_self ) {
	/*TRACEF (( "Label.update ()" ));*/
	return 0;
}
static void _draw ( void *_self ) {
	/*TRACEF (( "Label.draw ()" ));*/
	struct Label *self = _self;
	al_draw_text ( self->font, al_map_rgb (255, 255, 0), self->padding, self->padding, 0, self->text );
}

void label_setText ( void *_self, char *text ) {
	struct Label *self = _self;

	free ( self->text );
	self->text = strdup ( text );
	_compSize ( self );
}

void label_setMinWidth ( void *_self, int minWidth ) {
	struct Label *self = _self;
	self->minWidth = minWidth;
	_compSize ( self );
}
int label_getMinWidth ( void *_self, int minWidth ) {
	struct Label *self = _self;
	return self->minWidth;
}
void label_setPadding ( void *_self, int padding ) {
	struct Label *self = _self;
	self->padding = padding;
	_compSize ( self );
}
int label_getPadding ( void *_self, int padding ) {
	struct Label *self = _self;
	return self->padding;
}

struct GUIHandler _Label = {
	sizeof ( struct Label ),
	_ctor,
	_dtor,
	NULL,
	NULL,
	_update,
	_draw,
	NULL
};

void *Label = &_Label;
