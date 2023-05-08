#ifndef __MENU_H
#define __MENU_H

#include "../../controller/video/VBE.h"
#include "../../controller/video/graphics.h"
#include "../../controller/mouse/mouse.h"

int drawMenu();
int process_quit_button(uint16_t x , uint16_t y);

#endif
