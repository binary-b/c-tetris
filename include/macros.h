#ifndef _MACROS_H_
#define _MACROS_H_

typedef enum {
	false,
	true
} bool;

typedef enum {
	DIR_UP,
	DIR_DOWN,
	DIR_RIGHT,
	DIR_LETF,
	DIR_CLOCKWISE,
	DIR_COUNTER_CLOCKWISE
} direction;

typedef enum {
	EV_ONCLICK
} events;

typedef struct {
	int x;
	int y;
} Pos;

typedef struct {
	events type;
	Pos mouse_pos;
} Event;

typedef struct {
	int x, y;
	int w, h;
} Rect;

#endif
