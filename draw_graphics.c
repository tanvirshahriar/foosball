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
    // init BALL
    BALL.x = X_EDGE/2 - 1;
    BALL.y = Y_EDGE/2 - 1;
    BALL.velocity_x = (rand() % 2) * pow(-1, rand());
    BALL.velocity_y = (rand() % 2) * pow(-1, rand());

    // init gk
    GK_BLUE.x = 10;
    GK_BLUE.y = Y_EDGE/2 - 1;
    GK_RED.x = X_EDGE - 11;
    GK_RED.y = Y_EDGE/2 - 1;

    // init def
    DEF_BLUE[0].x = 40;
    DEF_BLUE[0].y = (1/3) * Y_EDGE - 1;
    DEF_BLUE[1].x = 40;
    DEF_BLUE[1].y = (2/3) * Y_EDGE - 1;
    DEF_RED[0].x = X_EDGE - 41;
    DEF_RED[0].y = (1/3) * Y_EDGE - 1;
    DEF_RED[1].x = X_EDGE - 41;
    DEF_RED[1].y = (2/3) * Y_EDGE - 1;

    // init mid
    MID_BLUE[0].x = 80;
    MID_BLUE[0].y = (1/5) * Y_EDGE - 1;
    MID_BLUE[1].x = 80;
    MID_BLUE[1].y = (2/5) * Y_EDGE - 1;
    MID_BLUE[2].x = 80;
    MID_BLUE[2].y = (3/5) * Y_EDGE - 1;
    MID_BLUE[3].x = 80;
    MID_BLUE[3].y = (4/5) * Y_EDGE - 1;
    MID_RED[0].x = X_EDGE - 81;
    MID_RED[0].y = (1/5) * Y_EDGE - 1;
    MID_RED[1].x = X_EDGE - 81;
    MID_RED[1].y = (2/5) * Y_EDGE - 1;
    MID_RED[2].x = X_EDGE - 81;
    MID_RED[2].y = (3/5) * Y_EDGE - 1;
    MID_RED[3].x = X_EDGE - 81;
    MID_RED[3].y = (4/5) * Y_EDGE - 1;

    // init atk
    ATK_BLUE[0].x = 120;
    ATK_BLUE[0].y = (1/4) * Y_EDGE - 1;
    ATK_BLUE[1].x = 120;
    ATK_BLUE[1].y = (2/4) * Y_EDGE - 1;
    ATK_BLUE[2].x = 120;
    ATK_BLUE[2].y = (3/4) * Y_EDGE - 1;
    ATK_RED[0].x = X_EDGE - 121;
    ATK_RED[0].y = (1/4) * Y_EDGE - 1;
    ATK_RED[1].x = X_EDGE - 121;
    ATK_RED[1].y = (2/4) * Y_EDGE - 1;
    ATK_RED[2].x = X_EDGE - 121;
    ATK_RED[2].y = (3/4) * Y_EDGE - 1;

    draw_field();
}

void draw_field() {
    int i, j, k;

    // green field
    for(i = 0; i < X_EDGE; i++) 
        for(j = 0; j < Y_EDGE; j++) 
            plot_pixel(i, j, 0xB3F442);

    // BALL
    for(i = BALL.x - 2; i <= BALL.x + 2; i++)
        for(j = BALL.y - 2; j <= BALL.y + 2; j++)
            plot_pixel(i, j, 0x6A668E); // Greyish

    // players
    for(i = GK_BLUE.x - X_LEN; i < GK_BLUE.x + X_LEN; i++)
        for(i = GK_BLUE.y - Y_LEN; j < GK_BLUE.y + Y_LEN; j++)
            plot_pixel(i, j, 0x4268F4); // Blue
    for(i = GK_RED.x - X_LEN; i < GK_RED.x + X_LEN; i++)
        for(i = GK_RED.y - Y_LEN; j < GK_RED.y + Y_LEN; j++)
            plot_pixel(i, j, 0xD62A1D); // Red
    
    for(k = 0; k < 2; k++)
        for(i = DEF_BLUE[k].x - X_LEN; i < DEF_BLUE[k].x + X_LEN; i++)
            for(i = DEF_BLUE[k].y - Y_LEN; j < DEF_BLUE[k].y + Y_LEN; j++)
                plot_pixel(i, j, 0x4268F4); // Blue
    for(k = 0; k < 2; k++)
        for(i = DEF_RED[k].x - X_LEN; i < DEF_RED[k].x + X_LEN; i++)
            for(i = DEF_RED[k].y - Y_LEN; j < DEF_RED[k].y + Y_LEN; j++)
                plot_pixel(i, j, 0xD62A1D); // Red
    
    for(k = 0; k < 4; k++)
        for(i = MID_BLUE[k].x - X_LEN; i < MID_BLUE[k].x + X_LEN; i++)
            for(i = MID_BLUE[k].y - Y_LEN; j < MID_BLUE[k].y + Y_LEN; j++)
                plot_pixel(i, j, 0x4268f4); // Blue
    for(k = 0; k < 4; k++)
        for(i = MID_RED[k].x - X_LEN; i < MID_RED[k].x + X_LEN; i++)
            for(i = MID_RED[k].y - Y_LEN; j < MID_RED[k].y + Y_LEN; j++)
                plot_pixel(i, j, 0xD62A1D); // Red
    
    for(k = 0; k < 3; k++)
        for(i = ATK_BLUE[k].x - X_LEN; i < ATK_BLUE[k].x + X_LEN; i++)
            for(i = ATK_BLUE[k].y - Y_LEN; j < ATK_BLUE[k].y + Y_LEN; j++)
                plot_pixel(i, j, 0x4268f4); // Blue
    for(k = 0; k < 3; k++)
        for(i = ATK_RED[k].x - X_LEN; i < ATK_RED[k].x + X_LEN; i++)
            for(i = ATK_RED[k].y - Y_LEN; j < ATK_RED[k].y + Y_LEN; j++)
                plot_pixel(i, j, 0xD62A1D); // Red
}