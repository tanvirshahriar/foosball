/*This file maintains a list of global variables.*/
#ifndef GLOBALS_H
#define GLOBALS_H

#include "objects.h"

#define X_EDGE 320
#define Y_EDGE 240
#define Y_LEN 3
#define X_LEN 0
#define SPEED 1

extern volatile int pixel_buffer_start;
extern int ps2_byte_1, ps2_byte_2, ps2_byte_3;

extern int p1_score, p2_score;
extern int p1_sel, p2_sel;
extern Players GK_BLUE, GK_RED;
extern Players DEF_BLUE[2], DEF_RED[2];
extern Players MID_BLUE[4], MID_RED[4];
extern Players ATK_BLUE[3], ATK_RED[3];
extern Ball BALL;

#endif