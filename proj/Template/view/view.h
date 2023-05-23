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
#include "game/modes/mode_1.h"
#include "game/modes/mode_2.h"
#include "game/modes/mode_3.h"

Sprite **alloc_matrix(int n, int m);
void draw_new_frame();
bool check_match(int id1, int id2);
void draw_initial_menu();
void draw_game_menu_2();
void draw_game_menu();
void draw_finish_menu();
void draw_mouse();
void swap_buffers();
void display_real_time();
int draw_sprite_xpm(Sprite *sprite, int x, int y);
int draw_sprite_button(Sprite *sprite, int x, int y);
int set_frame_buffers(uint16_t mode);
void draw_xpm_draw_buffer(xpm_map_t xpm, uint16_t x, uint16_t y);
int get_number(Sprite *cards, int size);
void draw_game_menu_3();
void shuffle(Sprite *cards, int size);
void shuffle2(Sprite *cards);
void shuffle3(Sprite *cards);
void draw_mode_menu();
void draw_game_menu_game_2();
void draw_game_menu_game_4();
void draw_game_menu_game_3();
void draw_card_animation(uint16_t x, uint16_t y);
void animation_trigger();

#endif
