/*This file maintains a list of struct objects used in the code.*/
#ifndef OBJECTS_H
#define OBJECTS_H

// 1 DOF - y axis.
typedef struct {
    int x, y;
} Players;

// 2 DOF - xy axes.
typedef struct {
    int x, y;
    int velocity_x;
    int velocity_y;
} Ball;

#endif