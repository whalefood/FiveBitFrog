
#include "fivebyfive.h"
#include "fivebyfive_textscrolling.h"

int main()
{
    fivebyfive_init();
    char text[]  = "START!  ";
    
    uint8_t frame[5] = {0x11,0x0A,0x04,0x0A,0x11};
    // uint8_t frame[5] = {0x1f,0x1f,0x1f,0x1f,0x1f};
    //uint8_t frame[5] = {0x00,0x0A,0x0,0x0,0x0};
  /*  while(1)
    {
        drawFrame(frame);
    }*/
        
    
    fivebyfivetext_scrolltext(text, 35, textscrollrepeat);
}