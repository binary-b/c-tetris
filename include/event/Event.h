#ifndef _EVENT_H_
#define _EVENT_H_

#include <allegro5/allegro.h>

/*
 * getAlEvent:
 *  - returns ALLEGRO_EVENT or NULL elEvent is not a
 *    clone of event - just pointer to it.
 *    Therefore it should not be altered
 */

extern void *Event;

ALLEGRO_EVENT *event_getAlEvent ( void *self );

#endif
