#include "draw_graphics.h"

void plot_pixel(int x, int y, short int line_color){
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
    return;
}

void clear_screen() {
    int i=0, j=0;
    for(i = 0; i < 320; i++) {
        for(j = 0; j < 240; j++) {
            plot_pixel(i, j, 0x0000);
        }
    }
    return;
}

void draw_line(int x0, int y0, int x1, int y1, short int line_color) {
    bool is_steep = abs(y1 - y0) > abs (x1 - x0);
    if(is_steep) {
        swap(&x0, &y0);
        swap(&x1, &y1);
    }
    if(x0 > x1) {
        swap(&x0, &x1);
        swap(&y0, &y1);
    }

    int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
    int error = -(deltax / 2);
    int y = y0;
    int y_step;

    if(y0 < y1) {
        y_step = 1;
    }
    else {
        y_step = -1;
    }

    int x;
    for(x = x0; x <= x1; x++) {
        if(is_steep)
            plot_pixel(y, x, line_color);
        else
            plot_pixel(x, y, line_color);
        error += deltay;
        if(error >= 0) {
            y += y_step;
            error -= deltax;
        }
    }
    return;
}
