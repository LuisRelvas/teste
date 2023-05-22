#include "mode_1.h"
#include "menu.h"

extern MenuState menuState;

bool button1Pressed = false;
bool button2Pressed = false;
bool button3Pressed = false;
bool button4Pressed = false;
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

void shuffle(Sprite *cards, int size)
{
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
    matrix[1][0] = cards[2];
    matrix[1][1] = cards[3];
    // how can I compare the values  ?
    //  Compare all elements in the matrix
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            // Compare the current element to all other elements in the matrix
            for (int k = 0; k < 2; k++)
            {
                for (int l = 0; l < 2; l++)
                {
                    // If the current element is not being compared to itself and has the same id as another element,
                    // print a message indicating that there is a match
                    if (i != k || j != l)
                    {
                        if (matrix[i][j].id == matrix[k][l].id)
                        {
                            printf("Match found: matrix[%d][%d].id = %d and matrix[%d][%d].id = %d\n",
                                   i, j, matrix[i][j].id, k, l, matrix[k][l].id);
                        }
                    }
                }
            }
        }
    }
}


void process_button1(Sprite *cards, int size)
{
    if (mouse_info.x < mode_info.XResolution / 2 && mouse_info.y < mode_info.YResolution / 2)
    {
        if(mouse_info.left_click){
        printf("BOTAO 1 CLICK\n");
        button1Pressed = true;
        }
    }
        if (button1Pressed)
    {
        draw_sprite_xpm(&matrix[0][0], 0, 0);
        printf("Entrei no botao 1\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[0][0].id;
            index_1_bool = &button1Pressed;
            index_1 = &matrix[0][0];
            printf("The value of index_1 on button1 is %d\n",index_1);
            printf("The value of matrix_id1 on button1 is %d",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[0][0]) {
            matrix_id2 = matrix[0][0].id;
            index_2_bool = &button1Pressed;
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
            printf("The value of the button1Pressed is %d",button1Pressed);
        }
        matrix_id1 = -1;
        matrix_id2 = -1; 
        }
        
    }
}

void process_button2(Sprite *cards, int size)
{
    if (mouse_info.x >= mode_info.XResolution / 2 && mouse_info.y <= mode_info.YResolution / 2)
    {
        if(mouse_info.left_click){
        button2Pressed = true;
        }
    }

    if (button2Pressed){
        draw_sprite_xpm(&matrix[0][1], mode_info.XResolution / 2, 0);
        printf("ENTREI NO BOTAO 2\n");
        if(matrix_id1 == -1) { 
            matrix_id1 = matrix[0][1].id;
            index_1_bool = &button2Pressed;
            index_1 = &matrix[0][1]; 
            printf("The value of index_1 on button2 is %d\n",index_1);
            printf("The value of matrix_id1 on  button2 is %d\n",matrix_id1);
        }
        else if(matrix_id2 == -1  && index_1 != &matrix[0][1]) { 
            matrix_id2 = matrix[0][1].id;
            index_2_bool = &button2Pressed;
            index_2 = &matrix[0][1];
            printf("The value of index_2 on button2 is %d\n",index_2);
            printf("The value of matrix_id2 on  button2 is %d\n",matrix_id2);
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

void process_button3(Sprite *cards, int size)
{
    if (mouse_info.x < mode_info.XResolution / 2 && mouse_info.y >= mode_info.YResolution / 2)
    {
        if(mouse_info.left_click){
        button3Pressed = true;
        }
        
    }
        if (button3Pressed)
    {
        draw_sprite_xpm(&matrix[1][0], 0, mode_info.YResolution / 2);
        printf("ENTREI NO BOTAO 3\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[1][0].id;
            index_1_bool = &button3Pressed;
            index_1 = &matrix[1][0];
            printf("The value of index_1 on button3 is %d\n",index_1);
            printf("The value of matrix_id1 on button3 is %d\n",matrix_id1);
        } 
        
        else if(matrix_id2 == -1 && index_1 != &matrix[1][0]) {
            matrix_id2 = matrix[1][0].id;
            index_2_bool = &button3Pressed;
            index_2 = &matrix[1][0];
            printf("The value of index_2 on button3 is %d\n",index_2);
            printf("The value of matrix_id2 on button3 is %d\n",matrix_id2);
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

void process_button4(Sprite *cards, int size)
{
   if (mouse_info.x >= mode_info.XResolution / 2 && mouse_info.y > mode_info.YResolution / 2)
    {
        if(mouse_info.left_click){
        button4Pressed = true;
        }
        
    }
        if (button4Pressed)
    {
        draw_sprite_xpm(&matrix[1][1],mode_info.XResolution / 2, mode_info.YResolution / 2);
        printf("ENTREI NO BOTAO 4\n");
        if(matrix_id1 == -1){
            matrix_id1 = matrix[1][1].id;
            index_1_bool = &button4Pressed;
            index_1 = &matrix[1][1];
            printf("The value of index_1 on button4 is %d\n",index_1);
            printf("The value of matrix_id1 on button4 is %d\n",matrix_id1);
        } 
        else if(matrix_id2 == -1 && index_1 != &matrix[1][1]) {
            matrix_id2 = matrix[1][1].id;
            index_2_bool = &button4Pressed;
            index_2 = &matrix[1][1];
            printf("The value of index_2 on button4 is %d\n",index_2);
            printf("The value of matrix_id2 on button4 is %d\n",matrix_id2);
         }
        if(matrix_id1 != -1 && matrix_id2 != -1) {
        if (check_match(matrix_id1,matrix_id2)){
        index_1->block = true;
        index_2->block = true;
        }
        else { 
            *index_2_bool = false; 
            *index_1_bool = false; 
        }
        matrix_id1 = -1; 
        matrix_id2 = -1;
        }
    }
}

void draw_game_menu()
{
    
    Sprite *back1 = back;
    Sprite *back2 = back;
    Sprite *back3 = back;
    Sprite *back4 = back;

   
    
    Sprite cards[] = {*number1, *number1, *number2, *number2};
    int j = sizeof(cards) / sizeof(cards[0]);


    if (pre == 0)
    {
        matrix = alloc_matrix(2,2);
        shuffle(cards, j);
        printf("matrix allocated\n,%d",matrix);
        pre++;
    }
    
    memset(drawing_frame_buffer, 0, mode_info.XResolution * mode_info.YResolution * mode_info.BitsPerPixel / 8);
    draw_sprite_xpm(back1, 0, 0);
    draw_sprite_xpm(back2, mode_info.XResolution / 2, 0);
    draw_sprite_xpm(back3, 0, mode_info.YResolution / 2);
    draw_sprite_xpm(back4, mode_info.XResolution / 2, mode_info.YResolution / 2);

    
    printf("matrix: %d\n", matrix_id1);
       
    if(matrix[0][0].block == false)
    {
        process_button1(cards,j);
    }
    if(matrix[0][0].block == true) 
    { 
        printf("CONSEGUIU BLOQUEAR");
        draw_sprite_xpm(&matrix[0][0], 0, 0);
    }

    if (matrix[0][1].block == false)
    {
        process_button2(cards, j);
    
    }
    else if (matrix[0][1].block == true)
    {
        printf("CONSEGUIU BLOQUEAR");
        draw_sprite_xpm(&matrix[0][1], mode_info.XResolution / 2, 0);
     
    }
    if (matrix[1][0].block == false)
    {
        process_button3(cards, j);
     
    }
    else if (matrix[1][0].block == true)
    {
        printf("CONSEGUIU BLOQUEAR");
        draw_sprite_xpm(&matrix[1][0], 0, mode_info.YResolution / 2);
    }
    if (matrix[1][1].block == false)
    {
        process_button4(cards, j);
    }
    else if (matrix[1][1].block == true)
    {
        printf("CONSEGUIU BLOQUEAR");
        draw_sprite_xpm(&matrix[1][1], mode_info.XResolution / 2, mode_info.YResolution / 2);
    }
    if (matrix[0][0].block == true && matrix[0][1].block == true && matrix[1][0].block == true && matrix[1][1].block == true)
    {
        menuState = END;
    }
}
