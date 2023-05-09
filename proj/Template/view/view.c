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
int chosen;

// Alocação de memória ao(s) buffer(s)
// Se houver só um buffer, esse é o principal
// Se houver double buffering, há um secundário a alocar a mesma quantidade de memória que serve
// exclusivamente para o desenho
int set_frame_buffers(uint16_t mode) {
    if (set_frame_buffer(mode, &main_frame_buffer)) return 1;
    frame_buffer_size = mode_info.XResolution * mode_info.YResolution * ((mode_info.BitsPerPixel + 7) / 8);
    if (DOUBLE_BUFFER) {
        secondary_frame_buffer = (uint8_t *) malloc(frame_buffer_size);
        drawing_frame_buffer = secondary_frame_buffer;
    } else {
        drawing_frame_buffer = main_frame_buffer;
    }
    return 0;
}

void clear_draw_buffer() { 
    memset(main_frame_buffer,0xFFFFFF,mode_info.XResolution*mode_info.YResolution*((mode_info.BitsPerPixel+7)/8));
}

// Double buffering
// Cópia para o frame buffer principal do frame construído desde a última atualização
// Otimizaçṍes: 
// A) como o swap é uma operação muito frequente, é melhor não estar  a calcular frame_buffer_size sempre. 
// Assim opta-se por uma variável global, que é constante ao longo da execução e calculada 1 vez na linha 30.
// Poupa-se (frequência * (2 multiplicações + 1 soma + 1 divisão)) operações por cada segundo.
// B) só vale a pena dar display do RTC quando passa um segundo
void swap_buffers() {
    memcpy(main_frame_buffer, secondary_frame_buffer, frame_buffer_size);
    if (timer_interrupts % GAME_FREQUENCY == 0) display_real_time();
}

// A construção de um novo frame é baseado:
// - no estado atual do modelo (menuState, mouse_info, mode_info, buttonX->pressed...);
// - no Algoritmo do Pintor - https://pt.wikipedia.org/wiki/Algoritmo_do_pintor
// A ideia é colocar no buffer primeiro o plano mais longe do observador (a cor do fundo) e só depois 
// os objetos em cima, no caso do cursor e / ou dos botões
void draw_new_frame() {
    switch (menuState) {
        case START:
            draw_initial_menu();
            break;
        case GAME:
            draw_game_menu();
            break;
        case END:
            draw_finish_menu();
            break;
    }
    draw_mouse();
}

// O menu inicial é apenas um retângulo com tamanho máximo, com um smile ao centro
void draw_initial_menu() {
    draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 0xFFFFFF, drawing_frame_buffer);
    draw_sprite_button(button1, 0, 0);
    draw_sprite_button(button2, mode_info.XResolution/2, 0);
    draw_sprite_button(button3, 0, mode_info.YResolution/2);
    draw_sprite_button(button4, mode_info.XResolution/2, mode_info.YResolution/2);
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
int aux2= 0;
int aux3 = 0; 
int aux4 = 0;
int pre = 0;
int j = 0;
int k = 0;
Sprite matrix[2][2];
int id_sprite1; 
int id_sprite2; 
int id_sprite3; 
int id_sprite4;

int get_number(Sprite *cards,int size) {

    int random_number = rand() % size;
    return random_number;
}
void shuffle(Sprite *cards, int size) 
{
    srand(time(NULL));
    for (int i = size -1; i >= 0; i--) {
        int j = rand() % (i + 1); 
        Sprite temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
    
    matrix[0][0] = cards[0];
    matrix[0][1] = cards[1];
    matrix[1][0] = cards[2];
    matrix[1][1] = cards[3];
    //how can I compare the values  ? 
    // Compare all elements in the matrix
for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
        // Compare the current element to all other elements in the matrix
        for (int k = 0; k < 2; k++) {
            for (int l = 0; l < 2; l++) {
                // If the current element is not being compared to itself and has the same id as another element,
                // print a message indicating that there is a match
                if (i != k || j != l) {
                    if (matrix[i][j].id == matrix[k][l].id) {
                        printf("Match found: matrix[%d][%d].id = %d and matrix[%d][%d].id = %d\n",
                            i, j, matrix[i][j].id, k, l, matrix[k][l].id);
                    }
                }
            }
        }
    }
}



    
}

void process_button1(Sprite *cards, int size) { 
    if(button1->pressed) {
        button1Pressed = true; 
        counter_cards++;
    }
    if(button1Pressed) { 
        
        draw_sprite_xpm(&matrix[0][0], 0, 0);
        if(counter_cards == 2 && (matrix[0][0].id == matrix[0][1].id)) 
        { 
            menuState = END;
        }
        else if(counter_cards == 2 && (matrix[0][0].id != matrix[0][1].id)) 
        { 
            button2Pressed = false;
            button1Pressed = false;
            counter_cards = 0;
        }
        if(counter_cards == 2 && (matrix[0][0].id == matrix[1][0].id))
        {
            menuState = END;
        }
        else if(counter_cards == 2 && (matrix[0][0].id != matrix[1][0].id))
        {
            button1Pressed = false; 
            button3Pressed = false; 
            counter_cards = 0;
        }
        if(counter_cards == 2 && (matrix[0][0].id == matrix[1][1].id)) 
        {
            menuState = END;
        }
        else if(counter_cards == 2 && (matrix[0][0].id != matrix[1][1].id))
        {
            button1Pressed = false; 
            button4Pressed = false; 
            counter_cards = 0;
        }
       
    }
}
void process_button2(Sprite *cards, int size){
    if(button2->pressed) {
       button2Pressed = true; 
       counter_cards++;
       
    }
    
    if(button2Pressed){      
    
        draw_sprite_xpm(&matrix[0][1], mode_info.XResolution/2, 0);
        
        if(counter_cards == 2 && (matrix[0][0].id == matrix[0][1].id)) 
        { 
            menuState = END;
        }
        else if(counter_cards == 2 && (matrix[0][0].id != matrix[0][1].id)) 
        { 
            button2Pressed = false;
            button1Pressed = false;
            counter_cards = 0;
        }
        if(counter_cards == 2 && (matrix[0][1].id == matrix[1][0].id))
        {
            menuState = END;
        }
        else if(counter_cards == 2 && (matrix[0][1].id != matrix[1][0].id))
        {
            button2Pressed = false; 
            button3Pressed = false; 
            counter_cards = 0;
        }
        if(counter_cards == 2 && (matrix[0][1].id == matrix[1][1].id))
        {
            menuState = END;
        }
        else if(counter_cards == 2 && (matrix[0][1].id != matrix[1][1].id))
        {
            button2Pressed = false; 
            button4Pressed = false; 
            counter_cards = 0;
        }
        
    }
}

void process_button3(Sprite *cards, int size)
{   
    
    if(button3->pressed) {
        button3Pressed = true; 
        counter_cards++;
    }
    
    if(button3Pressed){ 
        draw_sprite_xpm(&matrix[1][0], 0, mode_info.YResolution/2);
        if(counter_cards == 2 && (matrix[0][0].id == matrix[1][0].id))
        {
            menuState = END;
        }
        else if(counter_cards == 2 && (matrix[0][0].id != matrix[1][0].id))
        {
            button3Pressed = false; 
            button1Pressed = false; 
            counter_cards = 0;
        }
        if(counter_cards == 2 && (matrix[0][1].id == matrix[1][0].id))
        {
            menuState = END;
        }
        else if(counter_cards == 2 && (matrix[0][1].id != matrix[1][0].id))
        {
            button3Pressed = false;
            button2Pressed = false; 
            counter_cards = 0;
        }
        if(counter_cards == 2 && (matrix[1][0].id == matrix[1][1].id))
        {
            menuState = END;
        }
        else if(counter_cards == 2 && (matrix[1][0].id != matrix[1][1].id))
        {
            button3Pressed = false; 
            button4Pressed = false; 
            counter_cards = 0;
        }
    }

}

void process_button4(Sprite *cards,int size) 
{
    if(button4->pressed) {
        button4Pressed = true; 
        counter_cards++;
    }
    
    if(button4Pressed){ 
        draw_sprite_xpm(&matrix[1][1], mode_info.XResolution/2, mode_info.YResolution/2);
        if(counter_cards == 2 && (matrix[0][0].id == matrix[1][1].id)) 
        {
            menuState = END;
        }
        else if(counter_cards == 2 && (matrix[0][0].id != matrix[1][1].id))
        {
            button1Pressed = false; 
            button4Pressed = false; 
            counter_cards = 0;
        }
        if(counter_cards == 2 && (matrix[0][1].id == matrix[1][1].id))
        {
            menuState = END;
        }
        else if(counter_cards == 2 && (matrix[0][1].id != matrix[1][1].id))
        {
            button2Pressed = false; 
            button4Pressed = false; 
            counter_cards = 0;
        }
        if(counter_cards == 2 && (matrix[1][0].id == matrix[1][1].id))
        {
            menuState = END;
        }
        else if(counter_cards == 2 && (matrix[1][0].id != matrix[1][1].id))
        {
            button3Pressed = false; 
            button4Pressed = false; 
            counter_cards = 0;
        }
        
    }
}



// O menu do jogo é constituído por quatro botões
void draw_game_menu() {
    Sprite cards[] = {*mouse,*mouse,*smile,*smile};
    int j = sizeof(cards) / sizeof(cards[0]);
    if(pre == 0){
        shuffle(cards,j);
        pre++;
    }
    
    
    draw_sprite_button(button1, 0, 0);
    draw_sprite_button(button2, mode_info.XResolution/2, 0);
    draw_sprite_button(button3, 0, mode_info.YResolution/2);
    draw_sprite_button(button4, mode_info.XResolution/2, mode_info.YResolution/2);
    
    
    process_button1(cards,j); 
    process_button2(cards,j);
    process_button3(cards,j);    
    process_button4(cards,j); 
}
    

// O menu final é apenas um retângulo com tamanho máximo, com um smile ao centro
void draw_finish_menu() {
    draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, DARKBLUE, drawing_frame_buffer);
    draw_sprite_xpm(smile, mode_info.XResolution/2 - 100, mode_info.YResolution/2 - 100);
}

// O cursor mode ter dois estados:
// - "normal", quando está no menu de início ou de fim
// - "mão", quando está no menu com os botões
void draw_mouse() {
    switch (menuState) {
        case START: case END:
            draw_sprite_xpm(mouse, mouse_info.x, mouse_info.y);
            break;
        case GAME:
            draw_sprite_xpm(hand, mouse_info.x, mouse_info.y);
            break;
    }
}

// A função recebe um objeto Sprite proveniente de um XPM e mostra-o nas coordenadas (x, y)
// Usa as cores dinamicamente alocadas na altura da construção
// A função ignora a cor transparente do XPM para não modificar o fundo quando não é preciso
int draw_sprite_xpm(Sprite *sprite, int x, int y) { 
    uint16_t height = sprite->height;
    uint16_t width = sprite->width;
    uint32_t current_color;
    for (int h = 0 ; h < height ; h++) {
      for (int w = 0 ; w < width ; w++) {
        current_color = sprite->colors[w + h*width];
        if (current_color == TRANSPARENT) continue;
        if (draw_pixel(x + w, y + h, current_color, drawing_frame_buffer) != 0) return 1;
      }
    }
    return 0; 
}


// A função recebe um objeto Sprite de cor constante e mostra-o nas coordenadas (x, y)
// Usa apenas uma cor, alocada na altura da construção
// A função ignora a cor transparente do XPM para não modificar o fundo quando não é preciso
int draw_sprite_button(Sprite *sprite, int x, int y) { 
    uint16_t height = sprite->height;
    uint16_t width = sprite->width;
    uint32_t color = sprite->color; 
    //1 º quadrante -> Leva para o start 
    //2 º quadrante -> Leva para o game  
    // 3 º quadrante -> Leva para o end 
    // 4 º quadrante -> Leva para o exit
    if(menuState == START){
    if(sprite->pressed == 1)
    { 
        if(mouse_info.x > 0 && mouse_info.x < mode_info.XResolution/2 && mouse_info.y > 0 && mouse_info.y < mode_info.YResolution/2)
        {
            
            menuState = START;
        }
        else if(mouse_info.x > mode_info.XResolution/2 && mouse_info.x < mode_info.XResolution && mouse_info.y > 0 && mouse_info.y < mode_info.YResolution/2)
        {
            menuState = GAME;
        }
        else if(mouse_info.x > 0 && mouse_info.x < mode_info.XResolution/2 && mouse_info.y > mode_info.YResolution/2 && mouse_info.y < mode_info.YResolution)
        {
            menuState = END;
        }
        else if(mouse_info.x > mode_info.XResolution/2 && mouse_info.x < mode_info.XResolution && mouse_info.y > mode_info.YResolution/2 && mouse_info.y < mode_info.YResolution)
        {
            systemState = EXIT;
        }

    }
    }
   
    for (int h = 0 ; h < height ; h++) {
      for (int w = 0 ; w < width ; w++) {
        if (draw_pixel(x + w, y + h, color, drawing_frame_buffer) != 0) return 1;
      }
    }
    return 0; 
}

// Faz o display do tempo real num formato amigável
// No caso do Template esta função apenas retorna uma string para o ficheiro output.txt
// Em projetos pode ser mudada para invocar sprites que coloquem no ecrã os respetivos dígitos
void display_real_time() {
    printf("NOW: %d/%d/%d @%d:%d:%d\n", 2000 + time_info.year, time_info.month, time_info.day, time_info.hours, time_info.minutes, time_info.seconds);
}

void draw_xpm_draw_buffer(xpm_map_t xpm, uint16_t x, uint16_t y) 
{
    xpm_image_t img; 
    uint32_t *colors = (uint32_t *)xpm_load(xpm,XPM_8_8_8_8, &img);
    for(int h = 0; h < img.height ; h++)
    {
        for(int w = 0; w < img.width ; w++)
        {
            if((uint32_t) &colors[w + h*img.width] == 0xfffffe) return; 
            if(x >= mode_info.XResolution || y >= mode_info.YResolution) return;
            memcpy(&drawing_frame_buffer[(mode_info.XResolution*(y+h)+(x+w))*(mode_info.BitsPerPixel+7)/8],&colors[w+h*img.width],(mode_info.BitsPerPixel+7)/8);
        }
    }
    return;

}
