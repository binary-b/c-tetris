#ifndef _MACROS_H_
#define _MACROS_H_

#ifndef false
typedef enum {
	false,
	true
} bool;
#endif

typedef struct {
	int x;
	int y;
} Pos;

typedef struct {
	int x, y;
	int w, h;
} Rect;

#endif
