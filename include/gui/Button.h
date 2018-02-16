#ifndef _BUTTON_H_
#define _BUTTON_H_

extern void *Button;

void btn_setLabel ( void *self, void *label );
void *btn_getLabel ( void *self );

void btn_call ( void *self );

#endif
