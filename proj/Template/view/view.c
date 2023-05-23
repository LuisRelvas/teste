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
int animationFrame = 0;
bool isAnimating = false;
int chosen;

// alocação da memoria para a matriz;

Sprite **alloc_matrix(int n, int m)
{
    Sprite **mat = (Sprite **)malloc(sizeof(Sprite *) * m);
    for (int i = 0; i < n; i++)
    {
        mat[i] = (Sprite *)malloc(sizeof(Sprite) * n);
    }
    return mat;
}

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
    case GAME_8_2:
        draw_game_menu_game_3();
        break;
    case GAME_16_2:
        draw_game_menu_game_4();
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

// varibles for the game1
Sprite **matrix;
Sprite *index_1;
Sprite *index_2;
bool *index_1_bool;
bool *index_2_bool;

int id1 = 0;
int id2 = 0;
int matrix_id1 = -1;
int matrix_id2 = -1;
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

// O menu do jogo é constituído por quatro botões

void draw_game_menu_game_3()
{
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
        matrix = alloc_matrix(2, 2);
        shuffle(cards, j);
        pre++;
    }

    memset(drawing_frame_buffer, 0, mode_info.XResolution * mode_info.YResolution * mode_info.BitsPerPixel / 8);
    draw_sprite_xpm(back1, 0, 0);
    draw_sprite_xpm(back2, mode_info.XResolution / 2, 0);
    draw_sprite_xpm(back3, 0, mode_info.YResolution / 2);
    draw_sprite_xpm(back4, mode_info.XResolution / 2, mode_info.YResolution / 2);
    printf("matrix[0][0]->block: %d\n", matrix[0][0].block);
    if (!block1)
    {
        process_button1(cards, j);
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

void draw_game_menu_game_4()
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
        draw_sprite_xpm(&matrix[0][0], 0, 0);
    }
    if (!backBlock2)
    {
        process_deck2();
    }
    else if (backBlock2)
    {
        draw_sprite_xpm(&matrix[0][1], mode_info.XResolution / 4, 0);
    }
    if (!backBlock3)
    {
        process_deck3();
    }
    else if (backBlock3)
    {
        draw_sprite_xpm(&matrix[0][2], mode_info.XResolution / 2, 0);
    }
    if (!backBlock4)
    {
        process_deck4();
    }
    else if (backBlock4)
    {
        draw_sprite_xpm(&matrix[0][3], 3 * mode_info.XResolution / 4, 0);
    }
    if (!backBlock5)
    {
        process_deck5();
    }
    else if (backBlock5)
    {
        draw_sprite_xpm(&matrix[1][0], 0, mode_info.YResolution / 4);
    }
    if (!backBlock6)
    {
        process_deck6();
    }
    else if (backBlock6)
    {
        draw_sprite_xpm(&matrix[1][1], mode_info.XResolution / 4, mode_info.YResolution / 4);
    }
    if (!backBlock7)
    {
        process_deck7();
    }
    else if (backBlock7)
    {
        draw_sprite_xpm(&matrix[1][2], mode_info.XResolution / 2, mode_info.YResolution / 4);
    }
    if (!backBlock8)
    {
        process_deck8();
    }
    else if (backBlock8)
    {
        draw_sprite_xpm(&matrix[1][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 4);
    }
    if (!backBlock9)
    {
        process_deck9();
    }
    else if (backBlock9)
    {
        draw_sprite_xpm(&matrix[2][0], 0, mode_info.YResolution / 2);
    }
    if (!backBlock10)
    {
        process_deck10();
    }
    else if (backBlock10)
    {
        draw_sprite_xpm(&matrix[2][1], mode_info.XResolution / 4, mode_info.YResolution / 2);
    }
    if (!backBlock11)
    {
        process_deck11();
    }
    else if (backBlock11)
    {
        draw_sprite_xpm(&matrix[2][2], mode_info.XResolution / 2, mode_info.YResolution / 2);
    }
    if (!backBlock12)
    {
        process_deck12();
    }
    else if (backBlock12)
    {
        draw_sprite_xpm(&matrix[2][3], 3 * mode_info.XResolution / 4, mode_info.YResolution / 2);
    }
    if (!backBlock13)
    {
        process_deck13();
    }
    else if (backBlock13)
    {
        draw_sprite_xpm(&matrix[3][0], 0, 3 * mode_info.YResolution / 4);
    }
    if (!backBlock14)
    {
        process_deck14();
    }
    else if (backBlock14)
    {
        draw_sprite_xpm(&matrix[3][1], mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
    }
    if (!backBlock15)
    {
        process_deck15();
    }
    else if (backBlock15)
    {
        draw_sprite_xpm(&matrix[3][2], mode_info.XResolution / 2, 3 * mode_info.YResolution / 4);
    }
    if (!backBlock16)
    {
        process_deck16();
    }
    else if (backBlock16)
    {
        draw_sprite_xpm(&matrix[3][3], 3 * mode_info.XResolution / 4, 3 * mode_info.YResolution / 4);
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
    case GAME_8_2:
        draw_sprite_xpm(hand, mouse_info.x, mouse_info.y);
        break;
    case GAME_16_2:
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

void animation_trigger()
{
    if (!isAnimating)
    {
        // Start the animation
        animationFrame = 0;
        isAnimating = true;
    }
}
