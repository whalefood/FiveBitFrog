/*
 * fivebyfive_scrolltext.c - simple "text scrolling" test for FiveByFive badge circuit
 *
 * Copyright (c) 2012-2013 - Rolf van Widenfelt - Some rights reserved.
 *
 * Note: This source code is licensed under a Creative Commons License, CC-by-nc-sa.
 *		(attribution, non-commercial, share-alike)
 *  	see http://creativecommons.org/licenses/by-nc-sa/3.0/ for details.
 *
 *
 *	TODO:
 *		need to work out an efficient scrolling bitmap and display.
 *
 *		(answer)
 *		use "pixel groups" which are groups of 4-5 pixels which
 *		can be lit simultaneously.
 *		there are 6 pixel groups that cover all 25 pixels, yielding a 1/6 duty cycle for each LED.
 *
 *	revision history:
 *  - Feb 27, 2013 - Jonah
 *      separated the scrolltext fucntionality into separate files + refactoring
 *
 *	- jan 8, 2013 - rolf
 *		cleaned up code from original demo.  (based on older scrolltext.c of jun 28, 2012)
 *
 */

#include "fivebyfive.h"			/* for now, this defines clock speed F_CPU */


#include <util/delay.h>
/* defines IO pins, and output_low(), output_high() macros */



/* lookup table and related macros for charlie-plexed LEDs */

#define PACK(h,l)	((h<<4)|l)
#define UNPACKH(b)	((b>>4)&0xf)
#define UNPACKL(b)	(b&0xf)
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5

uint8_t LEDS[25] = {
	PACK(F,E),		/* top row, left to right */
	PACK(F,D),
	PACK(F,C),
	PACK(F,B),
	PACK(F,A),
	
	PACK(D,E),
	PACK(E,D),
	PACK(E,C),
	PACK(E,B),
	PACK(E,A),
	
	PACK(C,E),
	PACK(C,D),
	PACK(D,C),
	PACK(D,B),
	PACK(D,A),
	
	PACK(B,E),
	PACK(B,D),
	PACK(B,C),
	PACK(C,B),
	PACK(C,A),
	
	PACK(A,E),		/* bottom row, left to right */
	PACK(A,D),
	PACK(A,C),
	PACK(A,B),
	PACK(B,A),
};


// display buffer - this contains 25 "bits" that are displayed
// (we use the 5 LSBs of each byte)
uint8_t Disp[5];

// global flag that indicates whether we can use F_LINE for detecting switch presses
uint8_t FLineEnabled;

// forward references
void setpixel(uint8_t x, uint8_t y, uint8_t val);
void Refresh(void);

static void avrinit(void);
void delay1(uint8_t c);
void delay10(uint8_t c);
void blinkn(uint8_t n);


//pixel group arrays.  Each pixel group arrangment repressented by 5 uint8's
uint8_t PixelGroups[6][5] ={
    {0x1f,0x00,0x00,0x00,0x00},
    {0x00,0x0f,0x00,0x00,0x00},
    {0x00,0x10,0x07,0x00,0x00},
    {0x00,0x00,0x18,0x03,0x00},
    {0x00,0x00,0x00,0x1c,0x01},
    {0x00,0x00,0x00,0x00,0x1e}
};


uint8_t initialized = 0;
void fivebyfive_init()
{
    if(initialized)
        return;
    initialized = 1;
    
    avrinit();		// initialize AVR registers
    
    //
    // this is not the official way of figuring out whether the RSTDISBL fuse has been programmed,
    //	but it is a good substitute!
    //	(just don't press the button while powering on)
    //
    
    // immediately we poll switch - if it "seems" on (i.e. low), then probably it isn't working!  (leave it disabled)
    
    input_test(F_LINE);	// dummy read
    NOP();
    if (input_test(F_LINE) != 0) {		// enable switch (i.e. F_LINE) if this reads high
        FLineEnabled = 1;
    }
    
    // blink one of the LEDs... 4 times indicates that we are using 6 IO pins (otherwise it is 5 IO pins)
    if (FLineEnabled) {
        blinkn(4);
    } else {
        blinkn(3);
    }
}

uint8_t buttonispressed()
{
    return  FLineEnabled && (input_test(F_LINE) == 0) ? 1 : 0;
}


void setpixel(uint8_t x, uint8_t y, uint8_t val);

void drawFrame(uint8_t *frame)
{
    //must display each pixel group separately
    for(uint8_t grpNum =0; grpNum<6; grpNum++)
    {
       
        //setpixels that are intersection of pixel group and frame buffer
        uint8_t * pixGrp = PixelGroups[grpNum];
        for(uint8_t row=0; row<5; row++)
        {
            uint8_t colMask = 0x10;
            for(uint8_t col = 0; col < 5; col++)
            {
                if(pixGrp[row] & colMask & frame[row])
                {
                    setpixel(col, row, 1);
                }
                colMask >>=1;
            }
        }
        delay1(1);
        
        //turn off all pixels
        for(uint8_t row=0; row<5; row++)
        {
            uint8_t colMask = 0x10;
            for(uint8_t col = 0; col < 5; col++)
            {
                if(pixGrp[row] & colMask)
                {
                    setpixel(col,row, 0);
                }
                colMask >>=1;
            }
        }
    }
    
}

//
// set pixel at (x, y) to val (1 = on, 0 = off)
//
//	note:  top left is (0, 0) and bottom right is (4, 4).
//
void setpixel(uint8_t x, uint8_t y, uint8_t val)
{
	uint8_t n, b;
	uint8_t hi, lo;
	
	//n = x + 5*y;
	n = x + (y<<2) + y;		// equivalent to "n = x + 5*y" but avoids mult operation (attiny doesn't have MUL!)
	
	b = LEDS[n];			// get hi,lo nibbles from LED lookup table
	hi = UNPACKH(b);
	lo = UNPACKL(b);
    
	
	// enable/disable the high pin
	switch (hi) {
        case A:
            if (val) {
                output_enable(A_LINE);
                output_high(A_LINE);
            } else {
                output_low(A_LINE);
                output_disable(A_LINE);
            }
            break;
            
        case B:
            if (val) {
                output_enable(B_LINE);
                output_high(B_LINE);
            } else {
                output_low(B_LINE);
                output_disable(B_LINE);
            }
            break;
            
        case C:
            if (val) {
                output_enable(C_LINE);
                output_high(C_LINE);
            } else {
                output_low(C_LINE);
                output_disable(C_LINE);
            }
            break;
            
        case D:
            if (val) {
                output_enable(D_LINE);
                output_high(D_LINE);
            } else {
                output_low(D_LINE);
                output_disable(D_LINE);
            }
            break;
            
        case E:
            if (val) {
                output_enable(E_LINE);
                output_high(E_LINE);
            } else {
                output_low(E_LINE);
                output_disable(E_LINE);
            }
            break;
            
        case F:
            if (val) {
                output_enable(F_LINE);
                //output_high(F_LINE);
                output_low(F_LINE);			// XXX hack for V0.9 board - F_LINE is ALWAYS low
            } else {
                //output_low(F_LINE);
                output_disable(F_LINE);
            }
            break;
            
	}
    
    
	// low pin
	switch (lo) {
        case A:
            if (val) {
                output_enable(A_LINE);
                output_low(A_LINE);
            } else {
                output_disable(A_LINE);
            }
            break;
            
        case B:
            if (val) {
                output_enable(B_LINE);
                output_low(B_LINE);
            } else {
                output_disable(B_LINE);
            }
            break;
            
        case C:
            if (val) {
                output_enable(C_LINE);
                output_low(C_LINE);
            } else {
                output_disable(C_LINE);
            }
            break;
            
        case D:
            if (val) {
                output_enable(D_LINE);
                output_low(D_LINE);
            } else {
                output_disable(D_LINE);
            }
            break;
            
        case E:
            if (val) {
                output_enable(E_LINE);
                output_low(E_LINE);
            } else {
                output_disable(E_LINE);
            }
            break;
#ifdef NOTDEF
            // note: this case does not occur!
        case F:
            if (val) {
                output_enable(F_LINE);
                output_low(F_LINE);
            } else {
                output_disable(F_LINE);
            }
            break;
#endif		
	}
}




/*
 *
 *	low level init needed for AVR.  (attiny25/45/85)
 *
 *	note: settings below MUST be in sync with actual hardware!  (also see fivebyfive_iodefs.h)
 */
static void avrinit(void)
{
    
	cli();		// disable global interrupts (this may not be needed)
	
	// note: DDR pins are set to "1" to be an output, "0" for input.
    
	// bits   76543210
	PORTB = 0b00000000;			// (see above)
	DDRB  = 0b00000000;			// (see above)
    
	sei();		// enable global interrupts (individual interrupts still need to be enabled)
}


//
// delay (each count is roughly 1ms)
// note: valid range for c is 0..255
//
void delay1(uint8_t c)
{
	while (c--) {
        _delay_ms(1);
    }
	
}

//
// delay (each count is roughly 10ms)
// note: valid range for c is 0..255
//
void delay10(uint8_t c)
{
	while (c--) {
        _delay_ms(10);
	}
}

//
// blink a specific LED (at x,y) "n" times
//
void blinkn(uint8_t n)
{
	uint8_t del;
	uint8_t x = 0;
	uint8_t y = 1;
	uint8_t i;
    
	/* blink LED6 (at 0,1) "n" times */
    
	del = 25;
	for (i = 0; i < n; i++) {
		setpixel(x, y, 1);	// LED(x,y) on
		delay10(del);
		setpixel(x, y, 0);	// LED(x,y) off
		delay10(del);
	}
}
