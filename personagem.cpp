#include <iostream>
#include "physical.h"

enum PERSONAGEM_ACTIONS {
    STOP,
    WALKING,
    JUMP,
    FALLEN
};

enum PERSONAGEM_DIRECTIONS {
    RIGHT,
    LEFT
};

typedef struct PERSONAGEM
{
    float x, y;
    float dx, dy;
    int type;
    float topSpeed;
    int topAceleration;
    int aceleration;
    float speed;
    float last_muv_s;
    float time;
    bool locked = false;
    float life = 100;
    PERSONAGEM_DIRECTIONS direction;
    PERSONAGEM_ACTIONS state = FALLEN;
    int MAX_SPRITE_RUNNING = 6;
    int CURRENT_SPRITE_RUNNING = 0;
    int imageWidth = 64;
    int imageHeight = 64;
    double JUMP_TIME = 12; /** por isso ele começa caindo no começo do jogo **/
    float initial_y_in_start_jump = 0; /** guarda a posicao y no inicio do pulo */
    double gravity_aceleration = -2.5;

} PERSONAGEM;
PERSONAGEM Joao;

int controller_sprite_running(PERSONAGEM *p) {
    p->CURRENT_SPRITE_RUNNING = p->CURRENT_SPRITE_RUNNING + 1;
    if (p->CURRENT_SPRITE_RUNNING >= p->MAX_SPRITE_RUNNING) {
        p->CURRENT_SPRITE_RUNNING = 0;
    }
    return p->CURRENT_SPRITE_RUNNING;
}

int find(int arr[], int len, int seek)
{
    for (int i = 0; i < len; ++i)
    {
        if (arr[i] == seek) return i;
    }
    return -1;
}

bool isNotInLimitOfMovementHorizontally() {
    if (Joao.x < 0) {
        Joao.x = 0;
        return false;
    }
    return true;
}

void jump(PERSONAGEM *p) {
    if (p->state == PERSONAGEM_ACTIONS::STOP || p->state == PERSONAGEM_ACTIONS::WALKING) {
        p->state = PERSONAGEM_ACTIONS::JUMP;
    }
}

bool isMaxLimitMoveRight(PERSONAGEM *p) {
    if (p->x < MAX_PERSONAGEM_MOVE_RIGHT) {
        return false;
    }
    return true;
}

void jumpPersonagem(PERSONAGEM *p) {
    p->time = p->time + 1.0;
    double v0 = 20.0;
    double s_position = PhysicalMUV_S(p->aceleration, v0, p->time);

    if (p->last_muv_s < s_position) {
         p->y = p->y - (s_position - p->last_muv_s);
         p->last_muv_s = s_position;
    } else {
        p->state = PERSONAGEM_ACTIONS::FALLEN;
        p->time = 0;
        p->last_muv_s = 0;
    }
}

void inicializePersonagem(PERSONAGEM *p) {
    p->x = 10;
    p->y = 80;
    p->topSpeed = 10;
    p->topAceleration = 5;
    p->speed = 0;
    p->aceleration = -1.6;
    p->time = 21;
    p->last_muv_s = 199;
}
