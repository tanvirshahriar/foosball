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

// Interrupt settings.
void set_A9_IRQ_stack(void);
void config_GIC(void);
void enable_A9_interrupts(void);

void wait_for_vsync();
void read_keyboard();

int main(void) {
    // Variables.
    volatile int *pixel_ctrl_ptr = (int *)0xFF203020;
    volatile int *PS2_ptr = (int *)PS2_BASE;

    // PS2 input.
    int PS2_data, RVALID;
    *(PS2_ptr) = 0xFF; // Reset

    // Initialize the field.
    initialize_field();

    // Set up VGA buffer.
    *(pixel_ctrl_ptr + 1) = 0xC8000000;
    wait_for_vsync();
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();
    *(pixel_ctrl_ptr + 1) = 0xC0000000;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);

    // All drawing goes in this loop.
    while (1) {
        // Get PS2 input.
        PS2_data = *(PS2_ptr);
        RVALID = PS2_data & 0x8000; 
        // Clear before every draw.
        clear_screen();
        // Game activity.
        move_objects();
        
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

void read_keyboard() {

}


/*-------From the DE1-SoC Manual----*/

// Initialize the banked stack pointer register for IRQ mode

void set_A9_IRQ_stack(void)
{
int stack, mode;
stack = A9_ONCHIP_END - 7; // top of A9 onchip memory, aligned to 8 bytes
/* change processor to IRQ mode with interrupts disabled */
mode = INT_DISABLE | IRQ_MODE;
asm("msr cpsr, %[ps]" : : [ps] "r"(mode));
/* set banked stack pointer */
asm("mov sp, %[ps]" : : [ps] "r"(stack));
/* go back to SVC mode before executing subroutine return! */
mode = INT_DISABLE | SVC_MODE;
asm("msr cpsr, %[ps]" : : [ps] "r"(mode));
}

// Turn on interrupts in the ARM processor
void enable_A9_interrupts(void) {
int status = SVC_MODE | INT_ENABLE;
asm("msr cpsr, %[ps]" : : [ps] "r"(status));
}

// Configure the Generic Interrupt Controller (GIC)
void config_GIC(void) {
int address; // used to calculate register addresses
/* configure the HPS timer interrupt */
*((int *)0xFFFED8C4) = 0x01000000;
*((int *)0xFFFED118) = 0x00000080;
/* configure the FPGA interval timer and KEYs interrupts */
*((int *)0xFFFED848) = 0x00000101;
*((int *)0xFFFED108) = 0x00000300;
// Set Interrupt Priority Mask Register (ICCPMR). Enable interrupts of all
// priorities
address = MPCORE_GIC_CPUIF + ICCPMR;
*((int *)address) = 0xFFFF;
Intel Corporation - FPGA University Program
November 2017
53
DE1-SOC COMPUTER SYSTEM WITH ARM* CORTEX* A9 For Quartus® Prime 17.1
// Set CPU Interface Control Register (ICCICR). Enable signaling of
// interrupts
address = MPCORE_GIC_CPUIF + ICCICR;
*((int *)address) = ENABLE;
// Configure the Distributor Control Register (ICDDCR) to send pending
// interrupts to CPUs
address = MPCORE_GIC_DIST + ICDDCR;
*((int *)address) = ENABLE;
}