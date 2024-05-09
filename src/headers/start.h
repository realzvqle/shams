#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


#include <windows.h>


typedef struct _data{
    int sWidth;
    int sHeight;
    HDC dc;
    HBRUSH background;
} data;


int start_snake_game();

#endif