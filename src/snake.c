#include "headers/snake.h"
#include "headers/tools.h"






snake* setup_snake(data* data){
    snake* snke = alloc_mem(sizeof(snake));
    if(snke == NULL){
        return NULL;
    }
    snke->rect = (RECT){100, 100, 200, 200};
    snke->brush = CreateSolidBrush(RGB(0, 255, 0));
    snke->state = RIGHT;
    snke->amountOfTail = 1;
    return snke;
}



static void controls(snake* snake, data* data){
    if(GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44)){
        snake->state = RIGHT;
    }
    if(GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(0x41)){
        snake->state = LEFT;
    }
    if(GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(0x53)){
        snake->state = DOWN;
    }
    if(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(0x57)){
        snake->state = UP;
    }
}


void draw_snake(data* data, snake* snake){
    FillRect(data->dc, &snake->rect, data->background);
    for (int i = 0; i < snake->amountOfTail; i++) {
        if(snake->state == LEFT || snake->state == RIGHT){
            FillRect(data->dc, &(RECT){snake->rect.left - (i + 1) * 10, snake->rect.top, 
                                    snake->rect.right - (i + 1) * 10, snake->rect.bottom}, data->background);
        }
        else{
            FillRect(data->dc, &(RECT){snake->rect.left, snake->rect.top  - (i + 1) * 10, 
                                    snake->rect.right, snake->rect.bottom - (i + 1) * 10}, data->background);
        }
    }

    controls(snake, data);
    int speed = 102;
    if(snake->state == RIGHT){
        snake->rect.right+=speed;
        snake->rect.left+=speed;
    }
    if(snake->state == LEFT){
        snake->rect.right-=speed;
        snake->rect.left-=speed;
    }
    if(snake->state == UP){
        snake->rect.top-=speed;
        snake->rect.bottom-=speed;
    }
     if(snake->state == DOWN){
        snake->rect.top+=speed;
        snake->rect.bottom+=speed;
    }

  FillRect(data->dc, &snake->rect, snake->brush);

    // Draw snake tail
    
    for (int i = 0; i < snake->amountOfTail; i++) {
        if(snake->state == LEFT || snake->state == RIGHT){
            FillRect(data->dc, &(RECT){snake->rect.left - (i + 1) * 10, snake->rect.top, 
                                    snake->rect.right - (i + 1) * 10, snake->rect.bottom}, snake->brush);
        }
        else{
            FillRect(data->dc, &(RECT){snake->rect.left, snake->rect.top  - (i + 1) * 10, 
                                    snake->rect.right, snake->rect.bottom - (i + 1) * 10}, snake->brush);
        }
    }
    DrawTextA(data->dc, i_to_a(snake->amountOfTail, 6), 6, &snake->rect, 0);
    

}

BOOL end_snake(snake* snake){
    DeleteObject(snake->brush);
    return free_mem(snake);
}