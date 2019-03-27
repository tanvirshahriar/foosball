    /*This file maintains a list of global variables.*/
    #ifndef GLOBALS_H
    #define GLOBALS_H

    #include "objects.h"

    #define X_EDGE 320
    #define Y_EDGE 240
    #define Y_LEN 5
    #define X_LEN 3
    #define SPEED 1

    volatile int pixel_buffer_start;

    Players GK_BLUE, GK_RED;
    Players DEF_BLUE[2], DEF_RED[2];
    Players MID_BLUE[4], MID_RED[4];
    Players ATK_BLUE[3], ATK_RED[3];
    Ball BALL;

    #endif