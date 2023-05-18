#include "model.h"

// Variáveis externas importantes à construção e manipulação do modelo
extern uint8_t scancode;
extern uint8_t byte_index;
SystemState systemState = RUNNING;
MenuState menuState = START;
extern MouseInfo mouse_info;
extern vbe_mode_info_t mode_info;
extern real_time_info time_info;

// Objetos a construir e manipular com a mudança de estados
Sprite *mouse;
Sprite *hand;
Sprite *smile;
Sprite *teste;
Sprite *logo;
Sprite *quitButton;
Sprite *quitButtonPressed;
Sprite *button1;
Sprite *button2;
Sprite *button3;
Sprite *button4;
Sprite *number1;
Sprite *number2;
Sprite *number3;
Sprite *number4;
Sprite *number5;
Sprite *number6;
Sprite *number7;
Sprite *number8;
Sprite *back;
Sprite *back_anim1;
Sprite *back_anim2;
Sprite *back_anim3;
Sprite *back_anim4;
Sprite *game;
Sprite *start;
Sprite *hard;
Sprite *easy;
Sprite *medium;
Sprite *quit;

// Contador de interrupções do timer
int timer_interrupts = 0;

// Criação dos objetos via XPM e via comum
void setup_sprites()
{
    mouse = create_sprite_xpm((xpm_map_t)mouse_xpm);
    hand = create_sprite_xpm((xpm_map_t)hand_xpm);
    smile = create_sprite_xpm((xpm_map_t)smile_xpm);
    teste = create_sprite_xpm((xpm_map_t)teste_xpm);
    logo = create_sprite_xpm((xpm_map_t)logo_xpm);
    number1 = create_sprite_xpm((xpm_map_t)number1_xpm);
    number2 = create_sprite_xpm((xpm_map_t)number2_xpm);
    number3 = create_sprite_xpm((xpm_map_t)number3_xpm);
    number4 = create_sprite_xpm((xpm_map_t)number4_xpm);
    number5 = create_sprite_xpm((xpm_map_t)number5_xpm);
    number6 = create_sprite_xpm((xpm_map_t)number6_xpm);
    number7 = create_sprite_xpm((xpm_map_t)number7_xpm);
    number8 = create_sprite_xpm((xpm_map_t)number8_xpm);
    back = create_sprite_xpm((xpm_map_t)back_xpm);
    game = create_sprite_xpm((xpm_map_t)game_xpm);
    start = create_sprite_xpm((xpm_map_t)start_xpm);
    easy = create_sprite_xpm((xpm_map_t)easy_xpm);
    medium = create_sprite_xpm((xpm_map_t)medium_xpm);
    hard = create_sprite_xpm((xpm_map_t)hard_xpm);
    quit = create_sprite_xpm((xpm_map_t)quit_xpm);
    button1 = create_sprite_button(mode_info.XResolution / 2, mode_info.YResolution / 2, ORANGE);
    button2 = create_sprite_button(mode_info.XResolution / 2, mode_info.YResolution / 2, BLUE);
    button3 = create_sprite_button(mode_info.XResolution / 2, mode_info.YResolution / 2, GREEN);
    button4 = create_sprite_button(mode_info.XResolution / 2, mode_info.YResolution / 2, YELLOW);
    quitButton = create_sprite_xpm((xpm_map_t)quitButton_xpm);
    quitButtonPressed = create_sprite_xpm((xpm_map_t)quitButtonPressed_xpm);
    easy = create_sprite_xpm((xpm_map_t)easy_xpm);
    medium = create_sprite_xpm((xpm_map_t)medium_xpm);
    hard = create_sprite_xpm((xpm_map_t)hard_xpm);
    quit = create_sprite_xpm((xpm_map_t)quit_xpm);
    start = create_sprite_xpm((xpm_map_t)start_xpm);
    back_anim1 = create_sprite_xpm((xpm_map_t)back_anim1_xpm);
    back_anim2 = create_sprite_xpm((xpm_map_t)back_anim2_xpm);
    back_anim3 = create_sprite_xpm((xpm_map_t)back_anim3_xpm);
    back_anim4 = create_sprite_xpm((xpm_map_t)back_anim4_xpm);
}

// É boa prática antes de acabar o programa libertar a memória alocada
void destroy_sprites()
{
    destroy_sprite(game);
    destroy_sprite(mouse);
    destroy_sprite(hand);
    destroy_sprite(smile);
    destroy_sprite(teste);
    destroy_sprite(number1);
    destroy_sprite(number2);
    destroy_sprite(number3);
    destroy_sprite(number4);
    destroy_sprite(number5);
    destroy_sprite(number6);
    destroy_sprite(number7);
    destroy_sprite(back);
    destroy_sprite(button1);
    destroy_sprite(button2);
    destroy_sprite(button3);
    destroy_sprite(button4);
    destroy_sprite(quitButton);
    destroy_sprite(quitButtonPressed);
    destroy_sprite(back);
    destroy_sprite(easy);
    destroy_sprite(medium);
    destroy_sprite(hard);
    destroy_sprite(quit);
    destroy_sprite(start);
    destroy_sprite(back_anim1);
    destroy_sprite(back_anim2);
    destroy_sprite(back_anim3);
    destroy_sprite(back_anim4);
}

// Na altura da interrupção há troca dos buffers e incremento do contador
void update_timer_state()
{
    if (DOUBLE_BUFFER)
        swap_buffers();
    timer_interrupts++;
}

// Como o Real Time Clock é um módulo mais pesado,
// devemos só atualizar os valores quando passa um segundo
void update_rtc_state()
{
    if (timer_interrupts % GAME_FREQUENCY == 0)
        rtc_update_time();
}

// Sempre que uma nova tecla é pressionada há avaliação do scancode.
// No caso do Template o teclado influencia:
// - o systemState: se Q for pressionado, leva ao fim do programa
// - o menuState: se S, G, E forem pressionados, leva a um dos menus (start, game, end) disponíveis
void update_keyboard_state()
{
    (kbc_ih)();
    switch (scancode)
    {
    case Q_KEY:
        systemState = EXIT;
        break;
    case S_KEY:
        menuState = START;
        break;
    case G_KEY:
        menuState = GAME;
        break;
    case E_KEY:
        menuState = END;
        break;
    case I_KEY:
        menuState = GAME_2;
        break;
    case H_KEY:
        menuState = GAME_3;
        break;
    case J_KEY:
        menuState = GAME_4_2;
        break;
    default:
        break;
    }
    draw_new_frame();
}

// Sempre que há um novo pacote completo do rato
// - muda o seu estado interno (x, y, left_pressed, right_pressed) - mouse_sync_info();
// - pode mudar o estado do botão por baixo dele - update_buttons_state();
void update_mouse_state()
{
    (mouse_ih)();
    mouse_sync_bytes();
    if (byte_index == 3)
    {
        mouse_sync_info();
        update_buttons_state();
        draw_new_frame();
        byte_index = 0;
    }
}

// Se o rato tiver o botão esquerdo pressionado (mouse_info.left_click) então
// muda o estado do botão no mesmo quadrante
// Senão, todos os botões voltam a não estar pressionados (buttonX->pressed = 0;)
void update_buttons_state()
{

    if (mouse_info.left_click)
    {

        if (mouse_info.x < mode_info.XResolution / 2 && mouse_info.y < mode_info.YResolution / 2)
            button1->pressed = 1;

        if (mouse_info.x >= mode_info.XResolution / 2 && mouse_info.y <= mode_info.YResolution / 2)
            button2->pressed = 1;

        if (mouse_info.x < mode_info.XResolution / 2 && mouse_info.y >= mode_info.YResolution / 2)
            button3->pressed = 1;

        if (mouse_info.x >= mode_info.XResolution / 2 && mouse_info.y > mode_info.YResolution / 2)
            button4->pressed = 1;
    }
    else
    {
        button1->pressed = 0;
        button2->pressed = 0;
        button3->pressed = 0;
        button4->pressed = 0;
    }
}
