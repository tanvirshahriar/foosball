/*Maintains all interrupt handling and settings*/
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "globals.h"
#include "address_map_arm.h"

#define		CPU0	    0x01	// bit-mask; bit 0 represents cpu0
#define		ENABLE		0x1

// Declarations.
extern int ps2_byte_1, ps2_byte_2, ps2_byte_3;
extern Players GK_BLUE, GK_RED;
extern Players DEF_BLUE[2], DEF_RED[2];
extern Players MID_BLUE[4], MID_RED[4];
extern Players ATK_BLUE[3], ATK_RED[3];
extern Ball BALL;

// Interrupt mode setup.
void set_A9_IRQ_stack(void);
void config_GIC(void);
void enable_A9_interrupts(void);
void config_KEYs();
void config_PS2();
void config_interrupt (int int_ID, int CPU_target);
void hw_write_bits(volatile int * addr, volatile int unmask, volatile int value);

// Service Routines.
void PS2_ISR();
void KEY_ISR();
void p1_move(int pos_change);
void p2_move(int pos_change);

#endif