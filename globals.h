    /*This file maintains a list of global variables.*/
    #ifndef GLOBALS_H
    #define GLOBALS_H

    #include "objects.h"

    #define SPEED 1

    volatile int pixel_buffer_start;

    Players gk_blue, gk_red;
    Players def_blue[2], def_red[2];
    Players mid_blue[4], mid_red[4];
    Players atk_blue[3], atk_red[3];
    Ball telstar;

    #endif