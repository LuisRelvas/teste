#include "view/view.h"
#include "menu.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



// Variáveis externas importantes à visualização do modelo e dos seus estados
void draw_game_menu();
void process_button1(Sprite *cards,int size);
void process_button2(Sprite *cards,int size);
void process_button3(Sprite *cards,int size);
void process_button4(Sprite *cards,int size);
void shuffle(Sprite *cards,int size);
bool check_match(int id1, int id2);
Sprite **alloc_matrix(int n,int m);


