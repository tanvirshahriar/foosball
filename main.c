/***************************************************************
 * Foosball game displayed on VGA. 2 players. Keyboard inputs. *
 * Line-up : 1 - 2 - 4 - 3.                                    * 
 * Scores displyed on FGPA HEX.                                *
 ***************************************************************/
#include "address_map_arm.h"
#include "draw_graphics.h"
#include "objects.h"
#include "globals.h"
#include <stdbool.h>
#include <math.h>

void wait_for_vsync();

int main(void) {
    // Variables.
    volatile int *pixel_ctrl_ptr = (int *)0xFF203020;

    // Initialize the field.
    initialize_field();
    telstar.x = 159;
    telstar.y = 119;
    telstar.velocity_x = (rand() % 2) * pow(-1, rand());
    telstar.velocity_y = rand() % 2 * pow(-1, rand());

    // Set up VGA buffer.
    *(pixel_ctrl_ptr + 1) = 0xC8000000;
    wait_for_vsync();
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();
    *(pixel_ctrl_ptr + 1) = 0xC0000000;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);

    // All drawing goes in this loop.
    while (1) {
        // Clear before every draw.
        clear_screen();
        
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