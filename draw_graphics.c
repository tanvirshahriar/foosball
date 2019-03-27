#include "draw_graphics.h"

void plot_pixel(int x, int y, short int line_color){
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
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

void clear_screen() {
    int i=0, j=0;
    for(i = 0; i < 320; i++) {
        for(j = 0; j < 240; j++) {
            plot_pixel(i, j, 0x0000);
        }
    }
    return;
}

void initialize_field() {
    // init ball
    telstar.x = X_EDGE/2 - 1;
    telstar.y = Y_EDGE/2 - 1;
    telstar.velocity_x = (rand() % 2) * pow(-1, rand());
    telstar.velocity_y = rand() % 2 * pow(-1, rand());

    // init gk
    gk_blue.x = 10;
    gk_blue.y = Y_EDGE/2 - 1;
    gk_red.x = X_EDGE - 11;
    gk_red.y = Y_EDGE/2 - 1;

    // init def
    def_blue[0].x = 40;
    def_blue[0].y = (1/3) * Y_EDGE - 1;
    def_blue[1].x = 40;
    def_blue[1].y = (2/3) * Y_EDGE - 1;
    def_red[0].x = X_EDGE - 41;
    def_red[0].y = (1/3) * Y_EDGE - 1;
    def_red[1].x = X_EDGE - 41;
    def_red[1].y = (2/3) * Y_EDGE - 1;

    // init mid
    mid_blue[0].x = 80;
    mid_blue[0].y = (1/5) * Y_EDGE - 1;
    mid_blue[1].x = 80;
    mid_blue[1].y = (2/5) * Y_EDGE - 1;
    mid_blue[2].x = 80;
    mid_blue[2].y = (3/5) * Y_EDGE - 1;
    mid_blue[3].x = 80;
    mid_blue[3].y = (4/5) * Y_EDGE - 1;
    mid_red[0].x = X_EDGE - 81;
    mid_red[0].y = (1/5) * Y_EDGE - 1;
    mid_red[1].x = X_EDGE - 81;
    mid_red[1].y = (2/5) * Y_EDGE - 1;
    mid_red[2].x = X_EDGE - 81;
    mid_red[2].y = (3/5) * Y_EDGE - 1;
    mid_red[3].x = X_EDGE - 81;
    mid_red[3].y = (4/5) * Y_EDGE - 1;

    // init atk
    atk_blue[0].x = 120;
    atk_blue[0].y = (1/4) * Y_EDGE - 1;
    atk_blue[1].x = 120;
    atk_blue[1].y = (2/4) * Y_EDGE - 1;
    atk_blue[2].x = 120;
    atk_blue[2].y = (3/4) * Y_EDGE - 1;
    atk_red[0].x = X_EDGE - 121;
    atk_red[0].y = (1/4) * Y_EDGE - 1;
    atk_red[1].x = X_EDGE - 121;
    atk_red[1].y = (2/4) * Y_EDGE - 1;
    atk_red[2].x = X_EDGE - 121;
    atk_red[2].y = (3/4) * Y_EDGE - 1;

    draw_field();
}

void draw_field() {
    int i, j;

    // green field
    for(i = 0; i < X_EDGE; i++) 
        for(j = 0; j < Y_EDGE; j++) 
            plot_pixel(i, j, 0xB3F442);

    // ball
    for(i = telstar.x - 2; i <= telstar.x + 2; i++)
        for(j = telstar.y - 2; j <= telstar.y + 2; j++)
            plot_pixel(i, j, 0x6A668E);
}