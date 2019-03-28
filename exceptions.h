/*Maintains all interrupt handling and settings*/
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "globals.h"

// Forward declarations.
int ps2_byte_1, ps2_byte_2, ps2_byte_3;
Players GK_BLUE, GK_RED;
Players DEF_BLUE[2], DEF_RED[2];
Players MID_BLUE[4], MID_RED[4];
Players ATK_BLUE[3], ATK_RED[3];
Ball BALL;

// Interrupt mode setup.
void set_A9_IRQ_stack(void);
void config_GIC(void);
void enable_A9_interrupts(void);
void config_KEYs();
void config_PS2();

// Service Routines.
void PS2_ISR();
void KEY_ISR();
void p1_move(int pos_change);
void p2_move(int pos_change);

#endif