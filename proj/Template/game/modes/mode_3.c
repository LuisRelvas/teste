#include "mode_3.h"



extern uint8_t scancode;
extern uint8_t byte_index;
SystemState systemState = RUNNING;
MenuState menuState = START;
extern MouseInfo mouse_info;
extern vbe_mode_info_t mode_info;
extern real_time_info time_info;
Sprite **matrix;
int pre2 = 0;
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
bool backPressed1 = false;
bool backPressed2 = false;
bool backPressed3 = false;
bool backPressed4 = false;
bool backPressed5 = false;
bool backPressed6 = false;
bool backPressed7 = false;
bool backPressed8 = false;
bool backPressed9 = false;
bool backPressed10 = false;
bool backPressed11 = false;
bool backPressed12 = false;
bool backPressed13 = false;
bool backPressed14 = false;
bool backPressed15 = false;
bool backPressed16 = false;
bool backBlock1 = false;
bool backBlock2 = false;
bool backBlock3 = false;
bool backBlock4 = false;
bool backBlock5 = false;
bool backBlock6 = false;
bool backBlock7 = false;
bool backBlock8 = false;
bool backBlock9 = false;
bool backBlock10 = false;
bool backBlock11 = false;
bool backBlock12 = false;
bool backBlock13 = false;
bool backBlock14 = false;
bool backBlock15 = false;
bool backBlock16 = false;
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

void shuffle3(Sprite *cards)
{
    int size = 16;

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
    matrix[2][0] = cards[8];
    matrix[2][1] = cards[9];
    matrix[2][2] = cards[10];
    matrix[2][3] = cards[11];
    matrix[3][0] = cards[12];
    matrix[3][1] = cards[13];
    matrix[3][2] = cards[14];
    matrix[3][3] = cards[15];

    // Printing the shuffled matrix
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", matrix[i][j].id);
        }
        printf("\n");
    }
}

void process_deck1()
{
    if (mouse_info.x > 0 && mouse_info.x < mode_info.XResolution / 4 && mouse_info.y > 0 && mouse_info.y < mode_info.YResolution / 4)
    {
        if (mouse_info.left_click)
        {
            backPressed1 = true;
        }
    }
    if (backPressed1)
    {
        draw_sprite_xpm(&matrix[0][0], 0, 0);
       printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[0][0].id;
            index_1_bool = &backPressed1;
            index_1 = &matrix[0][0];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[0][0]) {
            matrix_id2 = matrix[0][0].id;
            index_2_bool = &backPressed1;
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
            printf("The value of the backPressed1 is %d",backPressed1);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        
        }
    }
}
void process_deck2()
{
    if (mouse_info.x > mode_info.XResolution / 4 && mouse_info.x < mode_info.XResolution / 2 && mouse_info.y > 0 && mouse_info.y < mode_info.YResolution / 4)
    {
        if (mouse_info.left_click)
        {
            backPressed2 = true;
        }
    }
    if (backPressed2)
    {
        draw_sprite_xpm(&matrix[0][1], mode_info.XResolution / 4, 0);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[0][1].id;
            index_1_bool = &backPressed2;
            index_1 = &matrix[0][1];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[0][1]) {
            matrix_id2 = matrix[0][1].id;
            index_2_bool = &backPressed2;
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
            printf("The value of the backPressed2 is %d",backPressed2);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}
void process_deck3()
{
    if (mouse_info.x > mode_info.XResolution / 2 && mouse_info.x < 3 * mode_info.XResolution / 4 && mouse_info.y > 0 && mouse_info.y < mode_info.YResolution / 4)
    {
        if (mouse_info.left_click)
        {
            backPressed3 = true;
        }
    }
    if (backPressed3)
    {
        draw_sprite_xpm(&matrix[0][2], mode_info.XResolution / 2, 0);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[0][2].id;
            index_1_bool = &backPressed3;
            index_1 = &matrix[0][2];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[0][2]) {
            matrix_id2 = matrix[0][2].id;
            index_2_bool = &backPressed3;
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
            printf("The value of the backPressed3 is %d",backPressed3);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}
void process_deck4()
{
    if (mouse_info.x > 3 * mode_info.XResolution / 4 && mouse_info.x < mode_info.XResolution && mouse_info.y > 0 && mouse_info.y < mode_info.YResolution / 4)
    {
        if (mouse_info.left_click)
        {
            backPressed4 = true;
        }
    }
    if (backPressed4)
    {
        draw_sprite_xpm(&matrix[0][3], 3 * mode_info.XResolution / 4, 0);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[0][3].id;
            index_1_bool = &backPressed4;
            index_1 = &matrix[0][3];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[0][3]) {
            matrix_id2 = matrix[0][3].id;
            index_2_bool = &backPressed4;
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
            printf("The value of the backPressed4 is %d",backPressed4);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}
void process_deck5()
{
    if (mouse_info.x > 0 && mouse_info.x < mode_info.XResolution / 4 && mouse_info.y > mode_info.YResolution / 4 && mouse_info.y < mode_info.YResolution / 2)
    {
        if (mouse_info.left_click)
        {
            backPressed5 = true;
        }
    }
    if (backPressed5)
    {
        draw_sprite_xpm(&matrix[1][0], 0, mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[1][0].id;
            index_1_bool = &backPressed5;
            index_1 = &matrix[1][0];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[1][0]) {
            matrix_id2 = matrix[1][0].id;
            index_2_bool = &backPressed5;
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
            printf("The value of the backPressed5 is %d",backPressed5);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}
void process_deck6()
{
    if (mouse_info.x > mode_info.XResolution / 4 && mouse_info.x < mode_info.XResolution / 2 && mouse_info.y > mode_info.YResolution / 4 && mouse_info.y < mode_info.YResolution / 2)
    {
        if (mouse_info.left_click)
        {
            backPressed6 = true;
        }
    }
    if (backPressed6)
    {
        draw_sprite_xpm(&matrix[1][1], mode_info.XResolution / 4, mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[1][1].id;
            index_1_bool = &backPressed6;
            index_1 = &matrix[1][1];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[1][1]) {
            matrix_id2 = matrix[1][1].id;
            index_2_bool = &backPressed6;
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
            printf("The value of the backPressed6 is %d",backPressed6);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}
void process_deck7()
{
    if (mouse_info.x > mode_info.XResolution / 2 && mouse_info.x < 3 * mode_info.XResolution / 4 && mouse_info.y > mode_info.YResolution / 4 && mouse_info.y < mode_info.YResolution / 2)
    {
        if (mouse_info.left_click)
        {
            backPressed7 = true;
        }
    }
    if (backPressed7)
    {
        draw_sprite_xpm(&matrix[1][2], mode_info.XResolution / 2, mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[1][2].id;
            index_1_bool = &backPressed7;
            index_1 = &matrix[1][2];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[1][2]) {
            matrix_id2 = matrix[1][2].id;
            index_2_bool = &backPressed7;
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
            printf("The value of the backPressed7 is %d",backPressed7);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}
void process_deck8()
{
    if (mouse_info.x > 3 * mode_info.XResolution / 4 && mouse_info.x < mode_info.XResolution && mouse_info.y > mode_info.YResolution / 4 && mouse_info.y < mode_info.YResolution / 2)
    {
        if (mouse_info.left_click)
        {
            backPressed8 = true;
        }
    }
    if (backPressed8)
    {
        draw_sprite_xpm(&matrix[1][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[1][3].id;
            index_1_bool = &backPressed8;
            index_1 = &matrix[1][3];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[1][3]) {
            matrix_id2 = matrix[1][3].id;
            index_2_bool = &backPressed8;
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
            printf("The value of the backPressed8 is %d",backPressed8);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}
void process_deck9()
{
    if (mouse_info.x > 0 && mouse_info.x < mode_info.XResolution / 4 && mouse_info.y > mode_info.YResolution / 2 && mouse_info.y < 3 * mode_info.YResolution / 4)
    {
        if (mouse_info.left_click)
        {
            backPressed9 = true;
        }
    }
    if (backPressed9)
    {
        draw_sprite_xpm(&matrix[2][0], 0, mode_info.YResolution / 2);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[2][0].id;
            index_1_bool = &backPressed9;
            index_1 = &matrix[2][0];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[2][0]) {
            matrix_id2 = matrix[2][0].id;
            index_2_bool = &backPressed9;
            index_2 = &matrix[2][0];
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
            printf("The value of the backPressed9 is %d",backPressed9);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}
void process_deck10()
{
    if (mouse_info.x > mode_info.XResolution / 4 && mouse_info.x < mode_info.XResolution / 2 && mouse_info.y > mode_info.YResolution / 2 && mouse_info.y < 3 * mode_info.YResolution / 4)
    {
        if (mouse_info.left_click)
        {
            backPressed10 = true;
        }
    }
    if (backPressed10)
    {
        draw_sprite_xpm(&matrix[2][1], mode_info.XResolution / 4, mode_info.YResolution / 2);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[2][1].id;
            index_1_bool = &backPressed10;
            index_1 = &matrix[2][1];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[2][1]) {
            matrix_id2 = matrix[2][1].id;
            index_2_bool = &backPressed10;
            index_2 = &matrix[2][1];
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
            printf("The value of the backPressed10 is %d",backPressed10);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}
void process_deck11()
{
    if (mouse_info.x > mode_info.XResolution / 2 && mouse_info.x < 3 * mode_info.XResolution / 4 && mouse_info.y > mode_info.YResolution / 2 && mouse_info.y < 3 * mode_info.YResolution / 4)
    {
        if (mouse_info.left_click)
        {
            backPressed11 = true;
        }
    }
    if (backPressed11)
    {
        draw_sprite_xpm(&matrix[2][2], mode_info.XResolution / 2, mode_info.YResolution / 2);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[2][2].id;
            index_1_bool = &backPressed11;
            index_1 = &matrix[2][2];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[2][2]) {
            matrix_id2 = matrix[2][2].id;
            index_2_bool = &backPressed11;
            index_2 = &matrix[2][2];
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
            printf("The value of the backPressed11 is %d",backPressed11);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}
void process_deck12()
{
    if (mouse_info.x > 3 * mode_info.XResolution / 4 && mouse_info.x < mode_info.XResolution && mouse_info.y > mode_info.YResolution / 2 && mouse_info.y < 3 * mode_info.YResolution / 4)
    {
        if (mouse_info.left_click)
        {
            backPressed12 = true;
        }
    }
    if (backPressed12)
    {
        draw_sprite_xpm(&matrix[2][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 2);
       printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[2][3].id;
            index_1_bool = &backPressed12;
            index_1 = &matrix[2][3];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[2][3]) {
            matrix_id2 = matrix[2][3].id;
            index_2_bool = &backPressed12;
            index_2 = &matrix[2][3];
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
            printf("The value of the backPressed12 is %d",backPressed12);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}
void process_deck13()
{
    if (mouse_info.x > 0 && mouse_info.x < mode_info.XResolution / 4 && mouse_info.y > 3 * mode_info.YResolution / 4 && mouse_info.y < mode_info.YResolution)
    {
        if (mouse_info.left_click)
        {
            backPressed13 = true;
        }
    }
    if (backPressed13)
    {
        draw_sprite_xpm(&matrix[3][0], 0, 3 * mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[3][0].id;
            index_1_bool = &backPressed13;
            index_1 = &matrix[3][0];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[3][0]) {
            matrix_id2 = matrix[3][0].id;
            index_2_bool = &backPressed13;
            index_2 = &matrix[3][0];
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
            printf("The value of the backPressed13 is %d",backPressed13);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}
void process_deck14()
{
    if (mouse_info.x > mode_info.XResolution / 4 && mouse_info.x < mode_info.XResolution / 2 && mouse_info.y > 3 * mode_info.YResolution / 4 && mouse_info.y < mode_info.YResolution)
    {
        if (mouse_info.left_click)
        {
            backPressed14 = true;
        }
    }
    if (backPressed14)
    {
        draw_sprite_xpm(&matrix[3][1], mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[3][1].id;
            index_1_bool = &backPressed14;
            index_1 = &matrix[3][1];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[3][1]) {
            matrix_id2 = matrix[3][1].id;
            index_2_bool = &backPressed14;
            index_2 = &matrix[3][1];
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
            printf("The value of the backPressed14 is %d",backPressed14);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}
void process_deck15()
{
    if (mouse_info.x > mode_info.XResolution / 2 && mouse_info.x < 3 * mode_info.XResolution / 4 && mouse_info.y > 3 * mode_info.YResolution / 4 && mouse_info.y < mode_info.YResolution)
    {
        if (mouse_info.left_click)
        {
            backPressed15 = true;
        }
    }
    if (backPressed15)
    {
        draw_sprite_xpm(&matrix[3][2], mode_info.XResolution / 2, 3 * mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[3][2].id;
            index_1_bool = &backPressed15;
            index_1 = &matrix[3][2];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[3][2]) {
            matrix_id2 = matrix[3][2].id;
            index_2_bool = &backPressed15;
            index_2 = &matrix[3][2];
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

        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}
void process_deck16()
{
    if (mouse_info.x > 3 * mode_info.XResolution / 4 && mouse_info.x < mode_info.XResolution && mouse_info.y > 3 * mode_info.YResolution / 4 && mouse_info.y < mode_info.YResolution)
    {
        if (mouse_info.left_click)
        {
            backPressed16 = true;
        }
    }
    if (backPressed16)
    {
        draw_sprite_xpm(&matrix[3][3], 3 * mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[3][3].id;
            index_1_bool = &backPressed16;
            index_1 = &matrix[3][3];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[3][3]) {
            matrix_id2 = matrix[3][3].id;
            index_2_bool = &backPressed16;
            index_2 = &matrix[3][3];
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
            printf("The value of the backPressed16 is %d",backPressed16);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
    }
}

void draw_game_menu_3()
{
    Sprite *deck1 = back;
    Sprite *deck2 = back;
    Sprite *deck3 = back;
    Sprite *deck4 = back;
    Sprite *deck5 = back;
    Sprite *deck6 = back;
    Sprite *deck7 = back;
    Sprite *deck8 = back;
    Sprite *deck9 = back;
    Sprite *deck10 = back;
    Sprite *deck11 = back;
    Sprite *deck12 = back;
    Sprite *deck13 = back;
    Sprite *deck14 = back;
    Sprite *deck15 = back;
    Sprite *deck16 = back;

    Sprite cards3[] = {*number1, *number1, *number2, *number2, *number3, *number3, *number4, *number4, *number5, *number5, *number6, *number6, *number7, *number7, *number8, *number8};
    if (pre2 == 0)
    {
        matrix = alloc_matrix(4,4);
        shuffle3(cards3);
        pre2++;
    }

    memset(drawing_frame_buffer, 0x000000, mode_info.XResolution * mode_info.YResolution * mode_info.BitsPerPixel / 8);
    draw_sprite_xpm(deck1, 0, 0);
    draw_sprite_xpm(deck2, mode_info.XResolution / 4, 0);
    draw_sprite_xpm(deck3, mode_info.XResolution / 2, 0);
    draw_sprite_xpm(deck4, 3 * mode_info.XResolution / 4, 0);
    draw_sprite_xpm(deck5, 0, mode_info.YResolution / 4);
    draw_sprite_xpm(deck6, mode_info.XResolution / 4, mode_info.YResolution / 4);
    draw_sprite_xpm(deck7, mode_info.XResolution / 2, mode_info.YResolution / 4);
    draw_sprite_xpm(deck8, 3 * mode_info.XResolution / 4, mode_info.YResolution / 4);
    draw_sprite_xpm(deck9, 0, mode_info.YResolution / 2);
    draw_sprite_xpm(deck10, mode_info.XResolution / 4, mode_info.YResolution / 2);
    draw_sprite_xpm(deck11, mode_info.XResolution / 2, mode_info.YResolution / 2);
    draw_sprite_xpm(deck12, 3 * mode_info.XResolution / 4, mode_info.YResolution / 2);
    draw_sprite_xpm(deck13, 0, 3 * mode_info.YResolution / 4);
    draw_sprite_xpm(deck14, mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
    draw_sprite_xpm(deck15, mode_info.XResolution / 2, 3 * mode_info.YResolution / 4);
    draw_sprite_xpm(deck16, 3 * mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);

    if (matrix[0][0].block == false)
    {
        process_deck1();
    }
    else if (matrix[0][0].block == true)
    {
        draw_sprite_xpm(&matrix[0][0], 0, 0);
    }
    if (matrix[0][1].block == false)
    {
        process_deck2();
    }
    else if (matrix[0][1].block == true)
    {
        draw_sprite_xpm(&matrix[0][1], mode_info.XResolution / 4, 0);
    }
    if (matrix[0][2].block == false)
    {
        process_deck3();
    }
    else if (matrix[0][2].block == true)
    {
        draw_sprite_xpm(&matrix[0][2], mode_info.XResolution / 2, 0);
    }
    if (matrix[0][3].block== false)
    {
        process_deck4();
    }
    else if (matrix[0][3].block == true)
    {
        draw_sprite_xpm(&matrix[0][3], 3 * mode_info.XResolution / 4, 0);
    }
    if (matrix[1][0].block == false)
    {
        process_deck5();
    }
    else if (matrix[1][0].block== true)
    {
        draw_sprite_xpm(&matrix[1][0], 0, mode_info.YResolution / 4);
    }
    if (matrix[1][1].block == false)
    {
        process_deck6();
    }
    else if (matrix[1][1].block == true)
    {
        draw_sprite_xpm(&matrix[1][1], mode_info.XResolution / 4, mode_info.YResolution / 4);
    }
    if (matrix[1][2].block == false)
    {
        process_deck7();
    }
    else if (matrix[1][2].block == true)
    {
        draw_sprite_xpm(&matrix[1][2], mode_info.XResolution / 2, mode_info.YResolution / 4);
    }
    if (matrix[1][3].block == false)
    {
        process_deck8();
    }
    else if (matrix[1][3].block == true)
    {
        draw_sprite_xpm(&matrix[1][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 4);
    }
    if (matrix[2][0].block == false)
    {
        process_deck9();
    }
    else if (matrix[2][0].block == true)
    {
        draw_sprite_xpm(&matrix[2][0], 0, mode_info.YResolution / 2);
    }
    if (matrix[2][1].block == false)
    {
        process_deck10();
    }
    else if (matrix[2][1].block == true)
    {
        draw_sprite_xpm(&matrix[2][1], mode_info.XResolution / 4, mode_info.YResolution / 2);
    }
    if (matrix[2][2].block == false)
    {
        process_deck11();
    }
    else if (matrix[2][2].block == true)
    {
        draw_sprite_xpm(&matrix[2][2], mode_info.XResolution / 2, mode_info.YResolution / 2);
    }
    if (matrix[2][3].block== false)
    {
        process_deck12();
    }
    else if (matrix[2][3].block == true)
    {
        draw_sprite_xpm(&matrix[2][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 2);
    }
    if (matrix[3][0].block == false)
    {
        process_deck13();
    }
    else if (matrix[3][0].block == true)
    {
        draw_sprite_xpm(&matrix[3][0], 0, 3 * mode_info.YResolution / 4);
    }
    if (matrix[3][1].block == false)
    {
        process_deck14();
    }
    else if (matrix[3][1].block == true)
    {
        draw_sprite_xpm(&matrix[3][1], mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
    }
    if (matrix[3][2].block == false)
    {
        process_deck15();
    }
    else if (matrix[3][2].block == true)
    {
        draw_sprite_xpm(&matrix[3][2], mode_info.XResolution / 2, 3 * mode_info.YResolution / 4);
    }
    if (matrix[3][3].block == false)
    {
        process_deck16();
    }
    else if (matrix[3][3].block == true)
    {
        draw_sprite_xpm(&matrix[3][3], 3 * mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
    }
    if (deck1->block && deck2->block && deck3->block && deck4->block && deck5->block && deck6->block && deck7->block && deck8->block && deck9->block && deck10->block && deck11->block && deck12->block && deck13->block && deck14->block && deck15->block && deck16->block)
    {
        menuState = END;
    }
    
}