#include "headers/apple.h"
#include "headers/tools.h"




apple* setup_apple(){
    apple* aple = alloc_mem(sizeof(apple));
    aple->rect = (RECT){300, 300, 400, 400};
    aple->brush = CreateSolidBrush(RGB(255, 0, 0));
    return aple;
}

void draw_apple(data* data, apple* apple){
    FillRect(data->dc, &apple->rect, apple->brush);
}



BOOL end_apple(apple* apple){
    DeleteObject(apple->brush);
    return free_mem(apple);
}