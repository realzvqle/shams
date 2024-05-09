#ifndef DRAWSNAKE_H_INCLUDED
#define DRAWSNAKE_H_INCLUDED

#include "start.h"


typedef enum _snakeState{
    UP,
    DOWN,
    LEFT,
    RIGHT
} snakeState;

typedef struct _snake{
    RECT rect;
    RECT prevRect;
    HBRUSH brush;
    snakeState state;
    int amountOfTail;
} snake;


snake* setup_snake(data* data);
void draw_snake(data* data, snake* snake);
BOOL end_snake(snake* snake);



#endif