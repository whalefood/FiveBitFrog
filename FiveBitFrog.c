//
//  FiveBitFrog.c
//  FiveBitFrog
//
//  Created by Jonah Wallerstein on 2/27/13.
//

#include "fivebyfive.h" 
#include   <stdlib.h>

//buffer for frame
uint8_t frameBuffer[5] = {0};

//player position
uint8_t playerPos = 0;

//cars
typedef struct {
    uint8_t speed,
    uint8_t direction
} Car;

enum {
    button_down,
    button_up
} buttonState;

void fivebitfrog_start(uint8_t speed,uint8_t carFreqency)
{
    playerPos = 0;
    
    uint32_t timer = 0
    
    buttonState = up;
    
    while(1)
    {
        timer++;
        
        
        
        moveCar();
        checkCollitions();
        renderFrame();
        
        drawFrame(frameBuffer);
        
        //check input
        if(buttonispress())
        {
            if(buttonState == button_up)
            {
                buttonState = button_down;
                playerPos ++;
            }
        }
        else
            buttonState = button_up;
    }
    
}



void moveCar(Car car)
{
    
}