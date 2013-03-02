/*
 * fivebyfive.h - various definitions for this project
 *
 * Copyright (c) 2011 - Rolf van WidenfeltSome rights reserved.
 *
 * Note: This source code is licensed under a Creative Commons License, CC-by-nc-sa.
 *		(attribution, non-commercial, share-alike)
 *  	see http://creativecommons.org/licenses/by-nc-sa/3.0/ for details.
 *
 *	revision history:
 *
 *	12/19/2011 - rolf
 *		added NOP() macro
 *
 */

#ifndef fivebyfive_h
#define fivebyfive_h

extern "C" {
#include <inttypes.h>
#include <avr/io.h>				/* this takes care of definitions for our specific AVR */
#include <avr/interrupt.h>		/* for interrupts, ISR macro, etc. */
}

#include "fivebyfive_iodefs.h"

/* CPU frequency (8000000UL == 8 MHz) */
#define F_CPU 8000000UL


/* public constants go here */
// XXX none!

/* NOP (adds a 1 cycle delay to your code) */
#define NOP()	__asm__ volatile("nop"::)


void fivebyfive_init();


uint8_t buttonispressed();

//
// set pixel at (x, y) to val (1 = on, 0 = off)
//
//	note:  top left is (0, 0) and bottom right is (4, 4).
//
void setpixel(uint8_t x, uint8_t y, uint8_t val);


// draws a 5x5 display frame (Disp must be len 5 array)
// note: frame disapears after drawn.  Must repeatedly to call this method to get lasting image
void drawFrame(uint8_t *Disp);

// delay (each count is roughly 1ms)
// note: valid range for c is 0..255
//
void delay1(uint8_t c);

//
// delay (each count is roughly 10ms)
// note: valid range for c is 0..255
//
void delay10(uint8_t c);


#endif /* fivebyfive_h */
