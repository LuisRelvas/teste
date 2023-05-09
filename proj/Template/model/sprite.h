#ifndef _LCOM_SPRITE_H_
#define _LCOM_SPRITE_H_

#include "controller/video/graphics.h"
#include "../model/xpm/buttons/quitButton.xpm"
#include "../model/xpm/buttons/quitButtonPressed.xpm"


typedef struct {
    uint16_t height;
    uint16_t width;
    uint32_t *colors;
    uint32_t color;
    uint8_t pressed;
    int id ;
} Sprite; 


Sprite *create_sprite_xpm(xpm_map_t sprite);
Sprite *create_sprite_button(uint16_t width, uint16_t height, uint32_t color);
void destroy_sprite(Sprite *sprite);

#endif
