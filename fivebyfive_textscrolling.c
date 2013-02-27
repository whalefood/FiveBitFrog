

#include "fivebyfive_textscrolling.h"

void drawFromDisplayBuffer(uint8_t *display);

// scrolls text accross the screen
// speed: adjusts scrolling speed (higher number == slower, 35-40 seems about right)
// repeat: 1 to repeat scrolling.  0 to display text once
void fivebyfivetext_scrolltext(char* text, uint8_t speed, uint8_t repeat)
{

	// now, start the text scrolling...

	uint8_t charDataWidth = 0;
    uint16_t charDataBuffer[5];
    uint8_t Disp[5];
	uint8_t chrCntr = 0;

    
    /* button press vars
     
	uint8_t buttonevent = 0;
	uint8_t prevbuttonpress = 0;
	uint8_t buttonpress;

	uint8_t msgnum = 0;		// this is "toggled" by a button press

*/
    

	while (1)  {  /* infinite loop */

        //grab next character
        char chrToDisp = text[chrCntr];
        if(!chrToDisp)
        {
            if(!repeat)
                break;
            chrCntr = 0;
            chrToDisp = text[chrCntr];
        }
        chrCntr++;

		//load char data and display
		uint8_t charDataWidth;
		loadfontcharintobuffer(chrToDisp, charDataBuffer, &charDataWidth);
        
		for (uint8_t col = 0; col < charDataWidth; col++) {		// do "width" times...
			for (uint8_t row = 0; row < 5; row++) {			// for each row of the display...

				Disp[row] <<= 1;
				if (charDataBuffer[row] & 0x80) {
					Disp[row]++;
				}
                
				charDataBuffer[row] <<=1;
			}


			for (uint8_t cntr = 0; cntr < speed; cntr++) {

				// catch button press "event" (also use Refresh as a "delay")
				/*if (FLineEnabled) {
					if (input_test(F_LINE) == 0) {
						buttonpress = 1;
					} else {
						buttonpress = 0;
					}
					if (!prevbuttonpress && buttonpress) {		// detect transition from unpressed to pressed
						buttonevent = 1;						// and set event flag
					}
					prevbuttonpress = buttonpress;
				}*/

				drawFrame(Disp);  // "refresh" LEDs
			}

		}
	}
}

