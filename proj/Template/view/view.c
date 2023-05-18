#include "view.h"
#include "../game/modes/menu.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Variáveis externas importantes à visualização do modelo e dos seus estados
uint8_t *main_frame_buffer;
uint8_t *secondary_frame_buffer;
uint8_t *drawing_frame_buffer;
uint32_t frame_buffer_size;
extern int timer_interrupts;
extern vbe_mode_info_t mode_info;
extern MouseInfo mouse_info;
extern real_time_info time_info;
extern MenuState menuState;
extern SystemState systemState;

// Objetos

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
extern Sprite *back_anim1;
extern Sprite *back_anim2;
extern Sprite *back_anim3;
extern Sprite *back_anim4;
int chosen;

// Alocação de memória ao(s) buffer(s)
// Se houver só um buffer, esse é o principal
// Se houver double buffering, há um secundário a alocar a mesma quantidade de memória que serve
// exclusivamente para o desenho
int set_frame_buffers(uint16_t mode)
{
    if (set_frame_buffer(mode, &main_frame_buffer))
        return 1;
    frame_buffer_size = mode_info.XResolution * mode_info.YResolution * ((mode_info.BitsPerPixel + 7) / 8);
    if (DOUBLE_BUFFER)
    {
        secondary_frame_buffer = (uint8_t *)malloc(frame_buffer_size);
        drawing_frame_buffer = secondary_frame_buffer;
    }
    else
    {
        drawing_frame_buffer = main_frame_buffer;
    }
    return 0;
}

void clear_draw_buffer()
{
    memset(main_frame_buffer, 0xFFFFFF, mode_info.XResolution * mode_info.YResolution * ((mode_info.BitsPerPixel + 7) / 8));
}

// Double buffering
// Cópia para o frame buffer principal do frame construído desde a última atualização
// Otimizaçṍes:
// A) como o swap é uma operação muito frequente, é melhor não estar  a calcular frame_buffer_size sempre.
// Assim opta-se por uma variável global, que é constante ao longo da execução e calculada 1 vez na linha 30.
// Poupa-se (frequência * (2 multiplicações + 1 soma + 1 divisão)) operações por cada segundo.
// B) só vale a pena dar display do RTC quando passa um segundo
void swap_buffers()
{
    memcpy(main_frame_buffer, secondary_frame_buffer, frame_buffer_size);
    if (timer_interrupts % GAME_FREQUENCY == 0)
        display_real_time();
}

// A construção de um novo frame é baseado:
// - no estado atual do modelo (menuState, mouse_info, mode_info, buttonX->pressed...);
// - no Algoritmo do Pintor - https://pt.wikipedia.org/wiki/Algoritmo_do_pintor
// A ideia é colocar no buffer primeiro o plano mais longe do observador (a cor do fundo) e só depois
// os objetos em cima, no caso do cursor e / ou dos botões
void draw_new_frame()
{
    switch (menuState)
    {
    case START:
        draw_initial_menu();
        break;
    case GAME:
        draw_game_menu();
        break;
    case END:
        draw_finish_menu();
        break;
    case GAME_2:
        draw_game_menu_2();
        break;
    case MODE:
        draw_mode_menu();
        break;
    case GAME_3:
        draw_game_menu_3();
        break;
    case GAME_4_2:
        draw_game_menu_game_2();
        break;
    }

    draw_mouse();
}

void process_start_button()
{
    if (mouse_info.x >= mode_info.XResolution / 3 && mouse_info.x <= mode_info.XResolution / 3 + game->width && mouse_info.y >= mode_info.YResolution / 3 && mouse_info.y <= mode_info.YResolution / 3 + game->height)
    {
        draw_sprite_xpm(start, mode_info.XResolution / 3, mode_info.YResolution / 3);
        if (mouse_info.left_click)
        {
            menuState = MODE;
        }
    }
}

void process_quit_button()
{
    if (mouse_info.x >= mode_info.XResolution / 3 && mouse_info.x <= mode_info.XResolution / 3 + quit->width && mouse_info.y >= mode_info.YResolution / 2 && mouse_info.y <= mode_info.YResolution / 2 + quit->height)
    {
        draw_sprite_xpm(quit, mode_info.XResolution / 3, mode_info.YResolution / 2);
        if (mouse_info.left_click)
        {
            menuState = END;
        }
    }
}

// O menu inicial é apenas um retângulo com tamanho máximo, com um smile ao centro
void draw_initial_menu()
{
    memset(drawing_frame_buffer, 0xFFFFFF, frame_buffer_size);
    draw_sprite_xpm(logo, mode_info.XResolution / 3, 0);

    draw_sprite_xpm(start, mode_info.XResolution / 3, mode_info.YResolution / 3);
    process_start_button();

    draw_sprite_xpm(quit, mode_info.XResolution / 3, mode_info.YResolution / 2);
    process_quit_button();
}

void process_mode1()
{
    if (mouse_info.x >= mode_info.XResolution / 2 && mouse_info.x <= mode_info.XResolution / 2 + easy->width && mouse_info.y >= mode_info.YResolution / 4 && mouse_info.y <= mode_info.YResolution / 4 + easy->height)
    {
        draw_sprite_xpm(easy, mode_info.XResolution / 2, mode_info.YResolution / 4);
        if (mouse_info.left_click)
        {
            menuState = GAME;
            chosen = 1;
        }
    }
}
void process_mode2()
{
    if (mouse_info.x >= mode_info.XResolution / 2 && mouse_info.x <= mode_info.XResolution / 2 + medium->width && mouse_info.y >= mode_info.YResolution / 2 && mouse_info.y <= mode_info.YResolution / 2 + medium->height)
    {
        draw_sprite_xpm(medium, mode_info.XResolution / 2, mode_info.YResolution / 2);
        if (mouse_info.left_click)
        {
            menuState = GAME_2;
            chosen = 2;
        }
    }
}

void process_mode3()
{
    if (mouse_info.x >= mode_info.XResolution / 2 && mouse_info.x <= mode_info.XResolution / 2 + hard->width && mouse_info.y >= 3 * mode_info.YResolution / 4 && mouse_info.y <= 3 * mode_info.YResolution / 4 + hard->height)
    {
        draw_sprite_xpm(hard, mode_info.XResolution / 2, 3 * mode_info.YResolution / 4);
        if (mouse_info.left_click)
        {
            menuState = GAME_3;
        }
    }
}

void draw_mode_menu()
{
    memset(drawing_frame_buffer, 0x000000, frame_buffer_size);
    draw_sprite_xpm(easy, mode_info.XResolution / 2, mode_info.YResolution / 4);
    process_mode1();
    draw_sprite_xpm(medium, mode_info.XResolution / 2, mode_info.YResolution / 2);
    process_mode2();
    draw_sprite_xpm(hard, mode_info.XResolution / 2, 3 * mode_info.YResolution / 4);
    process_mode3();
}

bool button1Pressed = false;
bool button2Pressed = false;
bool button3Pressed = false;
bool button4Pressed = false;
bool auxiliar1Pressed = false;
bool auxiliar2Pressed = false;
int counter_cards = 0;
int random_index = 0;
int aux = 0;
int aux2 = 0;
int aux3 = 0;
int aux4 = 0;
int pre = 0;
int j = 0;
int k = 0;
Sprite matrix[2][2];
Sprite matrix2[2][4];
Sprite matrix3[4][4];
int id_sprite1;
int id_sprite2;
int id_sprite3;
int id_sprite4;
int final = 0;
bool block1 = false;
bool block2 = false;
bool block3 = false;
bool block4 = false;
bool player1 = true;
bool player2 = false;
int player_1 = 0;
int player_2 = 0;
// game_2
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
int pre1 = 0;
int prato = 0;
// game_3
int pre2 = 0;
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

int get_number(Sprite *cards, int size)
{

    int random_number = rand() % size;
    return random_number;
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
    matrix2[0][0] = cards[0];
    matrix2[0][1] = cards[1];
    matrix2[0][2] = cards[2];
    matrix2[0][3] = cards[3];
    matrix2[1][0] = cards[4];
    matrix2[1][1] = cards[5];
    matrix2[1][2] = cards[6];
    matrix2[1][3] = cards[7];

    // Printing the shuffled matrix
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", matrix2[i][j].id);
        }
        printf("\n");
    }
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
    matrix3[0][0] = cards[0];
    matrix3[0][1] = cards[1];
    matrix3[0][2] = cards[2];
    matrix3[0][3] = cards[3];
    matrix3[1][0] = cards[4];
    matrix3[1][1] = cards[5];
    matrix3[1][2] = cards[6];
    matrix3[1][3] = cards[7];
    matrix3[2][0] = cards[8];
    matrix3[2][1] = cards[9];
    matrix3[2][2] = cards[10];
    matrix3[2][3] = cards[11];
    matrix3[3][0] = cards[12];
    matrix3[3][1] = cards[13];
    matrix3[3][2] = cards[14];
    matrix3[3][3] = cards[15];

    // Printing the shuffled matrix
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", matrix3[i][j].id);
        }
        printf("\n");
    }
}

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

void process_button1(Sprite *cards, int size)
{
    if (button1->pressed)
    {
        button1Pressed = true;
        counter_cards++;
    }
    if (button1Pressed)
    {
        draw_sprite_xpm(&matrix[0][0], 0, 0);
        if (button2Pressed)
        {
            if (check_match(matrix[0][0].id, matrix[0][1].id))
            { // match entre o id 1 e o id 2;
                block1 = true;
                block2 = true;
                button1Pressed = false;
                button2Pressed = false;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player_1++;
                    }
                    else if (player2)
                    {
                        player_2++;
                    }
                }
            }
            else
            {
                button1Pressed = false;
                button2Pressed = false;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player1 = false;
                        player2 = true;
                    }
                    else if (player2)
                    {
                        player2 = false;
                        player1 = true;
                    }
                }
                counter_cards = 0;
            }
        }
        if (button3Pressed)
        {
            if (check_match(matrix[0][0].id, matrix[1][0].id))
            {
                block1 = true;
                block3 = true;
                button1Pressed = false;
                button3Pressed = false;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player_1++;
                    }
                    else if (player2)
                    {
                        player_2++;
                    }
                }
            }
            else
            {
                button1Pressed = false;
                button3Pressed = false;
                counter_cards = 0;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player1 = false;
                        player2 = true;
                    }
                    else if (player2)
                    {
                        player2 = false;
                        player1 = true;
                    }
                }
            }
        }
        if (button4Pressed)
        {
            if (check_match(matrix[0][0].id, matrix[1][1].id))
            {
                block1 = true;
                block4 = true;
                button1Pressed = false;
                button4Pressed = false;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player_1++;
                    }
                    else if (player2)
                    {
                        player_2++;
                    }
                }
            }
            else
            {
                button1Pressed = false;
                button4Pressed = false;
                counter_cards = 0;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player1 = false;
                        player2 = true;
                    }
                    else if (player2)
                    {
                        player2 = false;
                        player1 = true;
                    }
                }
            }
        }
    }
}
void process_button2(Sprite *cards, int size)
{
    if (button2->pressed)
    {
        button2Pressed = true;
        counter_cards++;
    }

    if (button2Pressed)
    {
        draw_sprite_xpm(&matrix[0][1], mode_info.XResolution / 2, 0);
        if (button1Pressed)
        {
            if (check_match(matrix[0][0].id, matrix[0][1].id))
            { // match entre o id 1 e o id 2;
                block1 = true;
                block2 = true;
                button1Pressed = false;
                button2Pressed = false;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player_1++;
                    }
                    else if (player2)
                    {
                        player_2++;
                    }
                }
            }
            else
            {
                button1Pressed = false;
                button2Pressed = false;
                counter_cards = 0;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player1 = false;
                        player2 = true;
                    }
                    else if (player2)
                    {
                        player2 = false;
                        player1 = true;
                    }
                }
            }
        }
        if (button3Pressed)
        {
            if (check_match(matrix[0][1].id, matrix[1][0].id))
            {
                block2 = true;
                block3 = true;
                button2Pressed = false;
                button3Pressed = false;
                final++;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player_1++;
                    }
                    else if (player2)
                    {
                        player_2++;
                    }
                }
            }
            else
            {
                button2Pressed = false;
                button3Pressed = false;
                counter_cards = 0;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player1 = false;
                        player2 = true;
                    }
                    else if (player2)
                    {
                        player2 = false;
                        player1 = true;
                    }
                }
            }
        }
        if (button4Pressed)
        {
            if (check_match(matrix[0][1].id, matrix[1][1].id))
            {
                block2 = true;
                block4 = true;
                button2Pressed = false;
                button4Pressed = false;
                final++;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player_1++;
                    }
                    else if (player2)
                    {
                        player_2++;
                    }
                }
            }
            else
            {
                button2Pressed = false;
                button4Pressed = false;
                counter_cards = 0;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player1 = false;
                        player2 = true;
                    }
                    else if (player2)
                    {
                        player2 = false;
                        player1 = true;
                    }
                }
            }
        }
    }
}

void process_button3(Sprite *cards, int size)
{
    if (button3->pressed)
    {
        button3Pressed = true;
        counter_cards++;
    }

    if (button3Pressed)
    {
        draw_sprite_xpm(&matrix[1][0], 0, mode_info.YResolution / 2);
        if (button1Pressed)
        {
            if (check_match(matrix[0][0].id, matrix[1][0].id))
            { // match entre o id 1 e o id 2;
                block1 = true;
                block3 = true;
                button1Pressed = false;
                button3Pressed = false;
                final++;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player_1++;
                    }
                    else if (player2)
                    {
                        player_2++;
                    }
                }
            }
            else
            {
                button1Pressed = false;
                button3Pressed = false;
                counter_cards = 0;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player1 = false;
                        player2 = true;
                    }
                    else if (player2)
                    {
                        player2 = false;
                        player1 = true;
                    }
                }
            }
        }
        if (button2Pressed)
        {
            if (check_match(matrix[0][1].id, matrix[1][0].id))
            {
                block2 = true;
                block3 = true;
                button2Pressed = false;
                button3Pressed = false;
                final++;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player_1++;
                    }
                    else if (player2)
                    {
                        player_2++;
                    }
                }
            }
            else
            {
                button2Pressed = false;
                button3Pressed = false;
                counter_cards = 0;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player1 = false;
                        player2 = true;
                    }
                    else if (player2)
                    {
                        player2 = false;
                        player1 = true;
                    }
                }
            }
        }
        if (button4Pressed)
        {
            if (check_match(matrix[1][0].id, matrix[1][1].id))
            {
                block3 = true;
                block4 = true;
                final++;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player_1++;
                    }
                    else if (player2)
                    {
                        player_2++;
                    }
                }
            }

            else
            {
                button3Pressed = false;
                button4Pressed = false;
                counter_cards = 0;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player1 = false;
                        player2 = true;
                    }
                    else if (player2)
                    {
                        player2 = false;
                        player1 = true;
                    }
                }
            }
        }
    }
}

void process_button4(Sprite *cards, int size)
{
    if (button4->pressed)
    {
        button4Pressed = true;
        counter_cards++;
    }

    if (button4Pressed)
    {
        draw_sprite_xpm(&matrix[1][1], mode_info.XResolution / 2, mode_info.YResolution / 2);
        if (button1Pressed)
        {
            if (check_match(matrix[0][0].id, matrix[1][1].id))
            { // match entre o id 1 e o id 2;
                block1 = true;
                block4 = true;
                button1Pressed = false;
                button4Pressed = false;
                final++;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player_1++;
                    }
                    else if (player2)
                    {
                        player_2++;
                    }
                }
            }
            else
            {
                button1Pressed = false;
                button4Pressed = false;
                counter_cards = 0;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player1 = false;
                        player2 = true;
                    }
                    else if (player2)
                    {
                        player2 = false;
                        player1 = true;
                    }
                }
            }
        }
        if (button2Pressed)
        {
            if (check_match(matrix[0][1].id, matrix[1][1].id))
            {
                block2 = true;
                block4 = true;
                button2Pressed = false;
                button4Pressed = false;
                final++;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player_1++;
                    }
                    else if (player2)
                    {
                        player_2++;
                    }
                }
            }
            else
            {
                button2Pressed = false;
                button4Pressed = false;
                counter_cards = 0;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player1 = false;
                        player2 = true;
                    }
                    else if (player2)
                    {
                        player2 = false;
                        player1 = true;
                    }
                }
            }
        }
        if (button3Pressed)
        {
            if (check_match(matrix[1][0].id, matrix[1][1].id))
            {
                block3 = true;
                block4 = true;
                button3Pressed = false;
                button4Pressed = false;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player_1++;
                    }
                    else if (player2)
                    {
                        player_2++;
                    }
                }
            }
            else
            {
                button3Pressed = false;
                button4Pressed = false;
                counter_cards = 0;
                if (menuState == GAME_4_2)
                {
                    if (player1)
                    {
                        player1 = false;
                        player2 = true;
                    }
                    else if (player2)
                    {
                        player2 = false;
                        player1 = true;
                    }
                }
            }
        }
    }
}

// O menu do jogo é constituído por quatro botões
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
        shuffle(cards, j);
        pre++;
    }

    memset(drawing_frame_buffer, 0, mode_info.XResolution * mode_info.YResolution * mode_info.BitsPerPixel / 8);
    draw_sprite_xpm(back1, 0, 0);
    draw_sprite_xpm(back2, mode_info.XResolution / 2, 0);
    draw_sprite_xpm(back3, 0, mode_info.YResolution / 2);
    draw_sprite_xpm(back4, mode_info.XResolution / 2, mode_info.YResolution / 2);

    if (!block1)
    {
        process_button1(cards, j);
        printf("player1: %d\n", player1);
        printf("player2: %d\n", player2);
    }
    else if (block1)
    {
        draw_sprite_xpm(&matrix[0][0], 0, 0);
        printf("player1: %d\n", player1);
        printf("player2: %d\n", player2);
    }
    if (!block2)
    {
        process_button2(cards, j);
        printf("player1: %d\n", player1);
        printf("player2: %d\n", player2);
    }
    else if (block2)
    {
        draw_sprite_xpm(&matrix[0][1], mode_info.XResolution / 2, 0);
        printf("player1: %d\n", player1);
        printf("player2: %d\n", player2);
    }
    if (!block3)
    {
        process_button3(cards, j);
        printf("player1: %d\n", player1);
        printf("player2: %d\n", player2);
    }
    else if (block3)
    {
        draw_sprite_xpm(&matrix[1][0], 0, mode_info.YResolution / 2);
    }
    if (!block4)
    {
        process_button4(cards, j);
    }
    else if (block4)
    {
        draw_sprite_xpm(&matrix[1][1], mode_info.XResolution / 2, mode_info.YResolution / 2);
    }
    if (block1 && block2 && block3 && block4)
    {
        printf("player1: %d\n", player_1);
        printf("player2: %d\n", player_2);
        menuState = END;
    }
}

void draw_game_menu_game_2()
{
    Sprite *back1 = back;
    Sprite *back2 = back;
    Sprite *back3 = back;
    Sprite *back4 = back;
    Sprite cards[] = {*number1, *number1, *number2, *number2};
    int j = sizeof(cards) / sizeof(cards[0]);
    if (pre == 0)
    {
        shuffle(cards, j);
        pre++;
    }

    memset(drawing_frame_buffer, 0, mode_info.XResolution * mode_info.YResolution * mode_info.BitsPerPixel / 8);
    draw_sprite_xpm(back1, 0, 0);
    draw_sprite_xpm(back2, mode_info.XResolution / 2, 0);
    draw_sprite_xpm(back3, 0, mode_info.YResolution / 2);
    draw_sprite_xpm(back4, mode_info.XResolution / 2, mode_info.YResolution / 2);

    if (!block1)
    {
        process_button1(cards, j);
        printf("player1: %d\n", player1);
        printf("player2: %d\n", player2);
    }
    else if (block1)
    {
        draw_sprite_xpm(&matrix[0][0], 0, 0);
        printf("player1: %d\n", player1);
        printf("player2: %d\n", player2);
    }
    if (!block2)
    {
        process_button2(cards, j);
        printf("player1: %d\n", player1);
        printf("player2: %d\n", player2);
    }
    else if (block2)
    {
        draw_sprite_xpm(&matrix[0][1], mode_info.XResolution / 2, 0);
        printf("player1: %d\n", player1);
        printf("player2: %d\n", player2);
    }
    if (!block3)
    {
        process_button3(cards, j);
        printf("player1: %d\n", player1);
        printf("player2: %d\n", player2);
    }
    else if (block3)
    {
        draw_sprite_xpm(&matrix[1][0], 0, mode_info.YResolution / 2);
    }
    if (!block4)
    {
        process_button4(cards, j);
    }
    else if (block4)
    {
        draw_sprite_xpm(&matrix[1][1], mode_info.XResolution / 2, mode_info.YResolution / 2);
    }
    if (block1 && block2 && block3 && block4)
    {
        printf("The value of l is: %d\n", player_1);
        printf("The value of l is: %d\n", player_2);
        menuState = END;
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
        draw_sprite_xpm(&matrix2[0][0], 0, 0);
        if (cardPressed2)
        {
            if (check_match(matrix2[0][0].id, matrix2[0][1].id))
            {
                cardBlock1 = true;
                cardBlock2 = true;
                cardPressed1 = false;
                cardPressed2 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed1 = false;
                cardPressed2 = false;
                printf("ERROU");
            }
        }
        if (cardPressed3)
        {
            if (check_match(matrix2[0][0].id, matrix2[0][2].id))
            {
                cardBlock1 = true;
                cardBlock3 = true;
                cardPressed1 = false;
                cardPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed1 = false;
                cardPressed3 = false;
                printf("ERROU");
            }
        }
        if (cardPressed4)
        {
            if (check_match(matrix2[0][0].id, matrix2[0][3].id))
            {
                cardBlock1 = true;
                cardBlock4 = true;
                cardPressed1 = false;
                cardPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed1 = false;
                cardPressed4 = false;
                printf("ERROU");
            }
        }
        if (cardPressed5)
        {
            if (check_match(matrix2[0][0].id, matrix2[1][0].id))
            {
                cardBlock1 = true;
                cardBlock5 = true;
                cardPressed1 = false;
                cardPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed1 = false;
                cardPressed5 = false;
                printf("ERROU");
            }
        }
        if (cardPressed6)
        {
            if (check_match(matrix2[0][0].id, matrix2[1][1].id))
            {
                cardBlock1 = true;
                cardBlock6 = true;
                cardPressed1 = false;
                cardPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed1 = false;
                cardPressed6 = false;
                printf("ERROU");
            }
        }
        if (cardPressed7)
        {
            if (check_match(matrix2[0][0].id, matrix2[1][2].id))
            {
                cardBlock1 = true;
                cardBlock7 = true;
                cardPressed1 = false;
                cardPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed1 = false;
                cardPressed7 = false;
                printf("ERROU");
            }
        }
        if (cardPressed8)
        {
            if (check_match(matrix2[0][0].id, matrix2[1][3].id))
            {
                cardBlock1 = true;
                cardBlock8 = true;
                cardPressed1 = false;
                cardPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed1 = false;
                cardPressed8 = false;
                printf("ERROU");
            }
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

        draw_sprite_xpm(&matrix2[0][1], mode_info.XResolution / 4, 0);
        if (cardPressed1)
        {
            if (check_match(matrix2[0][1].id, matrix2[0][0].id))
            {
                cardBlock1 = true;
                cardBlock2 = true;
                cardPressed1 = false;
                cardPressed2 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed1 = false;
                cardPressed2 = false;
                printf("ERROU");
            }
        }
        if (cardPressed3)
        {
            if (check_match(matrix2[0][1].id, matrix2[0][2].id))
            {
                cardBlock2 = true;
                cardBlock3 = true;
                cardPressed2 = false;
                cardPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed2 = false;
                cardPressed3 = false;
                printf("ERROU");
            }
        }
        if (cardPressed4)
        {
            if (check_match(matrix2[0][1].id, matrix2[0][3].id))
            {
                cardBlock2 = true;
                cardBlock4 = true;
                cardPressed2 = false;
                cardPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed2 = false;
                cardPressed4 = false;
                printf("ERROU");
            }
        }
        if (cardPressed5)
        {
            if (check_match(matrix2[0][1].id, matrix2[1][0].id))
            {
                cardBlock2 = true;
                cardBlock5 = true;
                cardPressed2 = false;
                cardPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed2 = false;
                cardPressed5 = false;
                printf("ERROU");
            }
        }
        if (cardPressed6)
        {
            if (check_match(matrix2[0][1].id, matrix2[1][1].id))
            {
                cardBlock2 = true;
                cardBlock6 = true;
                cardPressed2 = false;
                cardPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed2 = false;
                cardPressed6 = false;
                printf("ERROU");
            }
        }
        if (cardPressed7)
        {
            if (check_match(matrix2[0][1].id, matrix2[1][2].id))
            {
                cardBlock2 = true;
                cardBlock7 = true;
                cardPressed2 = false;
                cardPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed2 = false;
                cardPressed7 = false;
                printf("ERROU");
            }
        }
        if (cardPressed8)
        {
            if (check_match(matrix2[0][1].id, matrix2[1][3].id))
            {
                cardBlock2 = true;
                cardBlock8 = true;
                cardPressed2 = false;
                cardPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed2 = false;
                cardPressed8 = false;
                printf("ERROU");
            }
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

        draw_sprite_xpm(&matrix2[0][2], mode_info.XResolution / 2, 0);
        if (cardPressed1)
        {
            if (check_match(matrix2[0][2].id, matrix2[0][0].id))
            {
                cardBlock1 = true;
                cardBlock3 = true;
                cardPressed1 = false;
                cardPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed1 = false;
                cardPressed3 = false;
                printf("ERROU");
            }
        }
        if (cardPressed2)
        {
            if (check_match(matrix2[0][2].id, matrix2[0][1].id))
            {
                cardBlock2 = true;
                cardBlock3 = true;
                cardPressed2 = false;
                cardPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed2 = false;
                cardPressed3 = false;
                printf("ERROU");
            }
        }
        if (cardPressed4)
        {
            if (check_match(matrix2[0][2].id, matrix2[0][3].id))
            {
                cardBlock3 = true;
                cardBlock4 = true;
                cardPressed3 = false;
                cardPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed3 = false;
                cardPressed4 = false;
                printf("ERROU");
            }
        }
        if (cardPressed5)
        {
            if (check_match(matrix2[0][2].id, matrix2[1][0].id))
            {
                cardBlock3 = true;
                cardBlock5 = true;
                cardPressed3 = false;
                cardPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed3 = false;
                cardPressed5 = false;
                printf("ERROU");
            }
        }
        if (cardPressed6)
        {
            if (check_match(matrix2[0][2].id, matrix2[1][1].id))
            {
                cardBlock3 = true;
                cardBlock6 = true;
                cardPressed3 = false;
                cardPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed3 = false;
                cardPressed6 = false;
                printf("ERROU");
            }
        }
        if (cardPressed7)
        {
            if (check_match(matrix2[0][2].id, matrix2[1][2].id))
            {
                cardBlock3 = true;
                cardBlock7 = true;
                cardPressed3 = false;
                cardPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed3 = false;
                cardPressed7 = false;
                printf("ERROU");
            }
        }
        if (cardPressed8)
        {
            if (check_match(matrix2[0][2].id, matrix2[1][3].id))
            {
                cardBlock3 = true;
                cardBlock8 = true;
                cardPressed3 = false;
                cardPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed3 = false;
                cardPressed8 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix2[0][3], 3 * mode_info.XResolution / 4, 0);
        if (cardPressed1)
        {
            if (check_match(matrix2[0][3].id, matrix2[0][0].id))
            {
                cardBlock1 = true;
                cardBlock4 = true;
                cardPressed1 = false;
                cardPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed1 = false;
                cardPressed4 = false;
                printf("ERROU");
            }
        }
        if (cardPressed2)
        {
            if (check_match(matrix2[0][3].id, matrix2[0][1].id))
            {
                cardBlock2 = true;
                cardBlock4 = true;
                cardPressed2 = false;
                cardPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed2 = false;
                cardPressed4 = false;
                printf("ERROU");
            }
        }
        if (cardPressed3)
        {
            if (check_match(matrix2[0][3].id, matrix2[0][2].id))
            {
                cardBlock3 = true;
                cardBlock4 = true;
                cardPressed3 = false;
                cardPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed4 = false;
                cardPressed3 = false;
                printf("ERROU");
            }
        }
        if (cardPressed5)
        {
            if (check_match(matrix2[0][3].id, matrix2[1][0].id))
            {
                cardBlock4 = true;
                cardBlock5 = true;
                cardPressed4 = false;
                cardPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed4 = false;
                cardPressed5 = false;
                printf("ERROU");
            }
        }
        if (cardPressed6)
        {
            if (check_match(matrix2[0][3].id, matrix2[1][1].id))
            {
                cardBlock4 = true;
                cardBlock6 = true;
                cardPressed4 = false;
                cardPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed4 = false;
                cardPressed6 = false;
                printf("ERROU");
            }
        }
        if (cardPressed7)
        {
            if (check_match(matrix2[0][3].id, matrix2[1][2].id))
            {
                cardBlock4 = true;
                cardBlock7 = true;
                cardPressed4 = false;
                cardPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed4 = false;
                cardPressed7 = false;
                printf("ERROU");
            }
        }
        if (cardPressed8)
        {
            if (check_match(matrix2[0][3].id, matrix2[1][3].id))
            {
                cardBlock4 = true;
                cardBlock8 = true;
                cardPressed4 = false;
                cardPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed4 = false;
                cardPressed8 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix2[1][0], 0, mode_info.YResolution / 2);
        if (cardPressed1)
        {
            if (check_match(matrix2[1][0].id, matrix2[0][0].id))
            {
                cardBlock1 = true;
                cardBlock5 = true;
                cardPressed1 = false;
                cardPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed1 = false;
                cardPressed5 = false;
                printf("ERROU");
            }
        }
        if (cardPressed2)
        {
            if (check_match(matrix2[1][0].id, matrix2[0][1].id))
            {
                cardBlock2 = true;
                cardBlock5 = true;
                cardPressed2 = false;
                cardPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed2 = false;
                cardPressed5 = false;
                printf("ERROU");
            }
        }
        if (cardPressed3)
        {
            if (check_match(matrix2[1][0].id, matrix2[0][2].id))
            {
                cardBlock3 = true;
                cardBlock5 = true;
                cardPressed3 = false;
                cardPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed3 = false;
                cardPressed5 = false;
                printf("ERROU");
            }
        }
        if (cardPressed4)
        {
            if (check_match(matrix2[1][0].id, matrix2[0][3].id))
            {
                cardBlock4 = true;
                cardBlock5 = true;
                cardPressed4 = false;
                cardPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed5 = false;
                cardPressed4 = false;
                printf("ERROU");
            }
        }
        if (cardPressed6)
        {
            if (check_match(matrix2[1][0].id, matrix2[1][1].id))
            {
                cardBlock5 = true;
                cardBlock6 = true;
                cardPressed5 = false;
                cardPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed5 = false;
                cardPressed6 = false;
                printf("ERROU");
            }
        }
        if (cardPressed7)
        {
            if (check_match(matrix2[1][0].id, matrix2[1][2].id))
            {
                cardBlock5 = true;
                cardBlock7 = true;
                cardPressed5 = false;
                cardPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed5 = false;
                cardPressed7 = false;
                printf("ERROU");
            }
        }
        if (cardPressed8)
        {
            if (check_match(matrix2[1][0].id, matrix2[1][3].id))
            {
                cardBlock5 = true;
                cardBlock8 = true;
                cardPressed5 = false;
                cardPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed5 = false;
                cardPressed8 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix2[1][1], mode_info.XResolution / 4, mode_info.YResolution / 2);
        if (cardPressed1)
        {
            if (check_match(matrix2[1][1].id, matrix2[0][0].id))
            {
                cardBlock1 = true;
                cardBlock6 = true;
                cardPressed1 = false;
                cardPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed1 = false;
                cardPressed6 = false;
                printf("ERROU");
            }
        }
        if (cardPressed2)
        {
            if (check_match(matrix2[1][1].id, matrix2[0][1].id))
            {
                cardBlock2 = true;
                cardBlock6 = true;
                cardPressed2 = false;
                cardPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed2 = false;
                cardPressed6 = false;
                printf("ERROU");
            }
        }
        if (cardPressed3)
        {
            if (check_match(matrix2[1][1].id, matrix2[0][2].id))
            {
                cardBlock3 = true;
                cardBlock6 = true;
                cardPressed3 = false;
                cardPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed3 = false;
                cardPressed6 = false;
                printf("ERROU");
            }
        }
        if (cardPressed4)
        {
            if (check_match(matrix2[1][1].id, matrix2[0][3].id))
            {
                cardBlock4 = true;
                cardBlock6 = true;
                cardPressed4 = false;
                cardPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed4 = false;
                cardPressed6 = false;
                printf("ERROU");
            }
        }
        if (cardPressed5)
        {
            if (check_match(matrix2[1][1].id, matrix2[1][0].id))
            {
                cardBlock5 = true;
                cardBlock6 = true;
                cardPressed5 = false;
                cardPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed5 = false;
                cardPressed6 = false;
                printf("ERROU");
            }
        }
        if (cardPressed7)
        {
            if (check_match(matrix2[1][1].id, matrix2[1][2].id))
            {
                cardBlock6 = true;
                cardBlock7 = true;
                cardPressed6 = false;
                cardPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed7 = false;
                cardPressed6 = false;
                printf("ERROU");
            }
        }
        if (cardPressed8)
        {
            if (check_match(matrix2[1][1].id, matrix2[1][3].id))
            {
                cardBlock6 = true;
                cardBlock8 = true;
                cardPressed6 = false;
                cardPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed6 = false;
                cardPressed8 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix2[1][2], mode_info.XResolution / 2, mode_info.YResolution / 2);
        if (cardPressed1)
        {
            if (check_match(matrix2[1][2].id, matrix2[0][0].id))
            {
                cardBlock1 = true;
                cardBlock7 = true;
                cardPressed1 = false;
                cardPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed1 = false;
                cardPressed7 = false;
                printf("ERROU");
            }
        }
        if (cardPressed2)
        {
            if (check_match(matrix2[1][2].id, matrix2[0][1].id))
            {
                cardBlock2 = true;
                cardBlock7 = true;
                cardPressed2 = false;
                cardPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed2 = false;
                cardPressed7 = false;
                printf("ERROU");
            }
        }
        if (cardPressed3)
        {
            if (check_match(matrix2[1][2].id, matrix2[0][2].id))
            {
                cardBlock3 = true;
                cardBlock7 = true;
                cardPressed3 = false;
                cardPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed3 = false;
                cardPressed7 = false;
                printf("ERROU");
            }
        }
        if (cardPressed4)
        {
            if (check_match(matrix2[1][2].id, matrix2[0][3].id))
            {
                cardBlock4 = true;
                cardBlock7 = true;
                cardPressed4 = false;
                cardPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed4 = false;
                cardPressed7 = false;
                printf("ERROU");
            }
        }
        if (cardPressed5)
        {
            if (check_match(matrix2[1][2].id, matrix2[1][0].id))
            {
                cardBlock5 = true;
                cardBlock7 = true;
                cardPressed5 = false;
                cardPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed5 = false;
                cardPressed7 = false;
                printf("ERROU");
            }
        }
        if (cardPressed6)
        {
            if (check_match(matrix2[1][2].id, matrix2[1][1].id))
            {
                cardBlock6 = true;
                cardBlock7 = true;
                cardPressed6 = false;
                cardPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed6 = false;
                cardPressed7 = false;
                printf("ERROU");
            }
        }
        if (cardPressed8)
        {
            if (check_match(matrix2[1][2].id, matrix2[1][3].id))
            {
                cardBlock7 = true;
                cardBlock8 = true;
                cardPressed7 = false;
                cardPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed8 = false;
                cardPressed7 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix2[1][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 2);
        if (cardPressed1)
        {
            if (check_match(matrix2[1][3].id, matrix2[0][0].id))
            {
                cardBlock1 = true;
                cardBlock8 = true;
                cardPressed1 = false;
                cardPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed1 = false;
                cardPressed8 = false;
                printf("ERROU");
            }
        }
        if (cardPressed2)
        {
            if (check_match(matrix2[1][3].id, matrix2[0][1].id))
            {
                cardBlock2 = true;
                cardBlock8 = true;
                cardPressed2 = false;
                cardPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed2 = false;
                cardPressed8 = false;
                printf("ERROU");
            }
        }
        if (cardPressed3)
        {
            if (check_match(matrix2[1][3].id, matrix2[0][2].id))
            {
                cardBlock3 = true;
                cardBlock8 = true;
                cardPressed3 = false;
                cardPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed3 = false;
                cardPressed8 = false;
                printf("ERROU");
            }
        }
        if (cardPressed4)
        {
            if (check_match(matrix2[1][3].id, matrix2[0][3].id))
            {
                cardBlock4 = true;
                cardBlock8 = true;
                cardPressed4 = false;
                cardPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed4 = false;
                cardPressed8 = false;
                printf("ERROU");
            }
        }
        if (cardPressed5)
        {
            if (check_match(matrix2[1][3].id, matrix2[1][0].id))
            {
                cardBlock5 = true;
                cardBlock8 = true;
                cardPressed5 = false;
                cardPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed5 = false;
                cardPressed8 = false;
                printf("ERROU");
            }
        }
        if (cardPressed6)
        {
            if (check_match(matrix2[1][3].id, matrix2[1][1].id))
            {
                cardBlock6 = true;
                cardBlock8 = true;
                cardPressed6 = false;
                cardPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed6 = false;
                cardPressed8 = false;
                printf("ERROU");
            }
        }
        if (cardPressed7)
        {
            if (check_match(matrix2[1][3].id, matrix2[1][2].id))
            {
                cardBlock7 = true;
                cardBlock8 = true;
                cardPressed7 = false;
                cardPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                cardPressed7 = false;
                cardPressed8 = false;
                printf("ERROU");
            }
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
    if (!cardBlock1)
    {
        process_cardPressed1();
    }
    else if (cardBlock1)
    {
        draw_sprite_xpm(&matrix2[0][0], 0, 0);
    }
    if (!cardBlock2)
    {
        process_cardPressed2();
    }
    else if (cardBlock2)
    {
        draw_sprite_xpm(&matrix2[0][1], mode_info.XResolution / 4, 0);
    }
    if (!cardBlock3)
    {
        process_cardPressed3();
    }
    else if (cardBlock3)
    {
        draw_sprite_xpm(&matrix2[0][2], mode_info.XResolution / 2, 0);
    }
    if (!cardBlock4)
    {
        process_cardPressed4();
    }
    else if (cardBlock4)
    {
        draw_sprite_xpm(&matrix2[0][3], 3 * mode_info.XResolution / 4, 0);
    }
    if (!cardBlock5)
    {
        process_cardPressed5();
    }
    else if (cardBlock5)
    {
        draw_sprite_xpm(&matrix2[1][0], 0, mode_info.YResolution / 2);
    }
    if (!cardBlock6)
    {
        process_cardPressed6();
    }
    else if (cardBlock6)
    {
        draw_sprite_xpm(&matrix2[1][1], mode_info.XResolution / 4, mode_info.YResolution / 2);
    }
    if (!cardBlock7)
    {
        process_cardPressed7();
    }
    else if (cardBlock7)
    {
        draw_sprite_xpm(&matrix2[1][2], mode_info.XResolution / 2, mode_info.YResolution / 2);
    }
    if (!cardBlock8)
    {
        process_cardPressed8();
    }
    else if (cardBlock8)
    {
        draw_sprite_xpm(&matrix2[1][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 2);
    }
    if (cardBlock1 && cardBlock2 && cardBlock3 && cardBlock4 && cardBlock5 && cardBlock6 && cardBlock7 && cardBlock8)
    {
        draw_finish_menu();
        menuState = END;
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
        draw_sprite_xpm(&matrix3[0][0], 0, 0);
        if (backPressed2)
        {
            if (check_match(matrix3[0][0].id, matrix3[0][1].id))
            {
                backBlock1 = true;
                backBlock2 = true;
                backPressed1 = false;
                backPressed2 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed2 = false;
                printf("ERROU");
            }
        }
        if (backPressed3)
        {
            if (check_match(matrix3[0][0].id, matrix3[0][2].id))
            {
                backBlock1 = true;
                backBlock3 = true;
                backPressed1 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed4)
        {
            if (check_match(matrix3[0][0].id, matrix3[0][3].id))
            {
                backBlock1 = true;
                backBlock4 = true;
                backPressed1 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed5)
        {
            if (check_match(matrix3[0][0].id, matrix3[1][0].id))
            {
                backBlock1 = true;
                backBlock5 = true;
                backPressed1 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed6)
        {
            if (check_match(matrix3[0][0].id, matrix3[1][1].id))
            {
                backBlock1 = true;
                backBlock6 = true;
                backPressed1 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed7)
        {
            if (check_match(matrix3[0][0].id, matrix3[1][2].id))
            {
                backBlock1 = true;
                backBlock7 = true;
                backPressed1 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed8)
        {
            if (check_match(matrix3[0][0].id, matrix3[1][3].id))
            {
                backBlock1 = true;
                backBlock8 = true;
                backPressed1 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed9)
        {
            if (check_match(matrix3[0][0].id, matrix3[2][0].id))
            {
                backBlock1 = true;
                backBlock9 = true;
                backPressed1 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed10)
        {
            if (check_match(matrix3[0][0].id, matrix3[2][1].id))
            {
                backBlock1 = true;
                backBlock10 = true;
                backPressed1 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed11)
        {
            if (check_match(matrix3[0][0].id, matrix3[2][2].id))
            {
                backBlock1 = true;
                backBlock11 = true;
                backPressed1 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed12)
        {
            if (check_match(matrix3[0][0].id, matrix3[2][3].id))
            {
                backBlock1 = true;
                backBlock12 = true;
                backPressed1 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed13)
        {
            if (check_match(matrix3[0][0].id, matrix3[3][0].id))
            {
                backBlock1 = true;
                backBlock13 = true;
                backPressed1 = false;
                backPressed13 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed14)
        {
            if (check_match(matrix3[0][0].id, matrix3[3][1].id))
            {
                backBlock1 = true;
                backBlock14 = true;
                backPressed1 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed15)
        {
            if (check_match(matrix3[0][0].id, matrix3[3][2].id))
            {
                backBlock1 = true;
                backBlock15 = true;
                backPressed1 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed16)
        {
            if (check_match(matrix3[0][0].id, matrix3[3][3].id))
            {
                backBlock1 = true;
                backBlock16 = true;
                backPressed1 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed16 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix3[0][1], mode_info.XResolution / 4, 0);
        if (backPressed1)
        {
            if (check_match(matrix3[0][1].id, matrix3[0][0].id))
            {
                backBlock1 = true;
                backBlock2 = true;
                backPressed1 = false;
                backPressed2 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed2 = false;
                printf("ERROU");
            }
        }
        if (backPressed3)
        {
            if (check_match(matrix3[0][1].id, matrix3[0][2].id))
            {
                backBlock2 = true;
                backBlock3 = true;
                backPressed2 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed4)
        {
            if (check_match(matrix3[0][1].id, matrix3[0][3].id))
            {
                backBlock2 = true;
                backBlock4 = true;
                backPressed2 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed5)
        {
            if (check_match(matrix3[0][1].id, matrix3[1][0].id))
            {
                backBlock2 = true;
                backBlock5 = true;
                backPressed2 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed6)
        {
            if (check_match(matrix3[0][1].id, matrix3[1][1].id))
            {
                backBlock2 = true;
                backBlock6 = true;
                backPressed2 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed7)
        {
            if (check_match(matrix3[0][1].id, matrix3[1][2].id))
            {
                backBlock2 = true;
                backBlock7 = true;
                backPressed2 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed8)
        {
            if (check_match(matrix3[0][1].id, matrix3[1][3].id))
            {
                backBlock2 = true;
                backBlock8 = true;
                backPressed2 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed9)
        {
            if (check_match(matrix3[0][1].id, matrix3[2][0].id))
            {
                backBlock2 = true;
                backBlock9 = true;
                backPressed2 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed10)
        {
            if (check_match(matrix3[0][1].id, matrix3[2][1].id))
            {
                backBlock2 = true;
                backBlock10 = true;
                backPressed2 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed11)
        {
            if (check_match(matrix3[0][1].id, matrix3[2][2].id))
            {
                backBlock2 = true;
                backBlock11 = true;
                backPressed2 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed12)
        {
            if (check_match(matrix3[0][1].id, matrix3[2][3].id))
            {
                backBlock2 = true;
                backBlock12 = true;
                backPressed2 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed13)
        {
            if (check_match(matrix3[0][1].id, matrix3[3][0].id))
            {
                backBlock2 = true;
                backBlock13 = true;
                backPressed2 = false;
                backPressed13 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed14)
        {
            if (check_match(matrix3[0][1].id, matrix3[3][1].id))
            {
                backBlock2 = true;
                backBlock14 = true;
                backPressed2 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed15)
        {
            if (check_match(matrix3[0][1].id, matrix3[3][2].id))
            {
                backBlock2 = true;
                backBlock15 = true;
                backPressed2 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed16)
        {
            if (check_match(matrix3[0][1].id, matrix3[3][3].id))
            {
                backBlock2 = true;
                backBlock16 = true;
                backPressed2 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed16 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix3[0][2], mode_info.XResolution / 2, 0);
        if (backPressed1)
        {
            if (check_match(matrix3[0][2].id, matrix3[0][0].id))
            {
                backBlock1 = true;
                backBlock3 = true;
                backPressed1 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed2)
        {
            if (check_match(matrix3[0][2].id, matrix3[0][1].id))
            {
                backBlock2 = true;
                backBlock3 = true;
                backPressed2 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed4)
        {
            if (check_match(matrix3[0][2].id, matrix3[0][3].id))
            {
                backBlock4 = true;
                backBlock3 = true;
                backPressed4 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed4 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed5)
        {
            if (check_match(matrix3[0][2].id, matrix3[1][0].id))
            {
                backBlock5 = true;
                backBlock3 = true;
                backPressed5 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed5 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed6)
        {
            if (check_match(matrix3[0][2].id, matrix3[1][1].id))
            {
                backBlock6 = true;
                backBlock3 = true;
                backPressed6 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed6 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed7)
        {
            if (check_match(matrix3[0][2].id, matrix3[1][2].id))
            {
                backBlock7 = true;
                backBlock3 = true;
                backPressed7 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed7 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed8)
        {
            if (check_match(matrix3[0][2].id, matrix3[1][3].id))
            {
                backBlock8 = true;
                backBlock3 = true;
                backPressed8 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed8 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed9)
        {
            if (check_match(matrix3[0][2].id, matrix3[2][0].id))
            {
                backBlock9 = true;
                backBlock3 = true;
                backPressed9 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed9 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed10)
        {
            if (check_match(matrix3[0][2].id, matrix3[2][1].id))
            {
                backBlock10 = true;
                backBlock3 = true;
                backPressed10 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed10 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed11)
        {
            if (check_match(matrix3[0][2].id, matrix3[2][2].id))
            {
                backBlock11 = true;
                backBlock3 = true;
                backPressed11 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed11 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed12)
        {
            if (check_match(matrix3[0][2].id, matrix3[2][3].id))
            {
                backBlock12 = true;
                backBlock3 = true;
                backPressed12 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed12 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed13)
        {
            if (check_match(matrix3[0][2].id, matrix3[3][0].id))
            {
                backBlock13 = true;
                backBlock3 = true;
                backPressed13 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed14)
        {
            if (check_match(matrix3[0][2].id, matrix3[3][1].id))
            {
                backBlock14 = true;
                backBlock3 = true;
                backPressed14 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed14 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed15)
        {
            if (check_match(matrix3[0][2].id, matrix3[3][2].id))
            {
                backBlock15 = true;
                backBlock3 = true;
                backPressed15 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed15 = false;
                backPressed3 = false;
                printf("ERROU");
            }
        }
        if (backPressed16)
        {
            if (check_match(matrix3[0][2].id, matrix3[3][3].id))
            {
                backBlock16 = true;
                backBlock3 = true;
                backPressed16 = false;
                backPressed3 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed16 = false;
                backPressed3 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix3[0][3], 3 * mode_info.XResolution / 4, 0);
        if (backPressed1)
        {
            if (check_match(matrix3[0][3].id, matrix3[0][0].id))
            {
                backBlock1 = true;
                backBlock4 = true;
                backPressed1 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed2)
        {
            if (check_match(matrix3[0][3].id, matrix3[0][1].id))
            {
                backBlock2 = true;
                backBlock4 = true;
                backPressed2 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed3)
        {
            if (check_match(matrix3[0][3].id, matrix3[0][2].id))
            {
                backBlock3 = true;
                backBlock4 = true;
                backPressed3 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed3 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed5)
        {
            if (check_match(matrix3[0][3].id, matrix3[1][0].id))
            {
                backBlock5 = true;
                backBlock4 = true;
                backPressed5 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed5 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed6)
        {
            if (check_match(matrix3[0][3].id, matrix3[1][1].id))
            {
                backBlock6 = true;
                backBlock4 = true;
                backPressed6 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed6 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed7)
        {
            if (check_match(matrix3[0][3].id, matrix3[1][2].id))
            {
                backBlock7 = true;
                backBlock4 = true;
                backPressed7 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed7 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed8)
        {
            if (check_match(matrix3[0][3].id, matrix3[1][3].id))
            {
                backBlock8 = true;
                backBlock4 = true;
                backPressed8 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed8 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed9)
        {
            if (check_match(matrix3[0][3].id, matrix3[2][0].id))
            {
                backBlock9 = true;
                backBlock4 = true;
                backPressed9 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed9 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed10)
        {
            if (check_match(matrix3[0][3].id, matrix3[2][1].id))
            {
                backBlock10 = true;
                backBlock4 = true;
                backPressed10 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed10 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed11)
        {
            if (check_match(matrix3[0][3].id, matrix3[2][2].id))
            {
                backBlock11 = true;
                backBlock4 = true;
                backPressed11 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed11 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed12)
        {
            if (check_match(matrix3[0][3].id, matrix3[2][3].id))
            {
                backBlock12 = true;
                backBlock4 = true;
                backPressed12 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed12 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed13)
        {
            if (check_match(matrix3[0][3].id, matrix3[3][0].id))
            {
                backBlock13 = true;
                backBlock4 = true;
                backPressed13 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed14)
        {
            if (check_match(matrix3[0][3].id, matrix3[3][1].id))
            {
                backBlock14 = true;
                backBlock4 = true;
                backPressed14 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed14 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed15)
        {
            if (check_match(matrix3[0][3].id, matrix3[3][2].id))
            {
                backBlock15 = true;
                backBlock4 = true;
                backPressed15 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed15 = false;
                backPressed4 = false;
                printf("ERROU");
            }
        }
        if (backPressed16)
        {
            if (check_match(matrix3[0][3].id, matrix3[3][3].id))
            {
                backBlock16 = true;
                backBlock4 = true;
                backPressed16 = false;
                backPressed4 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed16 = false;
                backPressed4 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix3[1][0], 0, mode_info.YResolution / 4);
        if (backPressed1)
        {
            if (check_match(matrix3[1][0].id, matrix3[0][0].id))
            {
                backBlock1 = true;
                backBlock5 = true;
                backPressed1 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed2)
        {
            if (check_match(matrix3[1][0].id, matrix3[0][1].id))
            {
                backBlock2 = true;
                backBlock5 = true;
                backPressed2 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed3)
        {
            if (check_match(matrix3[1][0].id, matrix3[0][2].id))
            {
                backBlock3 = true;
                backBlock5 = true;
                backPressed3 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed3 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed4)
        {
            if (check_match(matrix3[1][0].id, matrix3[0][3].id))
            {
                backBlock4 = true;
                backBlock5 = true;
                backPressed4 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed4 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed6)
        {
            if (check_match(matrix3[1][0].id, matrix3[1][1].id))
            {
                backBlock6 = true;
                backBlock5 = true;
                backPressed6 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed6 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed7)
        {
            if (check_match(matrix3[1][0].id, matrix3[1][2].id))
            {
                backBlock7 = true;
                backBlock5 = true;
                backPressed7 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed7 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed8)
        {
            if (check_match(matrix3[1][0].id, matrix3[1][3].id))
            {
                backBlock8 = true;
                backBlock5 = true;
                backPressed8 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed8 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed9)
        {
            if (check_match(matrix3[1][0].id, matrix3[2][0].id))
            {
                backBlock9 = true;
                backBlock5 = true;
                backPressed9 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed9 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed10)
        {
            if (check_match(matrix3[1][0].id, matrix3[2][1].id))
            {
                backBlock10 = true;
                backBlock5 = true;
                backPressed10 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed10 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed11)
        {
            if (check_match(matrix3[1][0].id, matrix3[2][2].id))
            {
                backBlock11 = true;
                backBlock5 = true;
                backPressed11 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed11 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed12)
        {
            if (check_match(matrix3[1][0].id, matrix3[2][3].id))
            {
                backBlock12 = true;
                backBlock5 = true;
                backPressed12 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed12 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed13)
        {
            if (check_match(matrix3[1][0].id, matrix3[3][0].id))
            {
                backBlock13 = true;
                backBlock5 = true;
                backPressed13 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed14)
        {
            if (check_match(matrix3[1][0].id, matrix3[3][1].id))
            {
                backBlock14 = true;
                backBlock5 = true;
                backPressed14 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed14 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed15)
        {
            if (check_match(matrix3[1][0].id, matrix3[3][2].id))
            {
                backBlock15 = true;
                backBlock5 = true;
                backPressed15 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed15 = false;
                backPressed5 = false;
                printf("ERROU");
            }
        }
        if (backPressed16)
        {
            if (check_match(matrix3[1][0].id, matrix3[3][3].id))
            {
                backBlock16 = true;
                backBlock5 = true;
                backPressed16 = false;
                backPressed5 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed16 = false;
                backPressed5 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix3[1][1], mode_info.XResolution / 4, mode_info.YResolution / 4);
        if (backPressed1)
        {
            if (check_match(matrix3[1][1].id, matrix3[0][0].id))
            {
                backBlock1 = true;
                backBlock6 = true;
                backPressed1 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed2)
        {
            if (check_match(matrix3[1][1].id, matrix3[0][1].id))
            {
                backBlock2 = true;
                backBlock6 = true;
                backPressed2 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed3)
        {
            if (check_match(matrix3[1][1].id, matrix3[0][2].id))
            {
                backBlock3 = true;
                backBlock6 = true;
                backPressed3 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed3 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed4)
        {
            if (check_match(matrix3[1][1].id, matrix3[0][3].id))
            {
                backBlock4 = true;
                backBlock6 = true;
                backPressed4 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed4 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed5)
        {
            if (check_match(matrix3[1][1].id, matrix3[1][0].id))
            {
                backBlock5 = true;
                backBlock6 = true;
                backPressed5 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed5 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed7)
        {
            if (check_match(matrix3[1][1].id, matrix3[1][2].id))
            {
                backBlock7 = true;
                backBlock6 = true;
                backPressed7 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed7 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed8)
        {
            if (check_match(matrix3[1][1].id, matrix3[1][3].id))
            {
                backBlock8 = true;
                backBlock6 = true;
                backPressed8 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed8 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed9)
        {
            if (check_match(matrix3[1][1].id, matrix3[2][0].id))
            {
                backBlock9 = true;
                backBlock6 = true;
                backPressed9 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed9 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed10)
        {
            if (check_match(matrix3[1][1].id, matrix3[2][1].id))
            {
                backBlock10 = true;
                backBlock6 = true;
                backPressed10 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed10 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed11)
        {
            if (check_match(matrix3[1][1].id, matrix3[2][2].id))
            {
                backBlock11 = true;
                backBlock6 = true;
                backPressed11 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed11 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed12)
        {
            if (check_match(matrix3[1][1].id, matrix3[2][3].id))
            {
                backBlock12 = true;
                backBlock6 = true;
                backPressed12 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed12 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed13)
        {
            if (check_match(matrix3[1][1].id, matrix3[3][0].id))
            {
                backBlock13 = true;
                backBlock6 = true;
                backPressed13 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed14)
        {
            if (check_match(matrix3[1][1].id, matrix3[3][1].id))
            {
                backBlock14 = true;
                backBlock6 = true;
                backPressed14 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed14 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed15)
        {
            if (check_match(matrix3[1][1].id, matrix3[3][2].id))
            {
                backBlock15 = true;
                backBlock6 = true;
                backPressed15 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed15 = false;
                backPressed6 = false;
                printf("ERROU");
            }
        }
        if (backPressed16)
        {
            if (check_match(matrix3[1][1].id, matrix3[3][3].id))
            {
                backBlock16 = true;
                backBlock6 = true;
                backPressed16 = false;
                backPressed6 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed16 = false;
                backPressed6 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix3[1][2], mode_info.XResolution / 2, mode_info.YResolution / 4);
        if (backPressed1)
        {
            if (check_match(matrix3[1][2].id, matrix3[0][0].id))
            {
                backBlock1 = true;
                backBlock7 = true;
                backPressed1 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed2)
        {
            if (check_match(matrix3[1][2].id, matrix3[0][1].id))
            {
                backBlock2 = true;
                backBlock7 = true;
                backPressed2 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed3)
        {
            if (check_match(matrix3[1][2].id, matrix3[0][2].id))
            {
                backBlock3 = true;
                backBlock7 = true;
                backPressed3 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed3 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed4)
        {
            if (check_match(matrix3[1][2].id, matrix3[0][3].id))
            {
                backBlock4 = true;
                backBlock7 = true;
                backPressed4 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed4 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed5)
        {
            if (check_match(matrix3[1][2].id, matrix3[1][0].id))
            {
                backBlock5 = true;
                backBlock7 = true;
                backPressed5 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed5 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed6)
        {
            if (check_match(matrix3[1][2].id, matrix3[1][1].id))
            {
                backBlock6 = true;
                backBlock7 = true;
                backPressed6 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed6 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed8)
        {
            if (check_match(matrix3[1][2].id, matrix3[1][3].id))
            {
                backBlock8 = true;
                backBlock7 = true;
                backPressed8 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed8 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed9)
        {
            if (check_match(matrix3[1][2].id, matrix3[2][0].id))
            {
                backBlock9 = true;
                backBlock7 = true;
                backPressed9 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed9 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed10)
        {
            if (check_match(matrix3[1][2].id, matrix3[2][1].id))
            {
                backBlock10 = true;
                backBlock7 = true;
                backPressed10 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed10 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed11)
        {
            if (check_match(matrix3[1][2].id, matrix3[2][2].id))
            {
                backBlock11 = true;
                backBlock7 = true;
                backPressed11 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed11 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed12)
        {
            if (check_match(matrix3[1][2].id, matrix3[2][3].id))
            {
                backBlock12 = true;
                backBlock7 = true;
                backPressed12 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed12 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed13)
        {
            if (check_match(matrix3[1][2].id, matrix3[3][0].id))
            {
                backBlock13 = true;
                backBlock7 = true;
                backPressed13 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed14)
        {
            if (check_match(matrix3[1][2].id, matrix3[3][1].id))
            {
                backBlock14 = true;
                backBlock7 = true;
                backPressed14 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed14 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed15)
        {
            if (check_match(matrix3[1][2].id, matrix3[3][2].id))
            {
                backBlock15 = true;
                backBlock7 = true;
                backPressed15 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed15 = false;
                backPressed7 = false;
                printf("ERROU");
            }
        }
        if (backPressed16)
        {
            if (check_match(matrix3[1][2].id, matrix3[3][3].id))
            {
                backBlock16 = true;
                backBlock7 = true;
                backPressed16 = false;
                backPressed7 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed16 = false;
                backPressed7 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix3[1][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 4);
        if (backPressed1)
        {
            if (check_match(matrix3[1][3].id, matrix3[0][0].id))
            {
                backBlock1 = true;
                backBlock8 = true;
                backPressed1 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed2)
        {
            if (check_match(matrix3[1][3].id, matrix3[0][1].id))
            {
                backBlock2 = true;
                backBlock8 = true;
                backPressed2 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed3)
        {
            if (check_match(matrix3[1][3].id, matrix3[0][2].id))
            {
                backBlock3 = true;
                backBlock8 = true;
                backPressed3 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed3 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed4)
        {
            if (check_match(matrix3[1][3].id, matrix3[0][3].id))
            {
                backBlock4 = true;
                backBlock8 = true;
                backPressed4 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed4 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed5)
        {
            if (check_match(matrix3[1][3].id, matrix3[1][0].id))
            {
                backBlock5 = true;
                backBlock8 = true;
                backPressed5 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed5 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed6)
        {
            if (check_match(matrix3[1][3].id, matrix3[1][1].id))
            {
                backBlock6 = true;
                backBlock8 = true;
                backPressed6 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed6 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed7)
        {
            if (check_match(matrix3[1][3].id, matrix3[1][2].id))
            {
                backBlock7 = true;
                backBlock8 = true;
                backPressed7 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed7 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed9)
        {
            if (check_match(matrix3[1][3].id, matrix3[2][0].id))
            {
                backBlock9 = true;
                backBlock8 = true;
                backPressed9 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed9 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed10)
        {
            if (check_match(matrix3[1][3].id, matrix3[2][1].id))
            {
                backBlock10 = true;
                backBlock8 = true;
                backPressed10 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed10 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed11)
        {
            if (check_match(matrix3[1][3].id, matrix3[2][2].id))
            {
                backBlock11 = true;
                backBlock8 = true;
                backPressed11 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed11 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed12)
        {
            if (check_match(matrix3[1][3].id, matrix3[2][3].id))
            {
                backBlock12 = true;
                backBlock8 = true;
                backPressed12 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed12 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed13)
        {
            if (check_match(matrix3[1][3].id, matrix3[3][0].id))
            {
                backBlock13 = true;
                backBlock8 = true;
                backPressed13 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed14)
        {
            if (check_match(matrix3[1][3].id, matrix3[3][1].id))
            {
                backBlock14 = true;
                backBlock8 = true;
                backPressed14 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed14 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed15)
        {
            if (check_match(matrix3[1][3].id, matrix3[3][2].id))
            {
                backBlock15 = true;
                backBlock8 = true;
                backPressed15 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed15 = false;
                backPressed8 = false;
                printf("ERROU");
            }
        }
        if (backPressed16)
        {
            if (check_match(matrix3[1][3].id, matrix3[3][3].id))
            {
                backBlock16 = true;
                backBlock8 = true;
                backPressed16 = false;
                backPressed8 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed16 = false;
                backPressed8 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix3[2][0], 0, mode_info.YResolution / 2);
        if (backPressed1)
        {
            if (check_match(matrix3[2][0].id, matrix3[0][0].id))
            {
                backBlock1 = true;
                backBlock9 = true;
                backPressed1 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed2)
        {
            if (check_match(matrix3[2][0].id, matrix3[0][1].id))
            {
                backBlock2 = true;
                backBlock9 = true;
                backPressed2 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed3)
        {
            if (check_match(matrix3[2][0].id, matrix3[0][2].id))
            {
                backBlock3 = true;
                backBlock9 = true;
                backPressed3 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed3 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed4)
        {
            if (check_match(matrix3[2][0].id, matrix3[0][3].id))
            {
                backBlock4 = true;
                backBlock9 = true;
                backPressed4 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed4 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed5)
        {
            if (check_match(matrix3[2][0].id, matrix3[1][0].id))
            {
                backBlock5 = true;
                backBlock9 = true;
                backPressed5 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed5 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed6)
        {
            if (check_match(matrix3[2][0].id, matrix3[1][1].id))
            {
                backBlock6 = true;
                backBlock9 = true;
                backPressed6 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed6 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed7)
        {
            if (check_match(matrix3[2][0].id, matrix3[1][2].id))
            {
                backBlock7 = true;
                backBlock9 = true;
                backPressed7 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed7 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed8)
        {
            if (check_match(matrix3[2][0].id, matrix3[1][3].id))
            {
                backBlock8 = true;
                backBlock9 = true;
                backPressed8 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed8 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed10)
        {
            if (check_match(matrix3[2][0].id, matrix3[2][1].id))
            {
                backBlock10 = true;
                backBlock9 = true;
                backPressed10 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed10 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed11)
        {
            if (check_match(matrix3[2][0].id, matrix3[2][2].id))
            {
                backBlock11 = true;
                backBlock9 = true;
                backPressed11 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed11 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed12)
        {
            if (check_match(matrix3[2][0].id, matrix3[2][3].id))
            {
                backBlock12 = true;
                backBlock9 = true;
                backPressed12 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed12 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed13)
        {
            if (check_match(matrix3[2][0].id, matrix3[3][0].id))
            {
                backBlock13 = true;
                backBlock9 = true;
                backPressed13 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed14)
        {
            if (check_match(matrix3[2][0].id, matrix3[3][1].id))
            {
                backBlock14 = true;
                backBlock9 = true;
                backPressed14 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed14 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed15)
        {
            if (check_match(matrix3[2][0].id, matrix3[3][2].id))
            {
                backBlock15 = true;
                backBlock9 = true;
                backPressed15 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed15 = false;
                backPressed9 = false;
                printf("ERROU");
            }
        }
        if (backPressed16)
        {
            if (check_match(matrix3[2][0].id, matrix3[3][3].id))
            {
                backBlock16 = true;
                backBlock9 = true;
                backPressed16 = false;
                backPressed9 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed16 = false;
                backPressed9 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix3[2][1], mode_info.XResolution / 4, mode_info.YResolution / 2);
        if (backPressed1)
        {
            if (check_match(matrix3[2][1].id, matrix3[0][0].id))
            {
                backBlock1 = true;
                backBlock10 = true;
                backPressed1 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed2)
        {
            if (check_match(matrix3[2][1].id, matrix3[0][1].id))
            {
                backBlock2 = true;
                backBlock10 = true;
                backPressed2 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed3)
        {
            if (check_match(matrix3[2][1].id, matrix3[0][2].id))
            {
                backBlock3 = true;
                backBlock10 = true;
                backPressed3 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed3 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed4)
        {
            if (check_match(matrix3[2][1].id, matrix3[0][3].id))
            {
                backBlock4 = true;
                backBlock10 = true;
                backPressed4 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed4 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed5)
        {
            if (check_match(matrix3[2][1].id, matrix3[1][0].id))
            {
                backBlock5 = true;
                backBlock10 = true;
                backPressed5 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed5 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed6)
        {
            if (check_match(matrix3[2][1].id, matrix3[1][1].id))
            {
                backBlock6 = true;
                backBlock10 = true;
                backPressed6 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed6 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed7)
        {
            if (check_match(matrix3[2][1].id, matrix3[1][2].id))
            {
                backBlock7 = true;
                backBlock10 = true;
                backPressed7 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed7 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed8)
        {
            if (check_match(matrix3[2][1].id, matrix3[1][3].id))
            {
                backBlock8 = true;
                backBlock10 = true;
                backPressed8 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed8 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed9)
        {
            if (check_match(matrix3[2][1].id, matrix3[2][0].id))
            {
                backBlock9 = true;
                backBlock10 = true;
                backPressed9 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed9 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed11)
        {
            if (check_match(matrix3[2][1].id, matrix3[2][2].id))
            {
                backBlock11 = true;
                backBlock10 = true;
                backPressed11 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed11 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed12)
        {
            if (check_match(matrix3[2][1].id, matrix3[2][3].id))
            {
                backBlock12 = true;
                backBlock10 = true;
                backPressed12 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed12 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed13)
        {
            if (check_match(matrix3[2][1].id, matrix3[3][0].id))
            {
                backBlock13 = true;
                backBlock10 = true;
                backPressed13 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed14)
        {
            if (check_match(matrix3[2][1].id, matrix3[3][1].id))
            {
                backBlock14 = true;
                backBlock10 = true;
                backPressed14 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed14 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed15)
        {
            if (check_match(matrix3[2][1].id, matrix3[3][2].id))
            {
                backBlock15 = true;
                backBlock10 = true;
                backPressed15 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed15 = false;
                backPressed10 = false;
                printf("ERROU");
            }
        }
        if (backPressed16)
        {
            if (check_match(matrix3[2][1].id, matrix3[3][3].id))
            {
                backBlock16 = true;
                backBlock10 = true;
                backPressed16 = false;
                backPressed10 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed16 = false;
                backPressed10 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix3[2][2], mode_info.XResolution / 2, mode_info.YResolution / 2);
        if (backPressed1)
        {
            if (check_match(matrix3[2][2].id, matrix3[0][0].id))
            {
                backBlock1 = true;
                backBlock11 = true;
                backPressed1 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed2)
        {
            if (check_match(matrix3[2][2].id, matrix3[0][1].id))
            {
                backBlock2 = true;
                backBlock11 = true;
                backPressed2 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed3)
        {
            if (check_match(matrix3[2][2].id, matrix3[0][2].id))
            {
                backBlock3 = true;
                backBlock11 = true;
                backPressed3 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed3 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed4)
        {
            if (check_match(matrix3[2][2].id, matrix3[0][3].id))
            {
                backBlock4 = true;
                backBlock11 = true;
                backPressed4 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed4 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed5)
        {
            if (check_match(matrix3[2][2].id, matrix3[1][0].id))
            {
                backBlock5 = true;
                backBlock11 = true;
                backPressed5 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed5 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed6)
        {
            if (check_match(matrix3[2][2].id, matrix3[1][1].id))
            {
                backBlock6 = true;
                backBlock11 = true;
                backPressed6 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed6 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed7)
        {
            if (check_match(matrix3[2][2].id, matrix3[1][2].id))
            {
                backBlock7 = true;
                backBlock11 = true;
                backPressed7 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed7 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed8)
        {
            if (check_match(matrix3[2][2].id, matrix3[1][3].id))
            {
                backBlock8 = true;
                backBlock11 = true;
                backPressed8 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed8 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed9)
        {
            if (check_match(matrix3[2][2].id, matrix3[2][0].id))
            {
                backBlock9 = true;
                backBlock11 = true;
                backPressed9 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed9 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed10)
        {
            if (check_match(matrix3[2][2].id, matrix3[2][1].id))
            {
                backBlock10 = true;
                backBlock11 = true;
                backPressed10 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed10 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed12)
        {
            if (check_match(matrix3[2][2].id, matrix3[2][3].id))
            {
                backBlock12 = true;
                backBlock11 = true;
                backPressed12 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed12 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed13)
        {
            if (check_match(matrix3[2][2].id, matrix3[3][0].id))
            {
                backBlock13 = true;
                backBlock11 = true;
                backPressed13 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed14)
        {
            if (check_match(matrix3[2][2].id, matrix3[3][1].id))
            {
                backBlock14 = true;
                backBlock11 = true;
                backPressed14 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed14 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed15)
        {
            if (check_match(matrix3[2][2].id, matrix3[3][2].id))
            {
                backBlock15 = true;
                backBlock11 = true;
                backPressed15 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed15 = false;
                backPressed11 = false;
                printf("ERROU");
            }
        }
        if (backPressed16)
        {
            if (check_match(matrix3[2][2].id, matrix3[3][3].id))
            {
                backBlock16 = true;
                backBlock11 = true;
                backPressed16 = false;
                backPressed11 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed16 = false;
                backPressed11 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix3[2][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 2);
        if (backPressed1)
        {
            if (check_match(matrix3[2][3].id, matrix3[0][0].id))
            {
                backBlock1 = true;
                backBlock12 = true;
                backPressed1 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed2)
        {
            if (check_match(matrix3[2][3].id, matrix3[0][1].id))
            {
                backBlock2 = true;
                backBlock12 = true;
                backPressed2 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed3)
        {
            if (check_match(matrix3[2][3].id, matrix3[0][2].id))
            {
                backBlock3 = true;
                backBlock12 = true;
                backPressed3 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed3 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed4)
        {
            if (check_match(matrix3[2][3].id, matrix3[0][3].id))
            {
                backBlock4 = true;
                backBlock12 = true;
                backPressed4 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed4 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed5)
        {
            if (check_match(matrix3[2][3].id, matrix3[1][0].id))
            {
                backBlock5 = true;
                backBlock12 = true;
                backPressed5 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed5 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed6)
        {
            if (check_match(matrix3[2][3].id, matrix3[1][1].id))
            {
                backBlock6 = true;
                backBlock12 = true;
                backPressed6 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed6 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed7)
        {
            if (check_match(matrix3[2][3].id, matrix3[1][2].id))
            {
                backBlock7 = true;
                backBlock12 = true;
                backPressed7 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed7 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed8)
        {
            if (check_match(matrix3[2][3].id, matrix3[1][3].id))
            {
                backBlock8 = true;
                backBlock12 = true;
                backPressed8 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed8 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed9)
        {
            if (check_match(matrix3[2][3].id, matrix3[2][0].id))
            {
                backBlock9 = true;
                backBlock12 = true;
                backPressed9 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed9 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed10)
        {
            if (check_match(matrix3[2][3].id, matrix3[2][1].id))
            {
                backBlock10 = true;
                backBlock12 = true;
                backPressed10 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed10 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed11)
        {
            if (check_match(matrix3[2][3].id, matrix3[2][2].id))
            {
                backBlock11 = true;
                backBlock12 = true;
                backPressed11 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed11 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed13)
        {
            if (check_match(matrix3[2][3].id, matrix3[3][0].id))
            {
                backBlock13 = true;
                backBlock12 = true;
                backPressed13 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed14)
        {
            if (check_match(matrix3[2][3].id, matrix3[3][1].id))
            {
                backBlock14 = true;
                backBlock12 = true;
                backPressed14 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed14 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed15)
        {
            if (check_match(matrix3[2][3].id, matrix3[3][2].id))
            {
                backBlock15 = true;
                backBlock12 = true;
                backPressed15 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed15 = false;
                backPressed12 = false;
                printf("ERROU");
            }
        }
        if (backPressed16)
        {
            if (check_match(matrix3[2][3].id, matrix3[3][3].id))
            {
                backBlock16 = true;
                backBlock12 = true;
                backPressed16 = false;
                backPressed12 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed16 = false;
                backPressed12 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix3[3][0], 0, 3 * mode_info.YResolution / 4);
        if (backPressed1)
        {
            if (check_match(matrix3[3][0].id, matrix3[0][0].id))
            {
                backBlock1 = true;
                backBlock13 = true;
                backPressed1 = false;
                backPressed13 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed2)
        {
            if (check_match(matrix3[3][0].id, matrix3[0][1].id))
            {
                backBlock2 = true;
                backBlock13 = true;
                backPressed2 = false;
                backPressed13 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed3)
        {
            if (check_match(matrix3[3][0].id, matrix3[0][2].id))
            {
                backBlock3 = true;
                backBlock13 = true;
                backPressed3 = false;
                backPressed13 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed3 = false;
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed4)
        {
            if (check_match(matrix3[3][0].id, matrix3[0][3].id))
            {
                backBlock4 = true;
                backBlock13 = true;
                backPressed4 = false;
                backPressed13 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed4 = false;
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed5)
        {
            if (check_match(matrix3[3][0].id, matrix3[1][0].id))
            {
                backBlock5 = true;
                backBlock13 = true;
                backPressed5 = false;
                backPressed13 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed5 = false;
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed6)
        {
            if (check_match(matrix3[3][0].id, matrix3[1][1].id))
            {
                backBlock6 = true;
                backBlock13 = true;
                backPressed6 = false;
                backPressed13 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed6 = false;
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed7)
        {
            if (check_match(matrix3[3][0].id, matrix3[1][2].id))
            {
                backBlock7 = true;
                backBlock13 = true;
                backPressed7 = false;
                backPressed13 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed7 = false;
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed8)
        {
            if (check_match(matrix3[3][0].id, matrix3[1][3].id))
            {
                backBlock8 = true;
                backBlock13 = true;
                backPressed8 = false;
                backPressed13 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed8 = false;
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed9)
        {
            if (check_match(matrix3[3][0].id, matrix3[2][0].id))
            {
                backBlock9 = true;
                backBlock13 = true;
                backPressed9 = false;
                backPressed13 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed9 = false;
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed10)
        {
            if (check_match(matrix3[3][0].id, matrix3[2][1].id))
            {
                backBlock10 = true;
                backBlock13 = true;
                backPressed10 = false;
                backPressed13 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed10 = false;
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed11)
        {
            if (check_match(matrix3[3][0].id, matrix3[2][2].id))
            {
                backBlock11 = true;
                backBlock13 = true;
                backPressed11 = false;
                backPressed13 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed11 = false;
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed12)
        {
            if (check_match(matrix3[3][0].id, matrix3[2][3].id))
            {
                backBlock12 = true;
                backBlock13 = true;
                backPressed12 = false;
                backPressed13 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed12 = false;
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed14)
        {
            if (check_match(matrix3[3][0].id, matrix3[3][1].id))
            {
                backBlock14 = true;
                backBlock13 = true;
                backPressed13 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed15)
        {
            if (check_match(matrix3[3][0].id, matrix3[3][2].id))
            {
                backBlock15 = true;
                backBlock13 = true;
                backPressed13 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                printf("ERROU");
            }
        }
        if (backPressed16)
        {
            if (check_match(matrix3[3][0].id, matrix3[3][3].id))
            {
                backBlock16 = true;
                backBlock13 = true;
                backPressed13 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix3[3][1], mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
        if (backPressed1)
        {
            if (check_match(matrix3[3][1].id, matrix3[0][0].id))
            {
                backBlock1 = true;
                backBlock14 = true;
                backPressed1 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed2)
        {
            if (check_match(matrix3[3][1].id, matrix3[0][1].id))
            {
                backBlock2 = true;
                backBlock14 = true;
                backPressed2 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed3)
        {
            if (check_match(matrix3[3][1].id, matrix3[0][2].id))
            {
                backBlock3 = true;
                backBlock14 = true;
                backPressed3 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed3 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed4)
        {
            if (check_match(matrix3[3][1].id, matrix3[0][3].id))
            {
                backBlock4 = true;
                backBlock14 = true;
                backPressed4 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed4 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed5)
        {
            if (check_match(matrix3[3][1].id, matrix3[1][0].id))
            {
                backBlock5 = true;
                backBlock14 = true;
                backPressed5 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed5 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed6)
        {
            if (check_match(matrix3[3][1].id, matrix3[1][1].id))
            {
                backBlock6 = true;
                backBlock14 = true;
                backPressed6 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed6 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed7)
        {
            if (check_match(matrix3[3][1].id, matrix3[1][2].id))
            {
                backBlock7 = true;
                backBlock14 = true;
                backPressed7 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed7 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed8)
        {
            if (check_match(matrix3[3][1].id, matrix3[1][3].id))
            {
                backBlock8 = true;
                backBlock14 = true;
                backPressed8 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed8 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed9)
        {
            if (check_match(matrix3[3][1].id, matrix3[2][0].id))
            {
                backBlock9 = true;
                backBlock14 = true;
                backPressed9 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed9 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed10)
        {
            if (check_match(matrix3[3][1].id, matrix3[2][1].id))
            {
                backBlock10 = true;
                backBlock14 = true;
                backPressed10 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed10 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed11)
        {
            if (check_match(matrix3[3][1].id, matrix3[2][2].id))
            {
                backBlock11 = true;
                backBlock14 = true;
                backPressed11 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed11 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed12)
        {
            if (check_match(matrix3[3][1].id, matrix3[2][3].id))
            {
                backBlock12 = true;
                backBlock14 = true;
                backPressed12 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed12 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed13)
        {
            if (check_match(matrix3[3][1].id, matrix3[3][0].id))
            {
                backBlock13 = true;
                backBlock14 = true;
                backPressed13 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed15)
        {
            if (check_match(matrix3[3][1].id, matrix3[3][2].id))
            {
                backBlock15 = true;
                backBlock14 = true;
                backPressed15 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed15 = false;
                backPressed14 = false;
                printf("ERROU");
            }
        }
        if (backPressed16)
        {
            if (check_match(matrix3[3][1].id, matrix3[3][3].id))
            {
                backBlock16 = true;
                backBlock14 = true;
                backPressed16 = false;
                backPressed14 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed16 = false;
                backPressed14 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix3[3][2], mode_info.XResolution / 2, 3 * mode_info.YResolution / 4);
        if (backPressed1)
        {
            if (check_match(matrix3[3][2].id, matrix3[0][0].id))
            {
                backBlock1 = true;
                backBlock15 = true;
                backPressed1 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed2)
        {
            if (check_match(matrix3[3][2].id, matrix3[0][1].id))
            {
                backBlock2 = true;
                backBlock15 = true;
                backPressed2 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed3)
        {
            if (check_match(matrix3[3][2].id, matrix3[0][2].id))
            {
                backBlock3 = true;
                backBlock15 = true;
                backPressed3 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed3 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed4)
        {
            if (check_match(matrix3[3][2].id, matrix3[0][3].id))
            {
                backBlock4 = true;
                backBlock15 = true;
                backPressed4 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed4 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed5)
        {
            if (check_match(matrix3[3][2].id, matrix3[1][0].id))
            {
                backBlock5 = true;
                backBlock15 = true;
                backPressed5 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed5 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed6)
        {
            if (check_match(matrix3[3][2].id, matrix3[1][1].id))
            {
                backBlock6 = true;
                backBlock15 = true;
                backPressed6 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed6 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed7)
        {
            if (check_match(matrix3[3][2].id, matrix3[1][2].id))
            {
                backBlock7 = true;
                backBlock15 = true;
                backPressed7 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed7 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed8)
        {
            if (check_match(matrix3[3][2].id, matrix3[1][3].id))
            {
                backBlock8 = true;
                backBlock15 = true;
                backPressed8 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed8 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed9)
        {
            if (check_match(matrix3[3][2].id, matrix3[2][0].id))
            {
                backBlock9 = true;
                backBlock15 = true;
                backPressed9 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed9 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed10)
        {
            if (check_match(matrix3[3][2].id, matrix3[2][1].id))
            {
                backBlock10 = true;
                backBlock15 = true;
                backPressed10 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed10 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed11)
        {
            if (check_match(matrix3[3][2].id, matrix3[2][2].id))
            {
                backBlock11 = true;
                backBlock15 = true;
                backPressed11 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed11 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed12)
        {
            if (check_match(matrix3[3][2].id, matrix3[2][3].id))
            {
                backBlock12 = true;
                backBlock15 = true;
                backPressed12 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed12 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed13)
        {
            if (check_match(matrix3[3][2].id, matrix3[3][0].id))
            {
                backBlock13 = true;
                backBlock15 = true;
                backPressed13 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed14)
        {
            if (check_match(matrix3[3][2].id, matrix3[3][1].id))
            {
                backBlock14 = true;
                backBlock15 = true;
                backPressed14 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed14 = false;
                backPressed15 = false;
                printf("ERROU");
            }
        }
        if (backPressed16)
        {
            if (check_match(matrix3[3][2].id, matrix3[3][3].id))
            {
                backBlock16 = true;
                backBlock15 = true;
                backPressed16 = false;
                backPressed15 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed16 = false;
                backPressed15 = false;
                printf("ERROU");
            }
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
        draw_sprite_xpm(&matrix3[3][3], 3 * mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
        if (backPressed1)
        {
            if (check_match(matrix3[3][3].id, matrix3[0][0].id))
            {
                backBlock1 = true;
                backBlock16 = true;
                backPressed1 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed1 = false;
                backPressed16 = false;
                printf("ERROU");
            }
        }
        if (backPressed2)
        {
            if (check_match(matrix3[3][3].id, matrix3[0][1].id))
            {
                backBlock2 = true;
                backBlock16 = true;
                backPressed2 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed2 = false;
                backPressed16 = false;
                printf("ERROU");
            }
        }
        if (backPressed3)
        {
            if (check_match(matrix3[3][3].id, matrix3[0][2].id))
            {
                backBlock3 = true;
                backBlock16 = true;
                backPressed3 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed3 = false;
                backPressed16 = false;
                printf("ERROU");
            }
        }
        if (backPressed4)
        {
            if (check_match(matrix3[3][3].id, matrix3[0][3].id))
            {
                backBlock4 = true;
                backBlock16 = true;
                backPressed4 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed4 = false;
                backPressed16 = false;
                printf("ERROU");
            }
        }
        if (backPressed5)
        {
            if (check_match(matrix3[3][3].id, matrix3[1][0].id))
            {
                backBlock5 = true;
                backBlock16 = true;
                backPressed5 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed5 = false;
                backPressed16 = false;
                printf("ERROU");
            }
        }
        if (backPressed6)
        {
            if (check_match(matrix3[3][3].id, matrix3[1][1].id))
            {
                backBlock6 = true;
                backBlock16 = true;
                backPressed6 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed6 = false;
                backPressed16 = false;
                printf("ERROU");
            }
        }
        if (backPressed7)
        {
            if (check_match(matrix3[3][3].id, matrix3[1][2].id))
            {
                backBlock7 = true;
                backBlock16 = true;
                backPressed7 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed7 = false;
                backPressed16 = false;
                printf("ERROU");
            }
        }
        if (backPressed8)
        {
            if (check_match(matrix3[3][3].id, matrix3[1][3].id))
            {
                backBlock8 = true;
                backBlock16 = true;
                backPressed8 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed8 = false;
                backPressed16 = false;
                printf("ERROU");
            }
        }
        if (backPressed9)
        {
            if (check_match(matrix3[3][3].id, matrix3[2][0].id))
            {
                backBlock9 = true;
                backBlock16 = true;
                backPressed9 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed9 = false;
                backPressed16 = false;
                printf("ERROU");
            }
        }
        if (backPressed10)
        {
            if (check_match(matrix3[3][3].id, matrix3[2][1].id))
            {
                backBlock10 = true;
                backBlock16 = true;
                backPressed10 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed10 = false;
                backPressed16 = false;
                printf("ERROU");
            }
        }
        if (backPressed11)
        {
            if (check_match(matrix3[3][3].id, matrix3[2][2].id))
            {
                backBlock11 = true;
                backBlock16 = true;
                backPressed11 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed11 = false;
                backPressed16 = false;
                printf("ERROU");
            }
        }
        if (backPressed12)
        {
            if (check_match(matrix3[3][3].id, matrix3[2][3].id))
            {
                backBlock12 = true;
                backBlock16 = true;
                backPressed12 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed12 = false;
                backPressed16 = false;
                printf("ERROU");
            }
        }
        if (backPressed13)
        {
            if (check_match(matrix3[3][3].id, matrix3[3][0].id))
            {
                backBlock13 = true;
                backBlock16 = true;
                backPressed13 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed13 = false;
                backPressed16 = false;
                printf("ERROU");
            }
        }
        if (backPressed14)
        {
            if (check_match(matrix3[3][3].id, matrix3[3][1].id))
            {
                backBlock14 = true;
                backBlock16 = true;
                backPressed14 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed14 = false;
                backPressed16 = false;
                printf("ERROU");
            }
        }
        if (backPressed15)
        {
            if (check_match(matrix3[3][3].id, matrix3[3][2].id))
            {
                backBlock15 = true;
                backBlock16 = true;
                backPressed15 = false;
                backPressed16 = false;
                printf("ACERTOU");
            }
            else
            {
                backPressed15 = false;
                backPressed16 = false;
                printf("ERROU");
            }
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

    if (!backBlock1)
    {
        process_deck1();
    }
    else if (backBlock1)
    {
        draw_sprite_xpm(&matrix3[0][0], 0, 0);
    }
    if (!backBlock2)
    {
        process_deck2();
    }
    else if (backBlock2)
    {
        draw_sprite_xpm(&matrix3[0][1], mode_info.XResolution / 4, 0);
    }
    if (!backBlock3)
    {
        process_deck3();
    }
    else if (backBlock3)
    {
        draw_sprite_xpm(&matrix3[0][2], mode_info.XResolution / 2, 0);
    }
    if (!backBlock4)
    {
        process_deck4();
    }
    else if (backBlock4)
    {
        draw_sprite_xpm(&matrix3[0][3], 3 * mode_info.XResolution / 4, 0);
    }
    if (!backBlock5)
    {
        process_deck5();
    }
    else if (backBlock5)
    {
        draw_sprite_xpm(&matrix3[1][0], 0, mode_info.YResolution / 4);
    }
    if (!backBlock6)
    {
        process_deck6();
    }
    else if (backBlock6)
    {
        draw_sprite_xpm(&matrix3[1][1], mode_info.XResolution / 4, mode_info.YResolution / 4);
    }
    if (!backBlock7)
    {
        process_deck7();
    }
    else if (backBlock7)
    {
        draw_sprite_xpm(&matrix3[1][2], mode_info.XResolution / 2, mode_info.YResolution / 4);
    }
    if (!backBlock8)
    {
        process_deck8();
    }
    else if (backBlock8)
    {
        draw_sprite_xpm(&matrix3[1][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 4);
    }
    if (!backBlock9)
    {
        process_deck9();
    }
    else if (backBlock9)
    {
        draw_sprite_xpm(&matrix3[2][0], 0, mode_info.YResolution / 2);
    }
    if (!backBlock10)
    {
        process_deck10();
    }
    else if (backBlock10)
    {
        draw_sprite_xpm(&matrix3[2][1], mode_info.XResolution / 4, mode_info.YResolution / 2);
    }
    if (!backBlock11)
    {
        process_deck11();
    }
    else if (backBlock11)
    {
        draw_sprite_xpm(&matrix3[2][2], mode_info.XResolution / 2, mode_info.YResolution / 2);
    }
    if (!backBlock12)
    {
        process_deck12();
    }
    else if (backBlock12)
    {
        draw_sprite_xpm(&matrix3[2][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 2);
    }
    if (!backBlock13)
    {
        process_deck13();
    }
    else if (backBlock13)
    {
        draw_sprite_xpm(&matrix3[3][0], 0, 3 * mode_info.YResolution / 4);
    }
    if (!backBlock14)
    {
        process_deck14();
    }
    else if (backBlock14)
    {
        draw_sprite_xpm(&matrix3[3][1], mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
    }
    if (!backBlock15)
    {
        process_deck15();
    }
    else if (backBlock15)
    {
        draw_sprite_xpm(&matrix3[3][2], mode_info.XResolution / 2, 3 * mode_info.YResolution / 4);
    }
    if (!backBlock16)
    {
        process_deck16();
    }
    else if (backBlock16)
    {
        draw_sprite_xpm(&matrix3[3][3], 3 * mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
    }
    if (backBlock1 && backBlock2 && backBlock3 && backBlock4 && backBlock5 && backBlock6 && backBlock7 && backBlock8 && backBlock9 && backBlock10 && backBlock11 && backBlock12 && backBlock13 && backBlock14 && backBlock15 && backBlock16)
    {
        menuState = END;
    }
}

// O menu final é apenas um retângulo com tamanho máximo, com um smile ao centro
void draw_finish_menu()
{
    draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 0x000000, drawing_frame_buffer);
    if (player_1 != 0)
    {
        if (player_1 == 0)
        {
            draw_sprite_xpm(back, mode_info.XResolution / 2 - 100, mode_info.YResolution / 2 - 100);
        }
        else if (player_1 == 1)
        {
            draw_sprite_xpm(number1, mode_info.XResolution / 2 - 100, mode_info.YResolution / 2 - 100);
        }
        else if (player_1 == 2)
        {
            draw_sprite_xpm(number2, mode_info.XResolution / 2 - 100, mode_info.YResolution / 2 - 100);
        }
    }
    if (player_2 != 0)
    {
        if (player_2 == 0)
        {
            draw_sprite_xpm(back, mode_info.XResolution / 3, mode_info.YResolution / 3);
        }
        else if (player_2 == 1)
        {
            draw_sprite_xpm(number1, mode_info.XResolution / 3, mode_info.YResolution / 3);
        }
        else if (player_2 == 2)
        {
            draw_sprite_xpm(number2, mode_info.XResolution / 3, mode_info.YResolution / 3);
        }
    }
    if (player_1 == 0 && player_2 == 0)
    {
        draw_sprite_xpm(smile, mode_info.XResolution / 2 - 100, mode_info.YResolution / 2 - 100);
    }
}

// O cursor mode ter dois estados:
// - "normal", quando está no menu de início ou de fim
// - "mão", quando está no menu com os botões
void draw_mouse()
{
    switch (menuState)
    {
    case START:
    case END:
        draw_sprite_xpm(mouse, mouse_info.x, mouse_info.y);
        break;
    case GAME:
        draw_sprite_xpm(hand, mouse_info.x, mouse_info.y);
        break;
    case GAME_2:
        draw_sprite_xpm(hand, mouse_info.x, mouse_info.y);
        break;
    case MODE:
        draw_sprite_xpm(mouse, mouse_info.x, mouse_info.y);
        break;
    case GAME_3:
        draw_sprite_xpm(hand, mouse_info.x, mouse_info.y);
        break;
    case GAME_4_2:
        draw_sprite_xpm(hand, mouse_info.x, mouse_info.y);
        break;
    }
}

// A função recebe um objeto Sprite proveniente de um XPM e mostra-o nas coordenadas (x, y)
// Usa as cores dinamicamente alocadas na altura da construção
// A função ignora a cor transparente do XPM para não modificar o fundo quando não é preciso
int draw_sprite_xpm(Sprite *sprite, int x, int y)
{
    uint16_t height = sprite->height;
    uint16_t width = sprite->width;
    uint32_t current_color;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            current_color = sprite->colors[w + h * width];
            if (current_color == TRANSPARENT)
                continue;
            if (draw_pixel(x + w, y + h, current_color, drawing_frame_buffer) != 0)
                return 1;
        }
    }
    return 0;
}

// A função recebe um objeto Sprite de cor constante e mostra-o nas coordenadas (x, y)
// Usa apenas uma cor, alocada na altura da construção
// A função ignora a cor transparente do XPM para não modificar o fundo quando não é preciso
int draw_sprite_button(Sprite *sprite, int x, int y)
{
    uint16_t height = sprite->height;
    uint16_t width = sprite->width;
    uint32_t color = sprite->color;
    // 1 º quadrante -> Leva para o start
    // 2 º quadrante -> Leva para o game
    //  3 º quadrante -> Leva para o end
    //  4 º quadrante -> Leva para o exit
    if (menuState == START)
    {
        if (sprite->pressed == 1)
        {
            if (mouse_info.x > 0 && mouse_info.x < mode_info.XResolution / 2 && mouse_info.y > 0 && mouse_info.y < mode_info.YResolution / 2)
            {

                menuState = START;
            }
            else if (mouse_info.x > mode_info.XResolution / 2 && mouse_info.x < mode_info.XResolution && mouse_info.y > 0 && mouse_info.y < mode_info.YResolution / 2)
            {
                menuState = GAME;
            }
            else if (mouse_info.x > 0 && mouse_info.x < mode_info.XResolution / 2 && mouse_info.y > mode_info.YResolution / 2 && mouse_info.y < mode_info.YResolution)
            {
                menuState = GAME_2;
            }
            else if (mouse_info.x > mode_info.XResolution / 2 && mouse_info.x < mode_info.XResolution && mouse_info.y > mode_info.YResolution / 2 && mouse_info.y < mode_info.YResolution)
            {
                systemState = EXIT;
            }
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (draw_pixel(x + w, y + h, color, drawing_frame_buffer) != 0)
                return 1;
        }
    }
    return 0;
}

// Faz o display do tempo real num formato amigável
// No caso do Template esta função apenas retorna uma string para o ficheiro output.txt
// Em projetos pode ser mudada para invocar sprites que coloquem no ecrã os respetivos dígitos
void display_real_time()
{
    printf("NOW: %d/%d/%d @%d:%d:%d\n", 2000 + time_info.year, time_info.month, time_info.day, time_info.hours, time_info.minutes, time_info.seconds);
}

void draw_xpm_draw_buffer(xpm_map_t xpm, uint16_t x, uint16_t y)
{
    xpm_image_t img;
    uint32_t *colors = (uint32_t *)xpm_load(xpm, XPM_8_8_8_8, &img);
    for (int h = 0; h < img.height; h++)
    {
        for (int w = 0; w < img.width; w++)
        {
            if ((uint32_t)&colors[w + h * img.width] == 0xfffffe)
                return;
            if (x >= mode_info.XResolution || y >= mode_info.YResolution)
                return;
            memcpy(&drawing_frame_buffer[(mode_info.XResolution * (y + h) + (x + w)) * (mode_info.BitsPerPixel + 7) / 8], &colors[w + h * img.width], (mode_info.BitsPerPixel + 7) / 8);
        }
    }
    return;
}
