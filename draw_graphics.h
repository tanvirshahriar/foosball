/* Maintains graphics functions. */
#ifndef DRAW_GRAPHICS_H
#define DRAW_GRAPHICS_H

#include "globals.h"
#include "utils.h"
#include <stdbool.h>
#include <math.h>

// Forward declarations.
extern volatile int pixel_buffer_start;
extern Players GK_BLUE, GK_RED;
extern Players DEF_BLUE[2], DEF_RED[2];
extern Players MID_BLUE[4], MID_RED[4];
extern Players ATK_BLUE[3], ATK_RED[3];
extern Ball BALL;

// Graphics functions.
void plot_pixel(int x, int y, short int line_color);
void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void clear_screen();
void initialize_field();
void draw_field();

#endif