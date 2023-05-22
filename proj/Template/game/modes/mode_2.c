#include "mode_2.h"


bool cardPressed1 = false;
bool cardPressed2 = false;
bool cardPressed3 = false;
bool cardPressed4 = false;
bool cardPressed5 = false;
bool cardPressed6 = false;
bool cardPressed7 = false;
bool cardPressed8 = false;
bool cardBlock1 = false;
bool cardBlock2 = false;
bool cardBlock3 = false;
bool cardBlock4 = false;
bool cardBlock5 = false;
bool cardBlock6 = false;
bool cardBlock7 = false;
bool cardBlock8 = false;
extern Sprite *mouse;
extern Sprite *hand;
extern Sprite *smile;
extern Sprite *teste;
extern Sprite *logo;
extern Sprite *quitButton;
extern Sprite *quitButtonPressed;
extern Sprite *button1;
extern Sprite *button2;
extern Sprite *button3;
extern Sprite *button4;
extern Sprite *number1;
extern Sprite *number2;
extern Sprite *number3;
extern Sprite *number4;
extern Sprite *number5;
extern Sprite *number6;
extern Sprite *number7;
extern Sprite *number8;
extern Sprite *back;
extern Sprite *game;
extern Sprite *easy;
extern Sprite *medium;
extern Sprite *hard;
extern Sprite *quit;
extern Sprite *start;
int pre1 = 0;
Sprite **matrix;
Sprite *index_1;
Sprite *index_2;
bool *index_1_bool;
bool *index_2_bool;
int matrix_id1 = -1; 
int matrix_id2 = -1;



bool check_match(int id1, int id2)
{
    if (id1 == id2)
    {
        return true;
    }
    else
    {
        return false;
    }
}


Sprite **alloc_matrix(int n,int m) 
{ 
    Sprite **mat = (Sprite**)malloc(sizeof(Sprite*)*m);
    for(int i = 0; i < n; i++) { 
        mat[i] = (Sprite*)malloc(sizeof(Sprite)*n);
    }
    return mat; 
}

void shuffle2(Sprite *cards)
{
    int size = 8;

    srand(time(NULL));
    for (int i = size - 1; i >= 0; i--)
    {
        int j = rand() % (i + 1);
        Sprite temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
    matrix[0][0] = cards[0];
    matrix[0][1] = cards[1];
    matrix[0][2] = cards[2];
    matrix[0][3] = cards[3];
    matrix[1][0] = cards[4];
    matrix[1][1] = cards[5];
    matrix[1][2] = cards[6];
    matrix[1][3] = cards[7];

    // Printing the shuffled matrix
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", matrix[i][j].id);
        }
        printf("\n");
    }
}


void process_cardPressed1()
{
    if (mouse_info.x >= 0 && mouse_info.y >= 0 && mouse_info.x <= mode_info.XResolution / 4 && mouse_info.y <= mode_info.YResolution / 2)
    {
        if (mouse_info.left_click)
        {
            cardPressed1 = true;
        }
    }
        if (cardPressed1)
    {
        draw_sprite_xpm(&matrix[0][0], 0, 0);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[0][0].id;
            index_1_bool = &cardPressed1;
            index_1 = &matrix[0][0];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[0][0]) {
            matrix_id2 = matrix[0][0].id;
            index_2_bool = &cardPressed1;
            index_2 = &matrix[0][0];
            printf("The value of index_2 on button1 is %d\n",index_2);
            printf("The value of matrix_id2 on button1 is %d",matrix_id2);
         }
        if(matrix_id1 != -1 && matrix_id2 != -1) {
        if (check_match(matrix_id1,matrix_id2)){
        index_1->block = true;
        index_2->block = true;
        } 
        else if(!check_match(matrix_id1,matrix_id2)) { 
            *index_2_bool = false; 
            *index_1_bool = false; 
            printf("The value of the cardPressed1 is %d",cardPressed1);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
        
    }
        
}
void process_cardPressed2()
{
    if (mouse_info.x >= mode_info.XResolution / 4 && mouse_info.y >= 0 && mouse_info.x <= mode_info.XResolution / 2 && mouse_info.y <= mode_info.YResolution / 2)
    {
        if (mouse_info.left_click)
        {
            cardPressed2 = true;
        }
    }
    if (cardPressed2)
    {

        draw_sprite_xpm(&matrix[0][1], mode_info.XResolution / 4 , 0);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[0][1].id;
            index_1_bool = &cardPressed2;
            index_1 = &matrix[0][1];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[0][1]) {
            matrix_id2 = matrix[0][1].id;
            index_2_bool = &cardPressed2;
            index_2 = &matrix[0][1];
            printf("The value of index_2 on button1 is %d\n",index_2);
            printf("The value of matrix_id2 on button1 is %d",matrix_id2);
         }
        if(matrix_id1 != -1 && matrix_id2 != -1) {
        if (check_match(matrix_id1,matrix_id2)){
        index_1->block = true;
        index_2->block = true;
        } 
        else if(!check_match(matrix_id1,matrix_id2)) { 
            *index_2_bool = false; 
            *index_1_bool = false; 
            printf("The value of the cardPressed2 is %d",cardPressed2);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }

}

void process_cardPressed3()
{
    if (mouse_info.x >= mode_info.XResolution / 2 && mouse_info.y >= 0 && mouse_info.x <= 3 * mode_info.XResolution / 4 && mouse_info.y <= mode_info.YResolution / 2)
    {
        if (mouse_info.left_click)
        {
            cardPressed3 = true;
        }
    }
    if (cardPressed3)
    {

        draw_sprite_xpm(&matrix[0][2], mode_info.XResolution / 2, 0);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[0][2].id;
            index_1_bool = &cardPressed3;
            index_1 = &matrix[0][2];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[0][2]) {
            matrix_id2 = matrix[0][2].id;
            index_2_bool = &cardPressed3;
            index_2 = &matrix[0][2];
            printf("The value of index_2 on button1 is %d\n",index_2);
            printf("The value of matrix_id2 on button1 is %d",matrix_id2);
         }
        if(matrix_id1 != -1 && matrix_id2 != -1) {
        if (check_match(matrix_id1,matrix_id2)){
        index_1->block = true;
        index_2->block = true;
        } 
        else if(!check_match(matrix_id1,matrix_id2)) { 
            *index_2_bool = false; 
            *index_1_bool = false; 
            printf("The value of the cardPressed3 is %d",cardPressed3);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}

void process_cardPressed4()
{
    if (mouse_info.x >= 3 * mode_info.XResolution / 4 && mouse_info.y >= 0 && mouse_info.x <= mode_info.XResolution && mouse_info.y <= mode_info.YResolution / 2)
    {
        if (mouse_info.left_click)
        {
            cardPressed4 = true;
        }
    }
    if (cardPressed4)
    {
        draw_sprite_xpm(&matrix[0][3], 3 * mode_info.XResolution / 4, 0);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[0][3].id;
            index_1_bool = &cardPressed4;
            index_1 = &matrix[0][3];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[0][3]) {
            matrix_id2 = matrix[0][3].id;
            index_2_bool = &cardPressed4;
            index_2 = &matrix[0][3];
            printf("The value of index_2 on button1 is %d\n",index_2);
            printf("The value of matrix_id2 on button1 is %d",matrix_id2);
         }
        if(matrix_id1 != -1 && matrix_id2 != -1) {
        if (check_match(matrix_id1,matrix_id2)){
        index_1->block = true;
        index_2->block = true;
        } 
        else if(!check_match(matrix_id1,matrix_id2)) { 
            *index_2_bool = false; 
            *index_1_bool = false; 
            printf("The value of the cardPressed4 is %d",cardPressed4);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}

void process_cardPressed5()
{
    if (mouse_info.x >= 0 && mouse_info.y >= mode_info.YResolution / 2 && mouse_info.x <= mode_info.XResolution / 4 && mouse_info.y <= mode_info.YResolution)
    {
        if (mouse_info.left_click)
        {
            cardPressed5 = true;
        }
    }
    if (cardPressed5)
    {
        draw_sprite_xpm(&matrix[1][0], 0, mode_info.YResolution / 2);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[1][0].id;
            index_1_bool = &cardPressed5;
            index_1 = &matrix[1][0];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[1][0]) {
            matrix_id2 = matrix[1][0].id;
            index_2_bool = &cardPressed5;
            index_2 = &matrix[1][0];
            printf("The value of index_2 on button1 is %d\n",index_2);
            printf("The value of matrix_id2 on button1 is %d",matrix_id2);
         }
        if(matrix_id1 != -1 && matrix_id2 != -1) {
        if (check_match(matrix_id1,matrix_id2)){
        index_1->block = true;
        index_2->block = true;
        } 
        else if(!check_match(matrix_id1,matrix_id2)) { 
            *index_2_bool = false; 
            *index_1_bool = false; 
            printf("The value of the cardPressed5 is %d",cardPressed5);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}

void process_cardPressed6()
{
    if (mouse_info.x >= mode_info.XResolution / 4 && mouse_info.y >= mode_info.YResolution / 2 && mouse_info.x <= mode_info.XResolution / 2 && mouse_info.y <= mode_info.YResolution)
    {
        if (mouse_info.left_click)
        {
            cardPressed6 = true;
        }
    }
    if (cardPressed6)
    {
        draw_sprite_xpm(&matrix[1][1], mode_info.XResolution / 4, mode_info.YResolution / 2);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[1][1].id;
            index_1_bool = &cardPressed6;
            index_1 = &matrix[1][1];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[1][1]) {
            matrix_id2 = matrix[1][1].id;
            index_2_bool = &cardPressed6;
            index_2 = &matrix[1][1];
            printf("The value of index_2 on button1 is %d\n",index_2);
            printf("The value of matrix_id2 on button1 is %d",matrix_id2);
         }
        if(matrix_id1 != -1 && matrix_id2 != -1) {
        if (check_match(matrix_id1,matrix_id2)){
        index_1->block = true;
        index_2->block = true;
        } 
        else if(!check_match(matrix_id1,matrix_id2)) { 
            *index_2_bool = false; 
            *index_1_bool = false; 
            printf("The value of the cardPressed6 is %d",cardPressed6);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}

void process_cardPressed7()
{
    if (mouse_info.x >= mode_info.XResolution / 2 && mouse_info.y >= mode_info.YResolution / 2 && mouse_info.x <= 3 * mode_info.XResolution / 4 && mouse_info.y <= mode_info.YResolution)
    {
        if (mouse_info.left_click)
        {
            cardPressed7 = true;
        }
    }
    if (cardPressed7)
    {
        draw_sprite_xpm(&matrix[1][2], mode_info.XResolution / 2, mode_info.YResolution / 2);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[1][2].id;
            index_1_bool = &cardPressed7;
            index_1 = &matrix[1][2];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[1][2]) {
            matrix_id2 = matrix[1][2].id;
            index_2_bool = &cardPressed7;
            index_2 = &matrix[1][2];
            printf("The value of index_2 on button1 is %d\n",index_2);
            printf("The value of matrix_id2 on button1 is %d",matrix_id2);
         }
        if(matrix_id1 != -1 && matrix_id2 != -1) {
        if (check_match(matrix_id1,matrix_id2)){
        index_1->block = true;
        index_2->block = true;
        } 
        else if(!check_match(matrix_id1,matrix_id2)) { 
            *index_2_bool = false; 
            *index_1_bool = false; 
            printf("The value of the cardPressed7 is %d",cardPressed7);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
    }
}
}

void process_cardPressed8()
{
    if (mouse_info.x >= 3 * mode_info.XResolution / 4 && mouse_info.y >= mode_info.YResolution / 2 && mouse_info.x <= mode_info.XResolution && mouse_info.y <= mode_info.YResolution)
    {
        if (mouse_info.left_click)
        {
            cardPressed8 = true;
        }
    }
    if (cardPressed8)
    {
        draw_sprite_xpm(&matrix[1][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 2);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[1][3].id;
            index_1_bool = &cardPressed8;
            index_1 = &matrix[1][3];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[1][3]) {
            matrix_id2 = matrix[1][3].id;
            index_2_bool = &cardPressed8;
            index_2 = &matrix[1][3];
            printf("The value of index_2 on button1 is %d\n",index_2);
            printf("The value of matrix_id2 on button1 is %d",matrix_id2);
         }
        if(matrix_id1 != -1 && matrix_id2 != -1) {
        if (check_match(matrix_id1,matrix_id2)){
        index_1->block = true;
        index_2->block = true;
        } 
        else if(!check_match(matrix_id1,matrix_id2)) { 
            *index_2_bool = false; 
            *index_1_bool = false; 
            printf("The value of the cardPressed8 is %d",cardPressed8);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}

void draw_game_menu_2()
{
    Sprite *back1 = back;
    Sprite *back2 = back;
    Sprite *back3 = back;
    Sprite *back4 = back;
    Sprite *back5 = back;
    Sprite *back6 = back;
    Sprite *back7 = back;
    Sprite *back8 = back;
    Sprite cards2[] = {*number1, *number1, *number2, *number2, *number3, *number3, *number4, *number4};
    if (pre1 == 0)
    {
        matrix = alloc_matrix(4,2);
        shuffle2(cards2);
        pre1++;
    }

    memset(drawing_frame_buffer, 0, mode_info.XResolution * mode_info.YResolution * mode_info.BitsPerPixel / 8);
    draw_sprite_xpm(back1, 0, 0);
    draw_sprite_xpm(back2, mode_info.XResolution / 4, 0);
    draw_sprite_xpm(back3, mode_info.XResolution / 2, 0);
    draw_sprite_xpm(back4, 3 * mode_info.XResolution / 4, 0);
    draw_sprite_xpm(back5, 0, mode_info.YResolution / 2);
    draw_sprite_xpm(back6, mode_info.XResolution / 4, mode_info.YResolution / 2);
    draw_sprite_xpm(back7, mode_info.XResolution / 2, mode_info.YResolution / 2);
    draw_sprite_xpm(back8, 3 * mode_info.XResolution / 4, mode_info.YResolution / 2);
    if (matrix[0][0].block == false)
    {
        process_cardPressed1();
    }
    else if (matrix[0][0].block == true)
    {
        draw_sprite_xpm(&matrix[0][0], 0, 0);
    }
    if (matrix[0][1].block== false)
    {
        process_cardPressed2();
    }
    else if (matrix[0][1].block == true)
    {
        draw_sprite_xpm(&matrix[0][1], mode_info.XResolution / 4, 0);
    }
    if (matrix[0][2].block == false)
    {
        process_cardPressed3();
    }
    else if (matrix[0][2].block == true)
    {
        draw_sprite_xpm(&matrix[0][2], mode_info.XResolution / 2, 0);
    }
    if (matrix[0][3].block == false)
    {
        process_cardPressed4();
    }
    else if (matrix[0][3].block == true)
    {
        draw_sprite_xpm(&matrix[0][3], 3 * mode_info.XResolution / 4, 0);
    }
    if (matrix[1][0].block == false)
    {
        process_cardPressed5();
    }
    else if (matrix[1][0].block == true)
    {
        draw_sprite_xpm(&matrix[1][0], 0, mode_info.YResolution / 2);
    }
    if (matrix[1][1].block == false)
    {
        process_cardPressed6();
    }
    else if (matrix[1][1].block == true)
    {
        draw_sprite_xpm(&matrix[1][1], mode_info.XResolution / 4, mode_info.YResolution / 2);
    }
    if (matrix[1][2].block== false)
    {
        process_cardPressed7();
    }
    else if (matrix[1][2].block == true)
    {
        draw_sprite_xpm(&matrix[1][2], mode_info.XResolution / 2, mode_info.YResolution / 2);
    }
    if (matrix[1][3].block == false)
    {
        process_cardPressed8();
    }
    else if (matrix[1][3].block == true)
    {
        draw_sprite_xpm(&matrix[1][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 2);
    }
    if (matrix[0][0].block == true && matrix[0][1].block == true && matrix[0][2].block == true && matrix[0][3].block == true && matrix[1][0].block == true && matrix[1][1].block == true && matrix[1][2].block == true && matrix[1][3].block == true){
        draw_finish_menu();
        menuState = END;
    }

}