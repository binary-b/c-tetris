#ifndef _LABEL_H_
#define _LABEL_H_

extern void *Label;

void label_setText ( void *self, char *text );

void label_setMinWidth ( void *self, int minWidth );
int label_getMinWidth ( void *self, int minWidth );
void label_setPadding ( void *self, int padding );
int label_getPadding ( void *self, int padding );

#endif
