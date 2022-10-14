#include "functions2.h"
#include <allegro5/allegro.h>
#include <stdio.h>

void func1(void) {
  printf("Function 1!\n");
}

void func2(void) {
  printf("Function 2!\n");
}


void allegro_inicializar(void) {
    if(!al_init())
    {
        printf("couldn't initialize allegro\n");
        //return 1;
    }
}

void install_keyboard_sm(void) {
    if(!al_install_keyboard())
    {
        printf("couldn't initialize keyboard\n");
        //return 1;
    }
}

void boost_graphics_sm(void) {
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
}
