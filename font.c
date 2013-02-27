/*
 *	font.c - a simple 5 pixel height font library
 *
 *	description:
 *
 *		not all ASCII characters are included, because of space limitations!
 *		currently, the following characters are included:
 *			ABCDEFGHIJKLMONOPQRSTUVWXYZ1234567890
 *			and a few others.
 *
 *
 *	revision history:
 *
 *	- jan 8, 2013 - rolf
 *		(comment only)
 *
 *	- nov 26, 2012 - rolf
 *		add filled heart for char \xF1 (but commented out for now)
 *
 *	- nov 11, 2012 - rolf
 *		add various new chars, such as "+" and "=".
 *		note: be careful, since each new char adds to code space.
 *
 *	- dec 2, 2007 - rolf
 *		created.
 *
 */

#include "fivebyfive_textscrolling.h"


// typing saver
typedef uint16_t uns16;

//
//	loads a given character into global font array (and loads width too)
//
void loadfontcharintobuffer(unsigned char c, uint16_t * buffer, uint8_t *fontWidth )
{
    uint8_t width;
    
	switch (c) {
	case 'A':
		buffer[0] = (uns16) 0x06 << 4;
		buffer[1] = (uns16) 0x09 << 4;
		buffer[2] = (uns16) 0x0f << 4;
		buffer[3] = (uns16) 0x09 << 4;
		buffer[4] = (uns16) 0x09 << 4;
		width = 5;
		break;
	case 'B':
		buffer[0] = (uns16) 0x0e << 4;
		buffer[1] = (uns16) 0x09 << 4;
		buffer[2] = (uns16) 0x0e << 4;
		buffer[3] = (uns16) 0x09 << 4;
		buffer[4] = (uns16) 0x0e << 4;
		width = 5;
		break;
	case 'C':
		buffer[0] = (uns16) 0x07 << 4;
		buffer[1] = (uns16) 0x08 << 4;
		buffer[2] = (uns16) 0x08 << 4;
		buffer[3] = (uns16) 0x08 << 4;
		buffer[4] = (uns16) 0x07 << 4;
		width = 5;
		break;
	case 'D':
		buffer[0] = (uns16) 0x0e << 4;
		buffer[1] = (uns16) 0x09 << 4;
		buffer[2] = (uns16) 0x09 << 4;
		buffer[3] = (uns16) 0x09 << 4;
		buffer[4] = (uns16) 0x0e << 4;
		width = 5;
		break;
	case 'E':
		buffer[0] = (uns16) 0x0f << 4;
		buffer[1] = (uns16) 0x08 << 4;
		buffer[2] = (uns16) 0x0e << 4;
		buffer[3] = (uns16) 0x08 << 4;
		buffer[4] = (uns16) 0x0f << 4;
		width = 5;
		break;
	case 'F':
		buffer[0] = (uns16) 0x0f << 4;
		buffer[1] = (uns16) 0x08 << 4;
		buffer[2] = (uns16) 0x0e << 4;
		buffer[3] = (uns16) 0x08 << 4;
		buffer[4] = (uns16) 0x08 << 4;
		width = 5;
		break;
	case 'G':
		buffer[0] = (uns16) 0x07 << 4;
		buffer[1] = (uns16) 0x08 << 4;
		buffer[2] = (uns16) 0x0b << 4;
		buffer[3] = (uns16) 0x09 << 4;
		buffer[4] = (uns16) 0x06 << 4;
		width = 5;
		break;
	case 'H':
		buffer[0] = (uns16) 0x09 << 4;
		buffer[1] = (uns16) 0x09 << 4;
		buffer[2] = (uns16) 0x0f << 4;
		buffer[3] = (uns16) 0x09 << 4;
		buffer[4] = (uns16) 0x09 << 4;
		width = 5;
		break;
	case 'I':
		buffer[0] = (uns16) 0x01 << 7;
		buffer[1] = (uns16) 0x01 << 7;
		buffer[2] = (uns16) 0x01 << 7;
		buffer[3] = (uns16) 0x01 << 7;
		buffer[4] = (uns16) 0x01 << 7;
		width = 2;
		break;
	case 'J':
		buffer[0] = (uns16) 0x01 << 4;
		buffer[1] = (uns16) 0x01 << 4;
		buffer[2] = (uns16) 0x01 << 4;
		buffer[3] = (uns16) 0x09 << 4;
		buffer[4] = (uns16) 0x06 << 4;
		width = 5;
		break;
	case 'K':
		buffer[0] = (uns16) 0x09 << 4;
		buffer[1] = (uns16) 0x0a << 4;
		buffer[2] = (uns16) 0x0c << 4;
		buffer[3] = (uns16) 0x0a << 4;
		buffer[4] = (uns16) 0x09 << 4;
		width = 5;
		break;
	case 'L':
		buffer[0] = (uns16) 0x08 << 4;
		buffer[1] = (uns16) 0x08 << 4;
		buffer[2] = (uns16) 0x08 << 4;
		buffer[3] = (uns16) 0x08 << 4;
		buffer[4] = (uns16) 0x0f << 4;
		width = 5;
		break;
	case 'M':
		buffer[0] = (uns16) 0x011 << 3;
		buffer[1] = (uns16) 0x01b << 3;
		buffer[2] = (uns16) 0x015 << 3;
		buffer[3] = (uns16) 0x011 << 3;
		buffer[4] = (uns16) 0x011 << 3;
		width = 6;
		break;
	case 'N':
		buffer[0] = (uns16) 0x09 << 4;
		buffer[1] = (uns16) 0x0d << 4;
		buffer[2] = (uns16) 0x0b << 4;
		buffer[3] = (uns16) 0x09 << 4;
		buffer[4] = (uns16) 0x09 << 4;
		width = 5;
		break;
	case 'O':
	case '0':	// zero
		buffer[0] = (uns16) 0x06 << 4;
		buffer[1] = (uns16) 0x09 << 4;
		buffer[2] = (uns16) 0x09 << 4;
		buffer[3] = (uns16) 0x09 << 4;
		buffer[4] = (uns16) 0x06 << 4;
		width = 5;
		break;
	case 'P':
		buffer[0] = (uns16) 0x0e << 4;
		buffer[1] = (uns16) 0x09 << 4;
		buffer[2] = (uns16) 0x0e << 4;
		buffer[3] = (uns16) 0x08 << 4;
		buffer[4] = (uns16) 0x08 << 4;
		width = 5;
		break;
	case 'Q':
		buffer[0] = (uns16) 0x0e << 3;
		buffer[1] = (uns16) 0x11 << 3;
		buffer[2] = (uns16) 0x11 << 3;
		buffer[3] = (uns16) 0x12 << 3;
		buffer[4] = (uns16) 0x0d << 3;
		width = 6;
		break;
	case 'R':
		buffer[0] = (uns16) 0x0e << 4;
		buffer[1] = (uns16) 0x09 << 4;
		buffer[2] = (uns16) 0x0e << 4;
		buffer[3] = (uns16) 0x09 << 4;
		buffer[4] = (uns16) 0x09 << 4;
		width = 5;
		break;
	case 'S':
		buffer[0] = (uns16) 0x07 << 4;
		buffer[1] = (uns16) 0x08 << 4;
		buffer[2] = (uns16) 0x06 << 4;
		buffer[3] = (uns16) 0x01 << 4;
		buffer[4] = (uns16) 0x0e << 4;
		width = 5;
		break;
	case 'T':
		buffer[0] = (uns16) 0x01f << 3;
		buffer[1] = (uns16) 0x04 << 3;
		buffer[2] = (uns16) 0x04 << 3;
		buffer[3] = (uns16) 0x04 << 3;
		buffer[4] = (uns16) 0x04 << 3;
		width = 6;
		break;
	case 'U':
		buffer[0] = (uns16) 0x09 << 4;
		buffer[1] = (uns16) 0x09 << 4;
		buffer[2] = (uns16) 0x09 << 4;
		buffer[3] = (uns16) 0x09 << 4;
		buffer[4] = (uns16) 0x06 << 4;
		width = 5;
		break;
	case 'V':
		buffer[0] = (uns16) 0x011 << 3;
		buffer[1] = (uns16) 0x011 << 3;
		buffer[2] = (uns16) 0x011 << 3;
		buffer[3] = (uns16) 0x0a << 3;
		buffer[4] = (uns16) 0x04 << 3;
		width = 6;
		break;
	case 'W':
		buffer[0] = (uns16) 0x015 << 3;
		buffer[1] = (uns16) 0x015 << 3;
		buffer[2] = (uns16) 0x015 << 3;
		buffer[3] = (uns16) 0x015 << 3;
		buffer[4] = (uns16) 0x00a << 3;
		width = 6;
		break;
	case 'X':
		buffer[0] = (uns16) 0x011 << 3;
		buffer[1] = (uns16) 0x0a << 3;
		buffer[2] = (uns16) 0x04 << 3;
		buffer[3] = (uns16) 0x0a << 3;
		buffer[4] = (uns16) 0x011 << 3;
		width = 6;
		break;
	case 'Y':
		buffer[0] = (uns16) 0x011 << 3;
		buffer[1] = (uns16) 0x0a << 3;
		buffer[2] = (uns16) 0x04 << 3;
		buffer[3] = (uns16) 0x04 << 3;
		buffer[4] = (uns16) 0x04 << 3;
		width = 6;
		break;
	case 'Z':
		buffer[0] = (uns16) 0x0f << 4;
		buffer[1] = (uns16) 0x01 << 4;
		buffer[2] = (uns16) 0x06 << 4;
		buffer[3] = (uns16) 0x08 << 4;
		buffer[4] = (uns16) 0x0f << 4;
		width = 5;
		break;
	case ' ':
		buffer[0] = (uns16) 0x0;
		buffer[1] = (uns16) 0x0;
		buffer[2] = (uns16) 0x0;
		buffer[3] = (uns16) 0x0;
		buffer[4] = (uns16) 0x0;
		width = 4;
		break;
	case '!':
		buffer[0] = (uns16) 0x01 << 7;
		buffer[1] = (uns16) 0x01 << 7;
		buffer[2] = (uns16) 0x01 << 7;
		buffer[3] = (uns16) 0x00 << 7;
		buffer[4] = (uns16) 0x01 << 7;
		width = 4;
		break;
	case '\'':
		buffer[0] = (uns16) 0x01 << 7;
		buffer[1] = (uns16) 0x01 << 7;
		buffer[2] = (uns16) 0x00 << 7;
		buffer[3] = (uns16) 0x00 << 7;
		buffer[4] = (uns16) 0x00 << 7;
		width = 2;
		break;
	case ':':
		buffer[0] = (uns16) 0x00 << 7;
		buffer[1] = (uns16) 0x01 << 7;
		buffer[2] = (uns16) 0x00 << 7;
		buffer[3] = (uns16) 0x01 << 7;
		buffer[4] = (uns16) 0x00 << 7;
		width = 2;
		break;
#ifdef NOTDEF
	case '(':		// old one - too close to next char
		buffer[0] = (uns16) 0x01 << 4;
		buffer[1] = (uns16) 0x02 << 4;
		buffer[2] = (uns16) 0x02 << 4;
		buffer[3] = (uns16) 0x02 << 4;
		buffer[4] = (uns16) 0x01 << 4;
		width = 4;
		break;
#endif
	case '(':
		buffer[0] = (uns16) 0x01 << 5;
		buffer[1] = (uns16) 0x02 << 5;
		buffer[2] = (uns16) 0x02 << 5;
		buffer[3] = (uns16) 0x02 << 5;
		buffer[4] = (uns16) 0x01 << 5;
		width = 4;
		break;
	case ')':
		buffer[0] = (uns16) 0x02 << 6;
		buffer[1] = (uns16) 0x01 << 6;
		buffer[2] = (uns16) 0x01 << 6;
		buffer[3] = (uns16) 0x01 << 6;
		buffer[4] = (uns16) 0x02 << 6;
		width = 4;
		break;
	case ',':
		buffer[0] = (uns16) 0x00 << 6;
		buffer[1] = (uns16) 0x00 << 6;
		buffer[2] = (uns16) 0x00 << 6;
		buffer[3] = (uns16) 0x01 << 6;
		buffer[4] = (uns16) 0x02 << 6;
		width = 3;
		break;
	case '.':		// 0x2e
		buffer[0] = (uns16) 0x00 << 7;
		buffer[1] = (uns16) 0x00 << 7;
		buffer[2] = (uns16) 0x00 << 7;
		buffer[3] = (uns16) 0x00 << 7;
		buffer[4] = (uns16) 0x01 << 7;
		width = 4;
		break;
	case '+':	// new!
		buffer[0] = (uns16) 0x00 << 5;
		buffer[1] = (uns16) 0x02 << 5;
		buffer[2] = (uns16) 0x07 << 5;
		buffer[3] = (uns16) 0x02 << 5;
		buffer[4] = (uns16) 0x00 << 5;
		width = 4;
		break;
	case '=':	// new!
		buffer[0] = (uns16) 0x00 << 5;
		buffer[1] = (uns16) 0x07 << 5;
		buffer[2] = (uns16) 0x00 << 5;
		buffer[3] = (uns16) 0x07 << 5;
		buffer[4] = (uns16) 0x00 << 5;
		width = 4;
		break;
#ifndef OPT_FONTS
	case 0xc9:		// ... (ellipses)
		buffer[0] = (uns16) 0x00 << 3;
		buffer[1] = (uns16) 0x00 << 3;
		buffer[2] = (uns16) 0x00 << 3;
		buffer[3] = (uns16) 0x00 << 3;
		buffer[4] = (uns16) 0x15 << 3;
		width = 6;
		break;
#endif
	case '1':	// 1
		buffer[0] = (uns16) 0x02 << 4;
		buffer[1] = (uns16) 0x06 << 4;
		buffer[2] = (uns16) 0x02 << 4;
		buffer[3] = (uns16) 0x02 << 4;
		buffer[4] = (uns16) 0x07 << 4;
		width = 5;
		break;
	case '2':
		buffer[0] = (uns16) 0x0e << 4;
		buffer[1] = (uns16) 0x01 << 4;
		buffer[2] = (uns16) 0x06 << 4;
		buffer[3] = (uns16) 0x08 << 4;
		buffer[4] = (uns16) 0x0f << 4;
		width = 5;
		break;
	case '3':
		buffer[0] = (uns16) 0x0e << 4;
		buffer[1] = (uns16) 0x01 << 4;
		buffer[2] = (uns16) 0x06 << 4;
		buffer[3] = (uns16) 0x01 << 4;
		buffer[4] = (uns16) 0x0e << 4;
		width = 5;
		break;
	case '4':
		buffer[0] = (uns16) 0x09 << 4;
		buffer[1] = (uns16) 0x09 << 4;
		buffer[2] = (uns16) 0x0f << 4;
		buffer[3] = (uns16) 0x01 << 4;
		buffer[4] = (uns16) 0x01 << 4;
		width = 5;
		break;
	case '5':
		buffer[0] = (uns16) 0x0f << 4;
		buffer[1] = (uns16) 0x08 << 4;
		buffer[2] = (uns16) 0x0e << 4;
		buffer[3] = (uns16) 0x01 << 4;
		buffer[4] = (uns16) 0x0e << 4;
		width = 5;
		break;
	case '6':
		buffer[0] = (uns16) 0x06 << 4;
		buffer[1] = (uns16) 0x08 << 4;
		buffer[2] = (uns16) 0x0e << 4;
		buffer[3] = (uns16) 0x09 << 4;
		buffer[4] = (uns16) 0x06 << 4;
		width = 5;
		break;
	case '7':
		buffer[0] = (uns16) 0x0f << 4;
		buffer[1] = (uns16) 0x01 << 4;
		buffer[2] = (uns16) 0x02 << 4;
		buffer[3] = (uns16) 0x04 << 4;
		buffer[4] = (uns16) 0x08 << 4;
		width = 5;
		break;
	case '8':
		buffer[0] = (uns16) 0x06 << 4;
		buffer[1] = (uns16) 0x09 << 4;
		buffer[2] = (uns16) 0x06 << 4;
		buffer[3] = (uns16) 0x09 << 4;
		buffer[4] = (uns16) 0x06 << 4;
		width = 5;
		break;
	case '9':
		buffer[0] = (uns16) 0x06 << 4;
		buffer[1] = (uns16) 0x09 << 4;
		buffer[2] = (uns16) 0x07 << 4;
		buffer[3] = (uns16) 0x01 << 4;
		buffer[4] = (uns16) 0x06 << 4;
		width = 5;
		break;
	case '?':
		buffer[0] = (uns16) 0x0e << 4;
		buffer[1] = (uns16) 0x01 << 4;
		buffer[2] = (uns16) 0x06 << 4;
		buffer[3] = (uns16) 0x00 << 4;
		buffer[4] = (uns16) 0x04 << 4;
		width = 5;
		break;
#ifndef OPT_FONTS
	case 0xF0:		// XXX	(heart - normally apple logo)
		buffer[0] = (uns16) 0x36 << 1;
		buffer[1] = (uns16) 0x49 << 1;
		buffer[2] = (uns16) 0x22 << 1;
		buffer[3] = (uns16) 0x14 << 1;
		buffer[4] = (uns16) 0x08 << 1;
		width = 8;
		break;
#ifdef NOTDEF
	// optional char
	case 0xF1:		// XXX	(filled heart)
		buffer[0] = (uns16) 0x36 << 1;
		buffer[1] = (uns16) 0x7f << 1;
		buffer[2] = (uns16) 0x3e << 1;
		buffer[3] = (uns16) 0x14 << 1;
		buffer[4] = (uns16) 0x08 << 1;
		width = 8;
		break;
#endif
#endif
#ifdef NOTDEF
	case 0xF2:		// up arrow
		buffer[0] = (uns16) 0x36 << 1;
		buffer[1] = (uns16) 0x49 << 1;
		buffer[2] = (uns16) 0x22 << 1;
		buffer[3] = (uns16) 0x14 << 1;
		buffer[4] = (uns16) 0x08 << 1;
		width = 8;
		break;
#endif
	default:	// badchar
#ifndef OPT_FONTS
		buffer[0] = (uns16) 0x15 << 3;
		buffer[1] = (uns16) 0x0a << 3;
		buffer[2] = (uns16) 0x15 << 3;
		buffer[3] = (uns16) 0x0a << 3;
		buffer[4] = (uns16) 0x15 << 3;
		width = 6;
#endif
		break;
	}
    
    *fontWidth = width;
}
