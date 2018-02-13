#include <allegro5/allegro.h>
#include <assert.h>

#include "gui/GUIObj.r"
#include "gui/View.r"

#include "gui/View.h"

#include "debug.h"

struct Image {
	struct View _p;
	ALLEGRO_BITMAP *image;
};

static void *_ctor ( void *_self, va_list *app ) {
	p_ctor ( _self, app );

	struct Image *self = _self;
	char *name;
	Rect r;

	ALLEGRO_PATH *path;
	ALLEGRO_BITMAP *image;

	TRACE;
	// load image
	name = va_arg ( *app, char * );
	path = al_get_standard_path ( ALLEGRO_RESOURCES_PATH );
	al_append_path_component ( path, "img" );
	al_set_path_filename ( path, name );
	image = al_load_bitmap ( al_path_cstr (path, ALLEGRO_NATIVE_PATH_SEP) );
	TRACEF (( "%s", al_path_cstr (path, ALLEGRO_NATIVE_PATH_SEP) ));
	assert ( image );
	TRACE;

	// set rectangle width and height
	r = view_getRect ( self );
	r.w = al_get_bitmap_width ( image );
	r.h = al_get_bitmap_height ( image );
	view_setRect ( self, r );
	TRACE;

	self->image = image;

	return _self;
}
static void _dtor ( void *_self ) {
	struct Image *self = _self;

	al_destroy_bitmap ( self->image );
}

static int _update ( void *_self ) {
	return 0;
}
static void _draw ( void *_self ) {
	struct Image *self = _self;
	al_draw_bitmap ( self->image, 0, 0, 0 );
}

struct GUIObj _Image = {
	sizeof ( struct Image ),
	_ctor,
	_dtor,
	NULL,
	NULL,
	_update,
	_draw
};

void *Image = &_Image;
