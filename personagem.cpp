#include <iostream>



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


bool check_colision_with_floor(PERSONAGEM *p) {

    int y = p->y;   // vertically
    int x = p->x;   // horizontally
    int maxVertically = y + p->topAceleration;
    int maxHorizontallyRight = x + 25;
    int maxHorizontallyLeft  = x;

    //if (p->direction == PERSONAGEM_DIRECTIONS::LEFT) {
    //    x = x + 25;
    //}

    int countRight = x;
    int countRightVertically;

    int value2;



    //int* posicao2 = *GAMEMAP[0][0];


    if (p->direction == PERSONAGEM_DIRECTIONS::RIGHT) {

        // MAP_MOVE
        // GAMEMAP

        //al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 80, 0, "linha %d", y / 10 + 1);
       // al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 100, 0, "coluna %d", x);
       // al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 120, 0, "GAMEMAP %d", posicao2);


        return true;

        /** while (countRight <= maxHorizontallyRight) {


            countRightVertically = y;
            while (countRightVertically < maxVertically) {

                //if (allFloor[countRightVertically][countRight] == 1) {

                if (GAMEMAP[countRightVertically / 10][countRight / 20] == 1) {
                    p->y = countRightVertically;
                    return true;
                }
                countRightVertically++;
            }
            countRight++;
        } **/
    }


    int countLeft = x + 25;
    int coutLeftVertically;
    if (p->direction == PERSONAGEM_DIRECTIONS::LEFT) {

        while (countLeft >= maxHorizontallyLeft) {
            coutLeftVertically = y;
            while (coutLeftVertically < maxVertically) {
                if (allFloor[coutLeftVertically][countLeft] == 1) {
                    p->y = coutLeftVertically;
                    return true;
                }
                coutLeftVertically++;
            }
            countLeft--;
        }
    }

    return false;
}

bool isNotInLimitOfMovementHorizontally() {


    if (Joao.x < 0) {
        Joao.x = 0;
        return false;
    }

    return true;
}

bool check_samuel_position_y() {

    if (Joao.y > 590) {
        Joao.y = 590;
        return false;
    }

    return true;
}


bool check_colision_with_floor_vertically(PERSONAGEM p, int space = 20) {

    int playerPositionYLine   = p.y - 3;   // line
    int playerPositionXColumn = p.x + (MAP_MOVE * -1);  // column

    //printf("> %d <", x);

    //int extremeSideLeft = x + ;

    int verticallyFloorX;
    int verticallyFloorY;
    int verifyRange = 3;

    int firstPointX;
    int firstPointY;
    int secondPointX;
    int secondPointY;

    if (p.direction == PERSONAGEM_DIRECTIONS::LEFT) {
        for (VERTICALLY_FLOOR floor_vertically_position : array_vertically_floor) {
            verticallyFloorX = floor_vertically_position.x + 20;
            verticallyFloorY = floor_vertically_position.y;

            verifyRange = 5;
            while(verifyRange >= -5) {
                if (verticallyFloorX == (playerPositionXColumn - verifyRange)) {
                    firstPointX = verticallyFloorX;
                    firstPointY = verticallyFloorY;
                    secondPointX = verticallyFloorX;
                    secondPointY = verticallyFloorY + 20;

                    if (playerPositionYLine > firstPointY && playerPositionYLine <= secondPointY) {
                        return true;
                    }
                }
                verifyRange--;
            }
        }
    }

    if (p.direction == PERSONAGEM_DIRECTIONS::RIGHT) {
        for (VERTICALLY_FLOOR floor_vertically_position : array_vertically_floor) {
            verticallyFloorX = floor_vertically_position.x;
            verticallyFloorY = floor_vertically_position.y;

            verifyRange = 5;
            while(verifyRange >= -5) {
                if (verticallyFloorX == (playerPositionXColumn + 25 + verifyRange)) {
                    firstPointX = verticallyFloorX;
                    firstPointY = verticallyFloorY;
                    secondPointX = verticallyFloorX;
                    secondPointY = verticallyFloorY + 20;

                    if (playerPositionYLine > firstPointY && playerPositionYLine <= secondPointY) {
                        return true;
                    }
                }
                verifyRange--;
            }
        }
    }

    return false;
}


void gravity_force(PERSONAGEM *p) {
    int personagem_y_position = p->y;
    bool _isCollision;

    if (p->state == PERSONAGEM_ACTIONS::WALKING) {
        _isCollision = check_colision_with_floor(p);

        if (_isCollision == false) {
            p->state = PERSONAGEM_ACTIONS::FALLEN;
        }
    }

    if (p->state != PERSONAGEM_ACTIONS::STOP) {
        _isCollision = check_colision_with_floor(p);
    }

    if (p->state == PERSONAGEM_ACTIONS::JUMP) {

        p->y = personagem_y_position -  p->aceleration;
        p->aceleration = p->aceleration - 1;

        if (p->aceleration <= 0) {
            p->state = PERSONAGEM_ACTIONS::FALLEN;
        }
    }

    if (p->state == PERSONAGEM_ACTIONS::FALLEN) {

        if (_isCollision == true) {
            p->state = PERSONAGEM_ACTIONS::STOP;
        } else {
            p->y = personagem_y_position +  p->aceleration;

            if (p->aceleration < p->topAceleration) {
                p->aceleration = p->aceleration + 1;
            }
        }
    }
}


void jump(PERSONAGEM *p) {
    if (p->state == PERSONAGEM_ACTIONS::STOP || p->state == PERSONAGEM_ACTIONS::WALKING) {
        p->state = PERSONAGEM_ACTIONS::JUMP;
        //Joao.y = Joao.y - 130;
    }
}

void movePersonagemToRight(PERSONAGEM *p) {
    p->x = p->x + 5;
}

bool isMaxLimitMoveRight(PERSONAGEM p) {
    if (Joao.x < MAX_PERSONAGEM_MOVE_RIGHT) {
        return false;
    }

    return true;
}

void jumpPersonagem(PERSONAGEM *p) {
    p->aceleration = 14; // aceleration = impulso para cima
}

void inicializePersonagem(PERSONAGEM *p) {
    p->x = 10;
    p->y = 100;
    p->topSpeed = 10;
    p->topAceleration = 5;
    p->speed = 0;
    p->aceleration = 0;
    p->time = 0;
}

