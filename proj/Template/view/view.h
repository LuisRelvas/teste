#ifndef _LCOM_MENU_H_
#define _LCOM_MENU_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "config.h"
#include "controller/video/graphics.h"
#include "controller/mouse/mouse.h"
#include "controller/rtc/rtc.h"
#include "model/sprite.h"
#include "model/model.h"

void draw_new_frame();
void draw_initial_menu();
void draw_game_menu();
void draw_finish_menu();
void draw_game_menu_2();
void draw_mouse();
void swap_buffers();
void display_real_time();
int draw_sprite_xpm(Sprite *sprite, int x, int y);
int draw_sprite_button(Sprite *sprite, int x, int y);
int set_frame_buffers(uint16_t mode);
void draw_xpm_draw_buffer(xpm_map_t xpm, uint16_t x, uint16_t y) ;
int get_number(Sprite *cards,int size);
void process_button2(Sprite *cards,int size);
void process_button1(Sprite *cards,int size);
void process_button3(Sprite *cards,int size);
void process_button4(Sprite *cards,int size);
void shuffle(Sprite *cards, int size);
void shuffle2(Sprite *cards);
void process_cardPressed1();
void process_cardPressed2();
void process_cardPressed3();
void process_cardPressed4();
void process_cardPressed5();
void process_cardPressed6();
void process_cardPressed7();
void process_cardPressed8();
void draw_mode_menu();
void draw_game_menu_3();
void draw_game_menu_game_2();

#endif
