#ifndef _MACROS_H_
#define _MACROS_H_

typedef enum {
	false,
	true
} bool;

typedef enum {
	UP,
	DOWN,
	RIGHT,
	LETF,
	CLOCKWISE,
	COUNTER_CLOCKWISE
} direction;

typedef enum {
	EV_ONCLICK
} events;

typedef struct {
	int x;
	int y;
} Pos;

typedef struct {
	int width;
	int height;
} Dim;

typedef struct {
	events type;
	Pos mouse_pos;
} Event;

#endif
