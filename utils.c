#include "utils.h"

// Swap.
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    return;
}

// Calculates ball position for every game iteration.
void ball_mechanics() {
    // Hits a goal post.
    if(((BALL.x-2) < 5) && ((BALL.y+2) > (Y_EDGE/2)-10) && ((BALL.y-2) < (Y_EDGE/2)+10)) {
        p1_score++;
        //goal = true;
        goal = 1;
        return;
    }
    else if(((BALL.x+2) > (X_EDGE-5)) && ((BALL.y+2) > (Y_EDGE/2)-10) && ((BALL.y-2) < (Y_EDGE/2)+10)) {
        p2_score++;
        //goal = true;
        goal = 1;
        return;
    }
    if(!goal) {
        // Hits a player.
        bool check_more = true;
        if((((BALL.x+2) == (GK_BLUE.x-X_LEN)) || ((BALL.x-2) == (GK_BLUE.x+X_LEN))) && (BALL.y == GK_BLUE.y)) {
            BALL.velocity_x *= -1;
            BALL.velocity_y = 0;
            check_more = false;
        }
        else if((((BALL.x+2) == (GK_BLUE.x-X_LEN)) || ((BALL.x-2) == (GK_BLUE.x+X_LEN))) && ((BALL.y >= GK_BLUE.y-Y_LEN) && (BALL.y <= GK_BLUE.y+Y_LEN))) {
            BALL.velocity_x *= -1;     
            if(rand()%2 == 0) BALL.velocity_y = -1;
            else BALL.velocity_y = 1;    
            check_more = false;   
        }
        else if((((BALL.x+2) == (GK_RED.x-X_LEN)) || ((BALL.x-2) == (GK_RED.x+X_LEN))) && (BALL.y == GK_RED.y)) {
            BALL.velocity_x *= -1;
            BALL.velocity_y = 0;
            check_more = false;
        }
        else if((((BALL.x+2) == (GK_RED.x-X_LEN)) || ((BALL.x-2) == (GK_RED.x+X_LEN))) && ((BALL.y >= GK_RED.y-Y_LEN) && (BALL.y <= GK_RED.y+Y_LEN))) {
            BALL.velocity_x *= -1;     
            if(rand()%2 == 0) BALL.velocity_y = -1;
            else BALL.velocity_y = 1; 
            check_more = false;      
        }  
        else if(check_more) {
            int i;
            for(i = 0; i < 2; i++) {
                if((((BALL.x+2) == (DEF_BLUE[i].x-X_LEN)) || ((BALL.x-2) == (DEF_BLUE[i].x+X_LEN))) && (BALL.y == DEF_BLUE[i].y)) {
                    BALL.velocity_x *= -1;
                    BALL.velocity_y = 0;
                    check_more = false;
                    break;
                }
                else if((((BALL.x+2) == (DEF_BLUE[i].x-X_LEN)) || ((BALL.x-2) == (DEF_BLUE[i].x+X_LEN))) && ((BALL.y >= DEF_BLUE[i].y-Y_LEN) && (BALL.y <= DEF_BLUE[i].y+Y_LEN))) {
                    BALL.velocity_x *= -1;     
                    if(rand()%2 == 0) BALL.velocity_y = -1;
                    else BALL.velocity_y = 1;
                    check_more = false;   
                    break;   
                }    
            }
            if(check_more) {
                for(i = 0; i < 2; i++) {
                    if((((BALL.x+2) == (DEF_RED[i].x-X_LEN)) || ((BALL.x-2) == (DEF_RED[i].x+X_LEN))) && (BALL.y == DEF_RED[i].y)) {
                        BALL.velocity_x *= -1;
                        BALL.velocity_y = 0;
                        check_more = false;
                        break;
                    }
                    else if((((BALL.x+2) == (DEF_RED[i].x-X_LEN)) || ((BALL.x-2) == (DEF_RED[i].x+X_LEN))) && ((BALL.y >= DEF_RED[i].y-Y_LEN) && (BALL.y <= DEF_RED[i].y+Y_LEN))) {
                        BALL.velocity_x *= -1;     
                        if(rand()%2 == 0) BALL.velocity_y = -1;
                        else BALL.velocity_y = 1;
                        check_more = false;   
                        break;   
                    }                
                }
            }
            if(check_more) {
                for(i = 0; i < 4; i++) {
                    if((((BALL.x+2) == (MID_BLUE[i].x-X_LEN)) || ((BALL.x-2) == (MID_BLUE[i].x+X_LEN))) && (BALL.y == MID_BLUE[i].y)) {
                        BALL.velocity_x *= -1;
                        BALL.velocity_y = 0;
                        check_more = false;
                        break;
                    }
                    else if((((BALL.x+2) == (MID_BLUE[i].x-X_LEN)) || ((BALL.x-2) == (MID_BLUE[i].x+X_LEN))) && ((BALL.y >= MID_BLUE[i].y-Y_LEN) && (BALL.y <= MID_BLUE[i].y+Y_LEN))) {
                        BALL.velocity_x *= -1;     
                        if(rand()%2 == 0) BALL.velocity_y = -1;
                        else BALL.velocity_y = 1;
                        check_more = false;   
                        break;   
                    }                
                }                
            }
            if(check_more) {
                for(i = 0; i < 4; i++) {
                    if((((BALL.x+2) == (MID_RED[i].x-X_LEN)) || ((BALL.x-2) == (MID_RED[i].x+X_LEN))) && (BALL.y == MID_RED[i].y)) {
                        BALL.velocity_x *= -1;
                        BALL.velocity_y = 0;
                        check_more = false;
                        break;
                    }
                    else if((((BALL.x+2) == (MID_RED[i].x-X_LEN)) || ((BALL.x-2) == (MID_RED[i].x+X_LEN))) && ((BALL.y >= MID_RED[i].y-Y_LEN) && (BALL.y <= MID_RED[i].y+Y_LEN))) {
                        BALL.velocity_x *= -1;     
                        if(rand()%2 == 0) BALL.velocity_y = -1;
                        else BALL.velocity_y = 1;
                        check_more = false;   
                        break;   
                    }                
                }                
            }
            if(check_more) {
                for(i = 0; i < 3; i++) {
                    if((((BALL.x+2) == (ATK_BLUE[i].x-X_LEN)) || ((BALL.x-2) == (ATK_BLUE[i].x+X_LEN))) && (BALL.y == ATK_BLUE[i].y)) {
                        BALL.velocity_x *= -1;
                        BALL.velocity_y = 0;
                        check_more = false;
                        break;
                    }
                    else if((((BALL.x+2) == (ATK_BLUE[i].x-X_LEN)) || ((BALL.x-2) == (ATK_BLUE[i].x+X_LEN))) && ((BALL.y >= ATK_BLUE[i].y-Y_LEN) && (BALL.y <= ATK_BLUE[i].y+Y_LEN))) {
                        BALL.velocity_x *= -1;     
                        if(rand()%2 == 0) BALL.velocity_y = -1;
                        else BALL.velocity_y = 1;
                        check_more = false;   
                        break;   
                    }                
                }                
            }
            if(check_more) {
                for(i = 0; i < 3; i++) {
                    if((((BALL.x+2) == (ATK_RED[i].x-X_LEN)) || ((BALL.x-2) == (ATK_RED[i].x+X_LEN))) && (BALL.y == ATK_RED[i].y)) {
                        BALL.velocity_x *= -1;
                        BALL.velocity_y = 0;
                        check_more = false;
                        break;
                    }
                    else if((((BALL.x+2) == (ATK_RED[i].x-X_LEN)) || ((BALL.x-2) == (ATK_RED[i].x+X_LEN))) && ((BALL.y >= ATK_RED[i].y-Y_LEN) && (BALL.y <= ATK_RED[i].y+Y_LEN))) {
                        BALL.velocity_x *= -1;     
                        if(rand()%2 == 0) BALL.velocity_y = -1;
                        else BALL.velocity_y = 1;
                        check_more = false;   
                        break;   
                    }                
                }                
            }    
        }  
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

void HEX(int b1, int b2, int b3) {
    volatile int * HEX3_HEX0_ptr = (int *)HEX3_HEX0_BASE;
    volatile int * HEX5_HEX4_ptr = (int *)HEX5_HEX4_BASE;
	
	//New vars
	int b1_a = b1 % 10;
	int b1_b = b1 / 10;
	int b2_a = b2 % 10;
	int b2_b = b2 / 10;
	int b3_a = b3 % 10;
	int b3_b = b3 / 10;
	
    /* SEVEN_SEGMENT_DECODE_TABLE gives the on/off settings for all segments in
     * a single 7-seg display in the DE2 Media Computer, for the hex digits 0 -
     * F */
    unsigned char seven_seg_decode_table[] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
        0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    unsigned char hex_segs[] = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned int  shift_buffer, nibble;
    unsigned char code;
    int           i;

    shift_buffer = (b3_b << 20) | (b3_a << 16) | (b1_b << 12) | (b1_a << 8) | (b2_b << 4) | b2_a;
    for (i = 0; i < 6; ++i) {
        nibble = shift_buffer & 0x0000000F; // character is in rightmost nibble
        code   = seven_seg_decode_table[nibble];
        hex_segs[i]  = code;
        shift_buffer = shift_buffer >> 4;
    }
    /* drive the hex displays */
    *(HEX3_HEX0_ptr) = *(int *)(hex_segs);
    *(HEX5_HEX4_ptr) = *(int *)(hex_segs + 4);
}
