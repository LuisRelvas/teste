#include "menu.h"
#include "lcom/vbe.h"
#include "../game.h"
#include "../../view/view.h"


extern bool gameRunning;
extern int gameMode; 

extern int gameplayCounter; 
extern Sprite *quitButton;
extern uint8_t *imgBuffer; 
extern uint8_t *drawBuffer; 
extern uint16_t xRes, yRes;
extern unsigned bytesPerPixel;

bool quitPressed = false;

