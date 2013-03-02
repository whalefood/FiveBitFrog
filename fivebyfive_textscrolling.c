

#include "fivebyfive_textscrolling.h"

void drawFromDisplayBuffer(uint8_t *display);

// scrolls text accross the screen
// speed: adjusts scrolling speed (higher number == slower, 35-40 seems about right)
// repeat: 1 to repeat scrolling.  0 to display text once
void fivebyfivetext_scrolltext(char* text, uint8_t speed, textscrolloption option)
{

	// now, start the text scrolling...

	uint8_t charDataWidth = 0;
    uint16_t charDataBuffer[5];
    uint8_t Disp[5];
	uint8_t chrCntr = 0;
	uint8_t buttondown = 0;
    

	while (1)  {  /* infinite loop */

        //grab next character
        char chrToDisp = text[chrCntr];
        if(!chrToDisp)
        {
            if(option ==  textscrollonce)
                return;
            chrCntr = 0;
            chrToDisp = text[chrCntr];
        }
        chrCntr++;

		//load char data and display
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

				if(option == textscrolluntilbutton)
                {
                    if(buttonispressed())
                    {
                        buttondown = 1;
                    }
                    else if(buttondown)
                    {
                        return;
                    }
                }

				drawFrame(Disp);  // "refresh" LEDs
			}

		}
	}
}

