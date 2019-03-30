#ifndef UTILS_H
#define UTILS_H

#include "globals.h"
#include <stdbool.h>

// Forward declarations.
extern int p1_score, p2_score;
extern Players GK_BLUE, GK_RED;
extern Players DEF_BLUE[2], DEF_RED[2];
extern Players MID_BLUE[4], MID_RED[4];
extern Players ATK_BLUE[3], ATK_RED[3];
extern Ball BALL;

void swap(int *x, int *y);
void ball_mechanics(bool goal);

#endif