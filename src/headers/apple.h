#ifndef APPLE_H_INCLUDED
#define APPLE_H_INCLUDED



#include "start.h"

typedef struct _apple{
    RECT rect;
    HBRUSH brush;
} apple;



apple* setup_apple();
void draw_apple(data* data, apple* apple);
BOOL end_apple(apple* apple);

#endif