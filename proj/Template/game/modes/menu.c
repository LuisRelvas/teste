#include "menu.h"
#include "lcom/vbe.h"
#include "../game.h"
#include "../../view/view.h"

extern stuct packet mouseP;

extern bool gameRunning;
extern int gameMode; 

extern int gameplayCounter; 
extern Sprite *quitButton;
extern uint8_t *imgBuffer; 
extern uint8_t *drawBuffer; 
extern uint16_t xRes, yRes;
extern unsigned bytesPerPixel;

bool quitPressed = false;



int process_quit_button(uint16_t x , uint16_t y) 
{ 
    if(x > 450 && x < 650 && y > 420 && y < 520) 
    {
        if(!quitPresssed) 
            if(mouseP.lb)
                quitPressed = true;
        if(quitPressed) 
            if(!mouseP.lb) 
                gameRunning = false; 
                quitPressed = false; 
    }
    else quitPressed = false; 
    return 0;

}

int drawMenu() 
{
    memset(imgBuffer,0xDDDDDD,xRes*yRes*bytesPerPixel);
    if(quitPressed) draw_sprite_button(quitButtonPressed,450,420);
    else (quitButton,450,420);
    return 0;

}