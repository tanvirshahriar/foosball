#include "utils.h"

// Swap.
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    return;
}

// Calculates ball position for every game iteration.
void ball_mechanics(bool goal) {
    // Hits a goal post.
    if(((BALL.x-2) < 5) && ((BALL.y+2) > (Y_EDGE/2)-10) && ((BALL.y-2) < (Y_EDGE/2)+10)) {
        p1_score++;
        goal = true;
    }
    else if(((BALL.x+2) > (X_EDGE-5)) && ((BALL.y+2) > (Y_EDGE/2)-10) && ((BALL.y-2) < (Y_EDGE/2)+10)) {
        p2_score++;
        goal = true;
    }
    if(!goal) {
        // Hits a player.
        if((((BALL.x+2) == (GK_BLUE.x-X_LEN)) || ((BALL.x-2) == (GK_BLUE.x+X_LEN))) && (BALL.y == GK_BLUE.y))
            BALL.velocity_x *= -1;
        else if((((BALL.x+2) == (GK_BLUE.x-X_LEN)) || ((BALL.x-2) == (GK_BLUE.x+X_LEN))) && ((BALL.y >= GK_BLUE.y-Y_LEN) && (BALL.y <= GK_BLUE.y+Y_LEN))) {
            BALL.velocity_x *= -1;     
            BALL.velocity_y *= -1;       
        }
        else if((((BALL.x+2) == (GK_RED.x-X_LEN)) || ((BALL.x-2) == (GK_RED.x+X_LEN))) && (BALL.y == GK_RED.y))
            BALL.velocity_x *= -1;
        else if((((BALL.x+2) == (GK_RED.x-X_LEN)) || ((BALL.x-2) == (GK_RED.x+X_LEN))) && ((BALL.y >= GK_RED.y-Y_LEN) && (BALL.y <= GK_RED.y+Y_LEN))) {
            BALL.velocity_x *= -1;     
            BALL.velocity_y *= -1;       
        }        
        // Hits a boundary.
        if(((BALL.x-2) == 0) || ((BALL.x+2) == X_EDGE))
            BALL.velocity_x *= -1;
        if(((BALL.y-2) == 0) || ((BALL.y+2) == Y_EDGE))
            BALL.velocity_y *= -1;        
        // Free to move.
        BALL.x += BALL.velocity_x;
        BALL.y += BALL.velocity_y;
    }
}