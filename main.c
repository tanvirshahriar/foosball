/***************************************************************
 * Foosball game displayed on VGA. 2 players. Keyboard inputs. *
 * Line-up : 1 - 2 - 4 - 3.                                    * 
 * Scores displyed on FGPA HEX (in Hex number format!).        *
 ***************************************************************/
#include "address_map_arm.h"
#include "draw_graphics.h"
#include "exceptions.h"
#include "objects.h"
#include "globals.h"
#include "utils.h"
#include <stdbool.h>
#include <math.h>
#include <time.h>

void wait_for_vsync();

// Forward declarations.
int p1_sel=0, p2_sel=3;
int p1_score=0, p2_score=0, time_now=0;
volatile int pixel_buffer_start;
int ps2_byte_1, ps2_byte_2, ps2_byte_3, goal=0, reset=0;
Players GK_BLUE, GK_RED;
Players DEF_BLUE[2], DEF_RED[2];
Players MID_BLUE[4], MID_RED[4];
Players ATK_BLUE[3], ATK_RED[3];
Ball BALL;


int main(void) {
    set_A9_IRQ_stack();
    config_GIC();
    config_PS2();
	config_MPcore_private_timer();

    enable_A9_interrupts();
    
    // Seed rands.
    srand(time(0));

    // Variables.
    volatile int *pixel_ctrl_ptr = (int *)0xFF203020;
    //bool goal = false;

    // Set up VGA buffer.
    *(pixel_ctrl_ptr + 1) = 0xC8000000;
    wait_for_vsync();
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();
    *(pixel_ctrl_ptr + 1) = 0xC0000000;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);

    // Initialize the field.
    initialize_field();
    // Initialize Timer.
    //time_t timer = time(NULL);
    //int display_time = 0;   // Game time in minutes.

    // All drawing goes in this loop.
    while (1) {
        // Clear before every draw.
        clear_screen();
        // Update game.
        ball_mechanics();
        // Redraw game.
        if(reset == 1) {
            initialize_field();
            // display_time = 0;
            p1_score = 0;
            p2_score = 0;
			time_now = 0;
            reset = 0;
        }
        else if(goal == 1) {
            initialize_field();
            //goal = false;
            goal = 0;
        }
        else
            draw_field();
        
        // if(time(NULL) == (timer + 60)) {
        //     timer = time(NULL);
        //     display_time++;
        // }

        HEX(p1_score, p2_score, time_now);

        wait_for_vsync(); // Swap front and back buffers on VGA vertical sync.
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // New back buffer.
    }
}

// Additional functions.
void wait_for_vsync() {
    volatile int *pixel_ctrl_ptr = (int *)0xFF203020;   
    *pixel_ctrl_ptr = 1;
    volatile int *status = pixel_ctrl_ptr + 3;
    while(1) {
        if((*status & 1) == 0) break;
    } 
    return;
}