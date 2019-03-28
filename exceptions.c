#include "exceptions.h"

void config_PS2() {
    volatile int *PS2_ptr = (int *) 0xFF200100;
    *(PS2_ptr + 1) = 1;
}

// Define the IRQ exception handler.
void __attribute__ ((interrupt)) __cs3_isr_irq (void) {
    // Read the ICCIAR.
    int int_ID = *((int *) 0xFFFEC10C);

    if (int_ID == 79) // check if interrupt is from PS2 device.
        PS2_ISR();
    else if (int_ID == 73) // check if interrupt is from the KEYs.
        KEY_ISR();
    else
        while (1) // Unexpected.

    // Write to ICCEOIR.
    *((int *) 0xFFFEC110) = int_ID;
    return;
}

// Define the remaining exception handlers.
void __attribute__ ((interrupt)) __cs3_isr_undef (void) {
    while (1);
}
void __attribute__ ((interrupt)) __cs3_isr_swi (void) {
    while (1);
}
void __attribute__ ((interrupt)) __cs3_isr_pabort (void) {
    while (1);
}
void __attribute__ ((interrupt)) __cs3_isr_dabort (void) {
    while (1);
}
void __attribute__ ((interrupt)) __cs3_isr_fiq (void) {
    while (1);
}

// PS2 service routine.
void PS2_ISR() {
    volatile int * PS2_ptr = (int *) 0xFF200100; // PS/2 port address
    int PS2_data, RVALID;
    
    PS2_data = *(PS2_ptr); // read the Data register in the PS/2 port
    RVALID = PS2_data & 0x8000; // extract the RVALID field
    if (RVALID) {
        // Save the last three bytes of data.
        ps2_byte_1 = ps2_byte_2;
        ps2_byte_2 = ps2_byte_3;
        ps2_byte_3 = PS2_data & 0xFF;  

        // Process data.
        if(ps2_byte_1 == 0xE0 && ps2_byte_2 == 0xF0 && ps2_byte_3 == 0x74) {
            if(p1_sel == 3) p1_sel = 0;
            else p1_sel++; // RIGHT
        }
        else if(ps2_byte_1 == 0xE0 && ps2_byte_2 == 0xF0 && ps2_byte_3 == 0x6B) {
            if(p1_sel == 0) p1_sel = 3;
            else p1_sel--; // LEFT
        }
        else if(ps2_byte_2 == 0xF0 && ps2_byte_3 == 0x23) {
            if(p2_sel == 3) p2_sel = 0;
            else p2_sel++; // D
        }
        else if(ps2_byte_2 == 0xF0 && ps2_byte_3 == 0x1B) {
            if(p2_sel == 0) p2_sel = 3;
            else p2_sel--; // A
        }
        else if(ps2_byte_1 == 0xE0 && ps2_byte_2 == 0xF0 && ps2_byte_3 == 0x75) {
            p1_move(1); // UP
        }
        else if(ps2_byte_1 == 0xE0 && ps2_byte_2 == 0xF0 && ps2_byte_3 == 0x72) {
            p1_move(-1); // DOWN
        }
        else if(ps2_byte_2 == 0xF0 && ps2_byte_3 == 0x1D) {
            p2_move(1); // W
        }
        else if(ps2_byte_2 == 0xF0 && ps2_byte_3 == 0x1B) {
            p2_move(-1); // S
        }
        else {
            return;
        }
    }
}

// Move player 1 objects.
void p1_move(int pos_change) {
    if(p1_sel == 0) {
        if((GK_BLUE.y == 0) && (pos_change == -1)) return;
        if((GK_BLUE.y == 239) && (pos_change == 1)) return;
        GK_BLUE.y += pos_change;
    }
    if(p1_sel == 1) {
        if((DEF_BLUE[0].y == 0) && (pos_change == -1)) return;
        if((DEF_BLUE[1].y == 239) && (pos_change == 1)) return;
        DEF_BLUE[0].y += pos_change;
        DEF_BLUE[1].y += pos_change;
    }
    if(p1_sel == 2) {
        if((MID_BLUE[0].y == 0) && (pos_change == -1)) return;
        if((MID_BLUE[3].y == 239) && (pos_change == 1)) return;
        MID_BLUE[0].y += pos_change;
        MID_BLUE[1].y += pos_change;
        MID_BLUE[2].y += pos_change;
        MID_BLUE[3].y += pos_change;
    }
    if(p1_sel == 3) {
        if((ATK_BLUE[0].y == 0) && (pos_change == -1)) return;
        if((ATK_BLUE[2].y == 239) && (pos_change == 1)) return;
        ATK_BLUE[0].y += pos_change;
        ATK_BLUE[1].y += pos_change;
        ATK_BLUE[2].y += pos_change;
    }
}

// Move player 2 objects.
void p2_move(int pos_change) {
    if(p2_sel == 0) {
        if((GK_RED.y == 0) && (pos_change == -1)) return;
        if((GK_RED.y == 239) && (pos_change == 1)) return;
        GK_RED.y += pos_change;
    }
    if(p2_sel == 1) {
        if((DEF_RED[0].y == 0) && (pos_change == -1)) return;
        if((DEF_RED[1].y == 239) && (pos_change == 1)) return;
        DEF_RED[0].y += pos_change;
        DEF_RED[1].y += pos_change;
    }
    if(p2_sel == 2) {
        if((MID_RED[0].y == 0) && (pos_change == -1)) return;
        if((MID_RED[3].y == 239) && (pos_change == 1)) return;
        MID_RED[0].y += pos_change;
        MID_RED[1].y += pos_change;
        MID_RED[2].y += pos_change;
        MID_RED[3].y += pos_change;
    }
    if(p2_sel == 3) {
        if((ATK_RED[0].y == 0) && (pos_change == -1)) return;
        if((ATK_RED[2].y == 239) && (pos_change == 1)) return;
        ATK_RED[0].y += pos_change;
        ATK_RED[1].y += pos_change;
        ATK_RED[2].y += pos_change;
    }    
}

// KEYs service routine.
void KEY_ISR() {
    while(1);
}

/*--------------From the DE1-SoC Manual-----------------------*/

// Initialize the banked stack pointer register for IRQ mode
void set_A9_IRQ_stack(void) {
    int stack, mode;
    stack = 0xFFFFFFFF - 7; // top of A9 on-chip memory, aligned to 8 bytes
    /* change processor to IRQ mode with interrupts disabled */
    mode = 0b11010010;
    asm("msr cpsr, %[ps]" : : [ps] "r" (mode));
    /* set banked stack pointer */
    asm("mov sp, %[ps]" : : [ps] "r" (stack));
    /* go back to SVC mode before executing subroutine return! */
    mode = 0b11010011;
    asm("msr cpsr, %[ps]" : : [ps] "r" (mode));
}

// Turn on interrupts in the ARM processor.
void enable_A9_interrupts(void) {
    int status = 0b01010011;
    asm("msr cpsr, %[ps]" : : [ps]"r"(status));
}

// Configure the Generic Interrupt Controller (GIC).
void config_GIC(void) {
    /* configure the HPS timer interrupt */
    *((int *) 0xFFFED8C4) = 0x01000000;
    *((int *) 0xFFFED118) = 0x00000080;
    /* configure the FPGA interval timer and KEYs interrupts */
    *((int *) 0xFFFED848) = 0x00000101;
    *((int *) 0xFFFED108) = 0x00000300;
    // Set Interrupt Priority Mask Register (ICCPMR). Enable interrupts of all priorities
    *((int *) 0xFFFEC104) = 0xFFFF;
    // Set CPU Interface Control Register (ICCICR). Enable signaling of interrupts
    *((int *) 0xFFFEC100) = 1; // enable = 1
    // Configure the Distributor Control Register (ICDDCR) to send pending interrupts to CPUs
    *((int *) 0xFFFED000) = 1; // enable = 1
}

// setup the KEY interrupts in the FPGA.
void config_KEYs() {
    volatile int * KEY_ptr = (int *) 0xFF200050; // pushbutton KEY address
    *(KEY_ptr + 2) = 0xF; // enable interrupts for all four KEYs
}