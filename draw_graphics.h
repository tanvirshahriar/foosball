/* Maintains graphics functions. */
#ifndef DRAW_GRAPHICS_H
#define DRAW_GRAPHICS_H

#include "globals.h"
#include "helpers.h"
#include <stdbool.h>

void plot_pixel(int x, int y, short int line_color);
void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void clear_screen();
void initialize_field();
void draw_field();

#endif