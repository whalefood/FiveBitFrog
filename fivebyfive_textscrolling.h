/*
 *	fivebyfive_textscrolling.h - simple font scrolling library
 *
 *	revision history:
 * - Feb 26, 2013 - Jonah
 *          separated and combined font library into text scrolling lib
 *
 *	- dec 2, 2007 - rolf
 *		created.
 *
 */

#ifndef FIVEBYFIVE_TEXTSCROLLING_H
#define FIVEBYFIVE_TEXTSCROLLING_H

#include "fivebyfive.h"

void loadfontcharintobuffer(unsigned char c, uint16_t * buffer, uint8_t *fontWidth );

// scrolls text accross the screen
// speed: adjusts scrolling speed (higher number == slower, 35-40 seems about right)
// repeat: 1 to repeat scrolling.  0 to display text once
void fivebyfivetext_scrolltext(char* text, uint8_t speed, uint8_t repeat);

#endif