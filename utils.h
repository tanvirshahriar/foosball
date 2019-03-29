#ifndef UTILS_H
#define UTILS_H

#include "globals.h"
#include <stdbool.h>

// Forward declarations.
int p1_score, p2_score;
Players GK_BLUE, GK_RED;
Players DEF_BLUE[2], DEF_RED[2];
Players MID_BLUE[4], MID_RED[4];
Players ATK_BLUE[3], ATK_RED[3];
Ball BALL;

void swap(int *x, int *y);
void ball_mechanics(bool goal);

#endif