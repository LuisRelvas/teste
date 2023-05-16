#ifndef _LCOM_MODEL_H_
#define _LCOM_MODEL_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "controller/keyboard/KBC.h"
#include "controller/mouse/mouse.h"
#include "controller/video/graphics.h"
#include "controller/rtc/rtc.h"
#include "xpm/hand.xpm"
#include "xpm/mouse.xpm"
#include "xpm/smile.xpm"
#include "xpm/teste.xpm"
#include "xpm/logo.xpm"
#include "view/view.h"
#include "model/sprite.h"
#include "config.h"
#include "xpm/back.xpm"
#include "xpm/game.xpm"
#include "xpm/number1.xpm"
#include "xpm/number2.xpm"
#include "xpm/number3.xpm"
#include "xpm/number4.xpm"
#include "xpm/number5.xpm"
#include "xpm/number6.xpm"
#include "xpm/number7.xpm"
#include "xpm/number8.xpm"
#include "xpm/start.xpm"
#include "xpm/hard.xpm"
#include "xpm/easy.xpm"
#include "xpm/medium.xpm"
#include "xpm/quit.xpm"



typedef enum {
    RUNNING,
    EXIT,
} SystemState;

typedef enum {
    START,
    GAME,
    GAME_2,
    END,
    MODE,
    GAME_3
} MenuState;

void update_timer_state();
void update_keyboard_state();
void update_mouse_state();
void update_buttons_state();
void update_rtc_state();
void setup_sprites();
void destroy_sprites();

#endif
