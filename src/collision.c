#include "headers/collision.h"
#include "headers/tools.h"


static inline double distance(int x1, int y1, int x2, int y2) {
    return ssqrt(ppow(x2 - x1, 2) + ppow(y2 - y1, 2));
}

static double distance_between_rects(RECT rect1, RECT rect2) {
    int center_x1 = (rect1.left + rect1.right) / 2;
    int center_y1 = (rect1.top + rect1.bottom) / 2;
    int center_x2 = (rect2.left + rect2.right) / 2;
    int center_y2 = (rect2.top + rect2.bottom) / 2;

    return distance(center_x1, center_y1, center_x2, center_y2);
}


int check_collision(data* data, apple* apple, snake* snake){
    FillRect(data->dc, &apple->rect, data->background);

    if(distance_between_rects(apple->rect, snake->rect) <= 100){
    snake->amountOfTail++;
    apple->rect.right = getRandomNumber(200, data->sWidth - 100);
    apple->rect.bottom = getRandomNumber(200, data->sHeight - 100);
    apple->rect.left = apple->rect.right - 100;
    apple->rect.top = apple->rect.bottom - 100;
    FillRect(data->dc, &apple->rect, apple->brush);
}

    DrawTextA(data->dc, i_to_a(apple->rect.bottom, 30), 6, &(RECT){100, 100, 200, 200}, 0);
    if (snake->rect.bottom > data->sHeight + 440 || snake->rect.left < 0 || snake->rect.right > data->sWidth + 576 || snake->rect.top < 0) {
        return 1;
    }


    return 0;
}