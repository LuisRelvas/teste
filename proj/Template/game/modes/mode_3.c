#include "mode_3.h"

extern int pre2;
extern Sprite **matrix;
extern Sprite *position_1;
extern Sprite *position_2;
extern bool *position_1_bool;
extern bool *position_2_bool;
extern int matrix_id1;
extern int matrix_id2;
extern int timer_interrupts;
extern vbe_mode_info_t mode_info;
extern Mouse_Info_Struct mouse_info_s;
extern real_time_mode_info time_mode_info;
extern MenuState menuState;
extern SystemState systemState;
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
extern bool backPressed1;
extern bool backPressed2;
extern bool backPressed3;
extern bool backPressed4;
extern bool backPressed5;
extern bool backPressed6;
extern bool backPressed7;
extern bool backPressed8;
extern bool backPressed9;
extern bool backPressed10;
extern bool backPressed11;
extern bool backPressed12;
extern bool backPressed13;
extern bool backPressed14;
extern bool backPressed15;
extern bool backPressed16;
extern uint8_t *main_frame_buf;
extern uint8_t *SECONDSondary_frame_buf;
extern uint8_t *drawing_frame_buf;
extern uint32_t frame_buf_size;
extern bool isAnimating;
extern int animationFrame;
extern Sprite *back_anim1;
extern Sprite *back_anim2;
extern Sprite *back_anim3;
extern Sprite *back_anim4;

void process_deck1()
{
    if (mouse_info_s.x > 0 && mouse_info_s.x < mode_info.XResolution / 4 && mouse_info_s.y > 0 && mouse_info_s.y < mode_info.YResolution / 4)
    {
        if (mouse_info_s.left_click)
        {
            backPressed1 = true;
            
        }
    }
    if (backPressed1)
    {
        draw_xpm(&matrix[0][0], 0, 0);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[0][0].id;
            position_1_bool = &backPressed1;
            position_1 = &matrix[0][0];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[0][0])
        {
            matrix_id2 = matrix[0][0].id;
            position_2_bool = &backPressed1;
            position_2 = &matrix[0][0];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
                printf("The value of the backPressed1 is %d", backPressed1);
            }
            matrix_id1 = -1;
            matrix_id2 = -1;
        }
    }
}
void process_deck2()
{
    if (mouse_info_s.x > mode_info.XResolution / 4 && mouse_info_s.x < mode_info.XResolution / 2 && mouse_info_s.y > 0 && mouse_info_s.y < mode_info.YResolution / 4)
    {
        if (mouse_info_s.left_click)
        {
            backPressed2 = true;
            
        }
    }
    if (backPressed2)
    {
        draw_xpm(&matrix[0][1], mode_info.XResolution / 4, 0);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[0][1].id;
            position_1_bool = &backPressed2;
            position_1 = &matrix[0][1];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[0][1])
        {
            matrix_id2 = matrix[0][1].id;
            position_2_bool = &backPressed2;
            position_2 = &matrix[0][1];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
                printf("The value of the backPressed2 is %d", backPressed2);
            }
            matrix_id1 = -1;
            matrix_id2 = -1;
        }
    }
}
void process_deck3()
{
    if (mouse_info_s.x > mode_info.XResolution / 2 && mouse_info_s.x < 3 * mode_info.XResolution / 4 && mouse_info_s.y > 0 && mouse_info_s.y < mode_info.YResolution / 4)
    {
        if (mouse_info_s.left_click)
        {
            backPressed3 = true;
            
        }
    }
    if (backPressed3)
    {
        draw_xpm(&matrix[0][2], mode_info.XResolution / 2, 0);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[0][2].id;
            position_1_bool = &backPressed3;
            position_1 = &matrix[0][2];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[0][2])
        {
            matrix_id2 = matrix[0][2].id;
            position_2_bool = &backPressed3;
            position_2 = &matrix[0][2];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
                printf("The value of the backPressed3 is %d", backPressed3);
            }
            matrix_id1 = -1;
            matrix_id2 = -1;
        }
    }
}
void process_deck4()
{
    if (mouse_info_s.x > 3 * mode_info.XResolution / 4 && mouse_info_s.x < mode_info.XResolution && mouse_info_s.y > 0 && mouse_info_s.y < mode_info.YResolution / 4)
    {
        if (mouse_info_s.left_click)
        {
            backPressed4 = true;
            
        }
    }
    if (backPressed4)
    {
        draw_xpm(&matrix[0][3], 3 * mode_info.XResolution / 4, 0);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[0][3].id;
            position_1_bool = &backPressed4;
            position_1 = &matrix[0][3];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[0][3])
        {
            matrix_id2 = matrix[0][3].id;
            position_2_bool = &backPressed4;
            position_2 = &matrix[0][3];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
                printf("The value of the backPressed4 is %d", backPressed4);
            }
            matrix_id1 = -1;
            matrix_id2 = -1;
        }
    }
}
void process_deck5()
{
    if (mouse_info_s.x > 0 && mouse_info_s.x < mode_info.XResolution / 4 && mouse_info_s.y > mode_info.YResolution / 4 && mouse_info_s.y < mode_info.YResolution / 2)
    {
        if (mouse_info_s.left_click)
        {
            backPressed5 = true;
            
        }
    }
    if (backPressed5)
    {
        draw_xpm(&matrix[1][0], 0, mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[1][0].id;
            position_1_bool = &backPressed5;
            position_1 = &matrix[1][0];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[1][0])
        {
            matrix_id2 = matrix[1][0].id;
            position_2_bool = &backPressed5;
            position_2 = &matrix[1][0];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
                printf("The value of the backPressed5 is %d", backPressed5);
            }
            matrix_id1 = -1;
            matrix_id2 = -1;
        }
    }
}
void process_deck6()
{
    if (mouse_info_s.x > mode_info.XResolution / 4 && mouse_info_s.x < mode_info.XResolution / 2 && mouse_info_s.y > mode_info.YResolution / 4 && mouse_info_s.y < mode_info.YResolution / 2)
    {
        if (mouse_info_s.left_click)
        {
            backPressed6 = true;
            
        }
    }
    if (backPressed6)
    {
        draw_xpm(&matrix[1][1], mode_info.XResolution / 4, mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[1][1].id;
            position_1_bool = &backPressed6;
            position_1 = &matrix[1][1];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[1][1])
        {
            matrix_id2 = matrix[1][1].id;
            position_2_bool = &backPressed6;
            position_2 = &matrix[1][1];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
                printf("The value of the backPressed6 is %d", backPressed6);
            }
            matrix_id1 = -1;
            matrix_id2 = -1;
        }
    }
}
void process_deck7()
{
    if (mouse_info_s.x > mode_info.XResolution / 2 && mouse_info_s.x < 3 * mode_info.XResolution / 4 && mouse_info_s.y > mode_info.YResolution / 4 && mouse_info_s.y < mode_info.YResolution / 2)
    {
        if (mouse_info_s.left_click)
        {
            backPressed7 = true;
            
        }
    }
    if (backPressed7)
    {
        draw_xpm(&matrix[1][2], mode_info.XResolution / 2, mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[1][2].id;
            position_1_bool = &backPressed7;
            position_1 = &matrix[1][2];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[1][2])
        {
            matrix_id2 = matrix[1][2].id;
            position_2_bool = &backPressed7;
            position_2 = &matrix[1][2];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
                printf("The value of the backPressed7 is %d", backPressed7);
            }
            matrix_id1 = -1;
            matrix_id2 = -1;
        }
    }
}
void process_deck8()
{
    if (mouse_info_s.x > 3 * mode_info.XResolution / 4 && mouse_info_s.x < mode_info.XResolution && mouse_info_s.y > mode_info.YResolution / 4 && mouse_info_s.y < mode_info.YResolution / 2)
    {
        if (mouse_info_s.left_click)
        {
            backPressed8 = true;
            
        }
    }
    if (backPressed8)
    {
        draw_xpm(&matrix[1][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[1][3].id;
            position_1_bool = &backPressed8;
            position_1 = &matrix[1][3];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[1][3])
        {
            matrix_id2 = matrix[1][3].id;
            position_2_bool = &backPressed8;
            position_2 = &matrix[1][3];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
                printf("The value of the backPressed8 is %d", backPressed8);
            }
            matrix_id1 = -1;
            matrix_id2 = -1;
        }
    }
}
void process_deck9()
{
    if (mouse_info_s.x > 0 && mouse_info_s.x < mode_info.XResolution / 4 && mouse_info_s.y > mode_info.YResolution / 2 && mouse_info_s.y < 3 * mode_info.YResolution / 4)
    {
        if (mouse_info_s.left_click)
        {
            backPressed9 = true;
            
        }
    }
    if (backPressed9)
    {
        draw_xpm(&matrix[2][0], 0, mode_info.YResolution / 2);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[2][0].id;
            position_1_bool = &backPressed9;
            position_1 = &matrix[2][0];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[2][0])
        {
            matrix_id2 = matrix[2][0].id;
            position_2_bool = &backPressed9;
            position_2 = &matrix[2][0];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
                printf("The value of the backPressed9 is %d", backPressed9);
            }
            matrix_id1 = -1;
            matrix_id2 = -1;
        }
    }
}
void process_deck10()
{
    if (mouse_info_s.x > mode_info.XResolution / 4 && mouse_info_s.x < mode_info.XResolution / 2 && mouse_info_s.y > mode_info.YResolution / 2 && mouse_info_s.y < 3 * mode_info.YResolution / 4)
    {
        if (mouse_info_s.left_click)
        {
            backPressed10 = true;
            
        }
    }
    if (backPressed10)
    {
        draw_xpm(&matrix[2][1], mode_info.XResolution / 4, mode_info.YResolution / 2);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[2][1].id;
            position_1_bool = &backPressed10;
            position_1 = &matrix[2][1];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[2][1])
        {
            matrix_id2 = matrix[2][1].id;
            position_2_bool = &backPressed10;
            position_2 = &matrix[2][1];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
                printf("The value of the backPressed10 is %d", backPressed10);
            }
            matrix_id1 = -1;
            matrix_id2 = -1;
        }
    }
}
void process_deck11()
{
    if (mouse_info_s.x > mode_info.XResolution / 2 && mouse_info_s.x < 3 * mode_info.XResolution / 4 && mouse_info_s.y > mode_info.YResolution / 2 && mouse_info_s.y < 3 * mode_info.YResolution / 4)
    {
        if (mouse_info_s.left_click)
        {
            backPressed11 = true;
            
        }
    }
    if (backPressed11)
    {
        draw_xpm(&matrix[2][2], mode_info.XResolution / 2, mode_info.YResolution / 2);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[2][2].id;
            position_1_bool = &backPressed11;
            position_1 = &matrix[2][2];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[2][2])
        {
            matrix_id2 = matrix[2][2].id;
            position_2_bool = &backPressed11;
            position_2 = &matrix[2][2];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
                printf("The value of the backPressed11 is %d", backPressed11);
            }
            matrix_id1 = -1;
            matrix_id2 = -1;
        }
    }
}
void process_deck12()
{
    if (mouse_info_s.x > 3 * mode_info.XResolution / 4 && mouse_info_s.x < mode_info.XResolution && mouse_info_s.y > mode_info.YResolution / 2 && mouse_info_s.y < 3 * mode_info.YResolution / 4)
    {
        if (mouse_info_s.left_click)
        {
            backPressed12 = true;
            
        }
    }
    if (backPressed12)
    {
        draw_xpm(&matrix[2][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 2);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[2][3].id;
            position_1_bool = &backPressed12;
            position_1 = &matrix[2][3];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[2][3])
        {
            matrix_id2 = matrix[2][3].id;
            position_2_bool = &backPressed12;
            position_2 = &matrix[2][3];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
                printf("The value of the backPressed12 is %d", backPressed12);
            }
            matrix_id1 = -1;
            matrix_id2 = -1;
        }
    }
}
void process_deck13()
{
    if (mouse_info_s.x > 0 && mouse_info_s.x < mode_info.XResolution / 4 && mouse_info_s.y > 3 * mode_info.YResolution / 4 && mouse_info_s.y < mode_info.YResolution)
    {
        if (mouse_info_s.left_click)
        {
            backPressed13 = true;
            
        }
    }
    if (backPressed13)
    {
        draw_xpm(&matrix[3][0], 0, 3 * mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[3][0].id;
            position_1_bool = &backPressed13;
            position_1 = &matrix[3][0];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[3][0])
        {
            matrix_id2 = matrix[3][0].id;
            position_2_bool = &backPressed13;
            position_2 = &matrix[3][0];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
                printf("The value of the backPressed13 is %d", backPressed13);
            }
            matrix_id1 = -1;
            matrix_id2 = -1;
        }
    }
}
void process_deck14()
{
    if (mouse_info_s.x > mode_info.XResolution / 4 && mouse_info_s.x < mode_info.XResolution / 2 && mouse_info_s.y > 3 * mode_info.YResolution / 4 && mouse_info_s.y < mode_info.YResolution)
    {
        if (mouse_info_s.left_click)
        {
            backPressed14 = true;
            
        }
    }
    if (backPressed14)
    {
        draw_xpm(&matrix[3][1], mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[3][1].id;
            position_1_bool = &backPressed14;
            position_1 = &matrix[3][1];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[3][1])
        {
            matrix_id2 = matrix[3][1].id;
            position_2_bool = &backPressed14;
            position_2 = &matrix[3][1];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
                printf("The value of the backPressed14 is %d", backPressed14);
            }
            matrix_id1 = -1;
            matrix_id2 = -1;
        }
    }
}
void process_deck15()
{
    if (mouse_info_s.x > mode_info.XResolution / 2 && mouse_info_s.x < 3 * mode_info.XResolution / 4 && mouse_info_s.y > 3 * mode_info.YResolution / 4 && mouse_info_s.y < mode_info.YResolution)
    {
        if (mouse_info_s.left_click)
        {
            backPressed15 = true;
            
        }
    }
    if (backPressed15)
    {
        draw_xpm(&matrix[3][2], mode_info.XResolution / 2, 3 * mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[3][2].id;
            position_1_bool = &backPressed15;
            position_1 = &matrix[3][2];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[3][2])
        {
            matrix_id2 = matrix[3][2].id;
            position_2_bool = &backPressed15;
            position_2 = &matrix[3][2];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
            }
            matrix_id1 = -1;
            matrix_id2 = -1;
        }
    }
}
void process_deck16()
{
    if (mouse_info_s.x > 3 * mode_info.XResolution / 4 && mouse_info_s.x < mode_info.XResolution && mouse_info_s.y > 3 * mode_info.YResolution / 4 && mouse_info_s.y < mode_info.YResolution)
    {
        if (mouse_info_s.left_click)
        {
            backPressed16 = true;
            
        }
    }
    if (backPressed16)
    {
        draw_xpm(&matrix[3][3], 3 * mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
        printf("Entrei no botao 1\n");
        if (matrix_id1 == -1)
        {
            matrix_id1 = matrix[3][3].id;
            position_1_bool = &backPressed16;
            position_1 = &matrix[3][3];
            printf("The value of position_1 on button1 is %d\n", position_1);
            printf("The value of matrix_id1 on button1 is %d", matrix_id1);
        }
        else if (matrix_id2 == -1 && position_1 != &matrix[3][3])
        {
            matrix_id2 = matrix[3][3].id;
            position_2_bool = &backPressed16;
            position_2 = &matrix[3][3];
            printf("The value of position_2 on button1 is %d\n", position_2);
            printf("The value of matrix_id2 on button1 is %d", matrix_id2);
        }
        if (matrix_id1 != -1 && matrix_id2 != -1)
        {
            if (check_match(matrix_id1, matrix_id2))
            {
                position_1->block = true;
                position_2->block = true;
            }
            else if (!check_match(matrix_id1, matrix_id2))
            {
                *position_2_bool = false;
                *position_1_bool = false;
                printf("The value of the backPressed16 is %d", backPressed16);
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
        matrix = alloc_matrix(4, 4);
        shuffle3(cards3);
        pre2++;
    }

    memset(drawing_frame_buf, 0x000000, mode_info.XResolution * mode_info.YResolution * mode_info.BitsPerPixel / 8);
    draw_xpm(deck1, 0, 0);
    draw_xpm(deck2, mode_info.XResolution / 4, 0);
    draw_xpm(deck3, mode_info.XResolution / 2, 0);
    draw_xpm(deck4, 3 * mode_info.XResolution / 4, 0);
    draw_xpm(deck5, 0, mode_info.YResolution / 4);
    draw_xpm(deck6, mode_info.XResolution / 4, mode_info.YResolution / 4);
    draw_xpm(deck7, mode_info.XResolution / 2, mode_info.YResolution / 4);
    draw_xpm(deck8, 3 * mode_info.XResolution / 4, mode_info.YResolution / 4);
    draw_xpm(deck9, 0, mode_info.YResolution / 2);
    draw_xpm(deck10, mode_info.XResolution / 4, mode_info.YResolution / 2);
    draw_xpm(deck11, mode_info.XResolution / 2, mode_info.YResolution / 2);
    draw_xpm(deck12, 3 * mode_info.XResolution / 4, mode_info.YResolution / 2);
    draw_xpm(deck13, 0, 3 * mode_info.YResolution / 4);
    draw_xpm(deck14, mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
    draw_xpm(deck15, mode_info.XResolution / 2, 3 * mode_info.YResolution / 4);
    draw_xpm(deck16, 3 * mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);

    if (matrix[0][0].block == false)
    {
        process_deck1();
    }
    else if (matrix[0][0].block == true)
    {
        draw_xpm(&matrix[0][0], 0, 0);
    }
    if (matrix[0][1].block == false)
    {
        process_deck2();
    }
    else if (matrix[0][1].block == true)
    {
        draw_xpm(&matrix[0][1], mode_info.XResolution / 4, 0);
    }
    if (matrix[0][2].block == false)
    {
        process_deck3();
    }
    else if (matrix[0][2].block == true)
    {
        draw_xpm(&matrix[0][2], mode_info.XResolution / 2, 0);
    }
    if (matrix[0][3].block == false)
    {
        process_deck4();
    }
    else if (matrix[0][3].block == true)
    {
        draw_xpm(&matrix[0][3], 3 * mode_info.XResolution / 4, 0);
    }
    if (matrix[1][0].block == false)
    {
        process_deck5();
    }
    else if (matrix[1][0].block == true)
    {
        draw_xpm(&matrix[1][0], 0, mode_info.YResolution / 4);
    }
    if (matrix[1][1].block == false)
    {
        process_deck6();
    }
    else if (matrix[1][1].block == true)
    {
        draw_xpm(&matrix[1][1], mode_info.XResolution / 4, mode_info.YResolution / 4);
    }
    if (matrix[1][2].block == false)
    {
        process_deck7();
    }
    else if (matrix[1][2].block == true)
    {
        draw_xpm(&matrix[1][2], mode_info.XResolution / 2, mode_info.YResolution / 4);
    }
    if (matrix[1][3].block == false)
    {
        process_deck8();
    }
    else if (matrix[1][3].block == true)
    {
        draw_xpm(&matrix[1][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 4);
    }
    if (matrix[2][0].block == false)
    {
        process_deck9();
    }
    else if (matrix[2][0].block == true)
    {
        draw_xpm(&matrix[2][0], 0, mode_info.YResolution / 2);
    }
    if (matrix[2][1].block == false)
    {
        process_deck10();
    }
    else if (matrix[2][1].block == true)
    {
        draw_xpm(&matrix[2][1], mode_info.XResolution / 4, mode_info.YResolution / 2);
    }
    if (matrix[2][2].block == false)
    {
        process_deck11();
    }
    else if (matrix[2][2].block == true)
    {
        draw_xpm(&matrix[2][2], mode_info.XResolution / 2, mode_info.YResolution / 2);
    }
    if (matrix[2][3].block == false)
    {
        process_deck12();
    }
    else if (matrix[2][3].block == true)
    {
        draw_xpm(&matrix[2][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 2);
    }
    if (matrix[3][0].block == false)
    {
        process_deck13();
    }
    else if (matrix[3][0].block == true)
    {
        draw_xpm(&matrix[3][0], 0, 3 * mode_info.YResolution / 4);
    }
    if (matrix[3][1].block == false)
    {
        process_deck14();
    }
    else if (matrix[3][1].block == true)
    {
        draw_xpm(&matrix[3][1], mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
    }
    if (matrix[3][2].block == false)
    {
        process_deck15();
    }
    else if (matrix[3][2].block == true)
    {
        draw_xpm(&matrix[3][2], mode_info.XResolution / 2, 3 * mode_info.YResolution / 4);
    }
    if (matrix[3][3].block == false)
    {
        process_deck16();
    }
    else if (matrix[3][3].block == true)
    {
        draw_xpm(&matrix[3][3], 3 * mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
    }
    if (matrix[0][0].block == true && matrix[0][1].block == true && matrix[0][2].block == true && matrix[0][3].block == true && matrix[1][0].block == true && matrix[1][1].block == true && matrix[1][2].block == true && matrix[1][3].block == true && matrix[2][0].block == true && matrix[2][1].block == true && matrix[2][2].block == true && matrix[2][3].block == true && matrix[3][0].block == true && matrix[3][1].block == true && matrix[3][2].block == true && matrix[3][3].block == true)
    {
        menuState = END;
    }
    Sprite *curr_frame = back_anim1;
    uint16_t x = 0;
    uint16_t y = 0;
    if (backPressed1)
    {
        x = 0;
        y = 0;
    }
    if (backPressed2)
    {
        x = mode_info.XResolution / 4;
        y = 0;
    }
    if (backPressed3)
    {
        x = mode_info.XResolution / 2;
        y = 0;
    }
    if (backPressed4)
    {
        x = 3 * mode_info.XResolution / 4;
        y = 0;
    }
    if (backPressed5)
    {
        x = 0;
        y = mode_info.YResolution / 4;
    }
    if (backPressed6)
    {
        x = mode_info.XResolution / 4;
        y = mode_info.YResolution / 4;
    }
    if (backPressed7)
    {
        x = mode_info.XResolution / 2;
        y = mode_info.YResolution / 4;
    }
    if (backPressed8)
    {
        x = 3 * mode_info.XResolution / 4;
        y = mode_info.YResolution / 4;
    }
    if (backPressed9)
    {
        x = 0;
        y = mode_info.YResolution / 2;
    }
    if (backPressed10)
    {
        x = mode_info.XResolution / 4;
        y = mode_info.YResolution / 2;
    }
    if (backPressed11)
    {
        x = mode_info.XResolution / 2;
        y = mode_info.YResolution / 2;
    }
    if (backPressed12)
    {
        x = 3 * mode_info.XResolution / 4;
        y = mode_info.YResolution / 2;
    }
    if (backPressed13)
    {
        x = 0;
        y = 3 * mode_info.YResolution / 4;
    }
    if (backPressed14)
    {
        x = mode_info.XResolution / 4;
        y = 3 * mode_info.YResolution / 4;
    }
    if (backPressed15)
    {
        x = mode_info.XResolution / 2;
        y = 3 * mode_info.YResolution / 4;
    }
    if (backPressed16)
    {
        x = 3 * mode_info.XResolution / 4;
        y = 3 * mode_info.YResolution / 4;
    }

    if (isAnimating)
    {
        switch (animationFrame)
        {
        case 0:
            curr_frame = back_anim1;
            break;
        case 1:
            curr_frame = back_anim2;
            break;
        case 2:
            curr_frame = back_anim3;
            break;
        case 3:
            curr_frame = back_anim4;
            break;
        }

        draw_xpm(curr_frame, x, y);

        // Increment animation frame
        animationFrame++;

        // Check if reached the end of the animation frames
        if (animationFrame == 3)
        {
            isAnimating = false; // Animation finished, reset the animation state
            // Perform any additional actions after the animation finishes
        }
    }
}
