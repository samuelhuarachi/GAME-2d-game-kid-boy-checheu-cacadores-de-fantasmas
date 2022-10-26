#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <math.h>
#include <array>
#include <iterator>

using namespace std;

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
#include <cstdlib>

#include "global_variables.cpp"
#include "clouds.cpp"
#include "ghosts.cpp"
#include "personagem.cpp"
#include "floor.cpp"
#include "functions.h"
#include "introduction.cpp"
#include "physical.h"



// tutorial allegro 5 https://github.com/liballeg/allegro_wiki/wiki/Allegro-Vivace%3A-Graphics
// physics 2D => http://chipmunk-physics.net/release/ChipmunkLatest-Docs/#Intro-HelloChipmunk

void defaultLoad() {
    allegro_inicializar();
    install_keyboard_sm();
    al_init_primitives_addon();
    boost_graphics_sm();
    al_install_audio();
    al_init_acodec_addon();
}

bool isMovingRight(int key) {


    if (key) {
        return true;
    }

    return false;
}

bool isMovingLeft(int key) {

    if (key) {
        return true;
    }

    return false;
}

void processDelay() {
    if (CURRENT_MAX_GLOBAL_DELAY > MAX_GLOBAL_DELAY) {
        CURRENT_MAX_GLOBAL_DELAY = 0;
    } else {
        CURRENT_MAX_GLOBAL_DELAY = CURRENT_MAX_GLOBAL_DELAY + 1;
    }
}

void moveMapToLeft() {
    MAP_MOVE = MAP_MOVE - MAP_MOVE_SPEED;
}


void processMoveRight() {



    if(isMovingRight(key[ALLEGRO_KEY_D]) && isNotInLimitOfMovementHorizontally() ) {

        //bool colisionFloorVertically = check_colision_with_floor_vertically(Joao);
        bool colisionFloorVertically = false;

        if (!isMaxLimitMoveRight(Joao) & !colisionFloorVertically) {
            movePersonagemToRight(&Joao);
        } else if(!colisionFloorVertically) {
            moveMapToLeft();
        }

        Joao.direction = RIGHT;
    }
}

void processMoveLeft() {

    if(isMovingLeft(key[ALLEGRO_KEY_A]) && isNotInLimitOfMovementHorizontally()) {
                        // movendo para a esquerda

        //bool colision = check_colision_with_floor_vertically(Joao, -25);
        bool colision = false;

        if (MAP_MOVE < 0 & colision == false) {
            MAP_MOVE = MAP_MOVE + MAP_MOVE_SPEED;
        } else {
            if (colision == false) {
                Joao.x = Joao.x - 5;
            }
        }

        Joao.direction = LEFT;
    }
}

bool isMoveRightOrLeft() {
    if (key[ALLEGRO_KEY_A] || key[ALLEGRO_KEY_D]) {
        return true;
    }

    return false;
}

bool isPersonagemNotFallen() {
    if (Joao.state != PERSONAGEM_ACTIONS::FALLEN) {
        return true;
    }

    return false;
}

bool isPersonagemNotJump() {
    if (Joao.state != PERSONAGEM_ACTIONS::JUMP) {
        return true;
    }
    return false;
}

bool isDelayReadyForAction() {
    if (CURRENT_MAX_GLOBAL_DELAY == 0) {
        return true;
    }

    return false;
}


void processWalkingAndAnimationWalking() {

    if(isMoveRightOrLeft() &&
       isPersonagemNotFallen() &&
       isPersonagemNotJump()
       ) {

        Joao.state = PERSONAGEM_ACTIONS::WALKING;

        if (isDelayReadyForAction()) {

            controller_sprite_running(&Joao);
        }
    }
}

void inGamePressing() {

    processMoveRight();

    processMoveLeft();

    processWalkingAndAnimationWalking();
}

void processPersonagemJump() {

    if(
       key[ALLEGRO_KEY_SPACE] &&
       isPersonagemNotJump() &&
       isPersonagemNotFallen()
    ){

        Joao.state = PERSONAGEM_ACTIONS::JUMP;
        jumpPersonagem(&Joao);
    }
}

void inGameKeyDown() {

    processPersonagemJump();


    if( (key[ALLEGRO_KEY_A] || key[ALLEGRO_KEY_D]) && Joao.state == PERSONAGEM_ACTIONS::STOP) {

        if (key[ALLEGRO_KEY_A] && Joao.direction == PERSONAGEM_DIRECTIONS::RIGHT) {
            Joao.x = Joao.x - 3;
        }

        if (key[ALLEGRO_KEY_D] && Joao.direction == PERSONAGEM_DIRECTIONS::LEFT) {
            Joao.x = Joao.x + 3;
        }

        if (key[ALLEGRO_KEY_D]) {

        }

        if (Joao.state == PERSONAGEM_ACTIONS::FALLEN) {
            printf("fallen...");
        }

        if (Joao.state == PERSONAGEM_ACTIONS::STOP) {
            //printf("stop...");
        }

        if (Joao.state == PERSONAGEM_ACTIONS::JUMP) {
           printf("jump...");
        }

        if (Joao.state == PERSONAGEM_ACTIONS::WALKING) {
           printf("walking...");
        }
    }
}

void loadingImages() {
    moonImage = al_load_bitmap("./images/moon.png");
    joaoImage = al_load_bitmap("./images/joao_waiting.png");
    jowImage = al_load_bitmap("./images/jow.png");
    gleisonImage = al_load_bitmap("./images/gleison.png");
    pedroImage = al_load_bitmap("./images/pedro.png");
    kidBoyImage = al_load_bitmap("./images/kidboy.png");
    ghostImage = al_load_bitmap("./images/ghost.png");
    houseAbandonedImage = al_load_bitmap("./images/house_abandoned.png");
    tree1Image = al_load_bitmap("./images/tree1.png");
    tree2Image = al_load_bitmap("./images/tree2.png");
    floorImage = al_load_bitmap("./images/floor2.png");
    floor3Image = al_load_bitmap("./images/floor3.png");
    nightImage = al_load_bitmap("./images/night4.jpg");
    joaoRunningImage = al_load_bitmap("./images/joao_running.png");
    joaoFallImage = al_load_bitmap("./images/joao_fall.png");
    joaoJumpImage = al_load_bitmap("./images/joao_fall.png");
}

void introKeyDown() {

    if(key[ALLEGRO_KEY_SPACE]) {

        cutscene = CUTSCENE::INGAME;
        al_stop_sample(&intro_sound_kbc);
        al_destroy_sample(introAudio);

        array_clouds.clear();
        //loadCloudsPosition("map1.txt");
        loadGhostsPosition("map1.txt");
    }
}

void destroyImagesAndAnothers() {
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(moonImage);
    al_destroy_bitmap(joaoImage);
    al_destroy_bitmap(jowImage);
    al_destroy_bitmap(gleisonImage);
    al_destroy_bitmap(pedroImage);
    al_destroy_bitmap(kidBoyImage);
    al_destroy_bitmap(ghostImage);
    al_destroy_bitmap(houseAbandonedImage);
    al_destroy_bitmap(tree1Image);
    al_destroy_bitmap(tree2Image);
    al_destroy_bitmap(floorImage);
    al_destroy_bitmap(floor3Image);
    al_destroy_bitmap(nightImage);
    al_destroy_bitmap(joaoRunningImage);
    al_destroy_bitmap(joaoFallImage);

    array_clouds.clear();
    array_vertically_floor.clear();
}

/**
carrega o mapa do jogo para um vetor
*/
void loadMap(string txtFile) {
    FILE* input_file = fopen(txtFile.c_str(), "r");
    if (input_file == nullptr) {}
    unsigned char character = 0;

    int line = 0;
    int column = 0;

    char newLine = '\n';

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 10000; j++) {
            GAMEMAP[i][j] = MAP_AIR_INT;
        }
    }

    printf("%s", "Iniciando carregamento no mapa!\n");
    while (!feof(input_file)) {
        character = getc(input_file);

        if (character == newLine) {
            line++;
            column = 0;
        }

        if (character == MAP_AIR) {
            GAMEMAP[line][column] = MAP_AIR_INT;
        } else if (character == MAP_FLOOR) {
            GAMEMAP[line][column] = MAP_FLOOR_INT;
        } else if (character == MAP_INFINITE_FLOOR) {
            GAMEMAP[line][column] = MAP_INFINITE_FLOOR_INT;
        } else if (character == MAP_CLOUD) {
            GAMEMAP[line][column] = MAP_CLOUD_INT;
        } else if (character == MAP_GHOST) {
            GAMEMAP[line][column] = MAP_GHOST_INT;
        }

        column++;
    }
    printf("%s", "Mapa carregado!\n");
}


bool personagemCheckCollisionHorizontally(int mapLine, int mapColumn, int value) {
    int personagemLine = Joao.y;
    int personagemColumn = Joao.x;

    //&& mapColumn == personagemColumn
    //mapLine == personagemLine &&

    if (value == MAP_AIR_INT) {
        return false;
    }

    return true;
}

void handlePersonagemJump() {

    double timeDelay = 0.5;
    double initialVelocity = 30;
    double positionInitial = PhysicalMUV_S(
                                           Joao.gravity_aceleration,
                                           initialVelocity,
                                           Joao.JUMP_TIME - timeDelay);
    double positionFinal = PhysicalMUV_S(
                                         Joao.gravity_aceleration,
                                         initialVelocity,
                                         Joao.JUMP_TIME);
    double variation = positionFinal - positionInitial;

    if (variation < 0) {
        Joao.state = PERSONAGEM_ACTIONS::FALLEN;
        return;
    }

    Joao.y = Joao.y - variation;
    Joao.JUMP_TIME = Joao.JUMP_TIME + timeDelay;
}

void handlePersonagemFallen() {
    double timeDelay = 0.5;
    double initialVelocity = 30;

    double positionInitial = PhysicalMUV_S(
                                           Joao.gravity_aceleration,
                                           initialVelocity,
                                           Joao.JUMP_TIME - timeDelay);
    double positionFinal = PhysicalMUV_S(
                                         Joao.gravity_aceleration,
                                         initialVelocity,
                                         Joao.JUMP_TIME);
    double variation = positionFinal - positionInitial;

    spaceControlPersonagem.setVariation(variation);

    //Joao.y = Joao.y - variation;

    Joao.JUMP_TIME = Joao.JUMP_TIME + timeDelay;
}

void handlePersonagemFallenDirty() {

    double variation = spaceControlPersonagem.getVariation();
    double variationCount = spaceControlPersonagem.getVariationCount();

    double variationBetweensVariations = std::abs(std::abs(variation) - variationCount);

    if (variationBetweensVariations < 1) {
        Joao.y = Joao.y - variation;
        return;
    }

    Joao.y = Joao.y - (-1 * variationCount);
}

void personagemHandle(int mapLine, int mapColumn, int value) {

    /**
    corrigir o bug de quando ele pula no final das arestas


    */

    int personagemLine = Joao.y;
    int personagemColumn = Joao.x;

    if (Joao.state == PERSONAGEM_ACTIONS::JUMP) {
        handlePersonagemJump();
        return;
    }

    if (Joao.state == PERSONAGEM_ACTIONS::FALLEN) {
        handlePersonagemFallen();
        return;
    }

    bool isCollision = personagemCheckCollisionHorizontally(mapLine, mapColumn, value);

    if (!isCollision) {
        Joao.state = PERSONAGEM_ACTIONS::FALLEN;
        return;
    }

    Joao.JUMP_TIME = 0;

    if (Joao.state != PERSONAGEM_ACTIONS::WALKING) {
        Joao.state = PERSONAGEM_ACTIONS::STOP;
    }


    Joao.y = mapLine;
}

void personagemHandleDirty(int mapLine, int mapColumn, int value) {
    bool isCollision = false;
    if (Joao.state == PERSONAGEM_ACTIONS::FALLEN) {
        handlePersonagemFallenDirty();
        isCollision = personagemCheckCollisionHorizontally(mapLine, mapColumn, value);
    }

    if (isCollision) {
        cout << "colidiu";
        Joao.state == PERSONAGEM_ACTIONS::STOP;
    }

    spaceControlPersonagem.handle();
    cout << ".";
}

bool iCanHandlePersonagem(int mapLine, int mapColumn) {

    int personagemLine = Joao.y;
    int personagemColumn = Joao.x;

    int diffLine = std::abs(personagemLine-mapLine);

    int diffColumn = std::abs(personagemColumn - mapColumn);

    if (diffLine<= 5 && diffColumn <= 10) {
        return true;
    }

    return false;
}

void drawMap() {

    while (!floorImage) {
        floorImage = al_load_bitmap("./images/floor2.png");
    }


    int clayContinueI;
    while (!clayImage) {
        clayImage = al_load_bitmap("./images/clay.png");
    }

    int columnsVisionMin = 0 + ((MAP_MOVE * -1) / 20) + 1;
    int columnsVisionMax = 41 + ((MAP_MOVE * -1) / 20) + 1;

    int linesVisionMin = 0;
    int linesVisionMax = 60;
    int value;

    int result = GAMEMAP[0][0];

    al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 60, 0, "result %d", result);

    VERTICALLY_FLOOR position_vertically_floor;

    if (DEBUG_TIMES_TO_RUN_COUNTER >= DEBUG_TIMES_TO_RUN) {

      return;
    }

    // zera as posicoes tanto do chao, quanto do chao na vertical
    for (int i = 0; i < 1999; i++) {
        for (int j = 0; j < 1999; j++) {
            allFloor[i][j] = 0; // parece que uso para identificar colisões
            allVerticallyFloor[i][j] = 0; // parece que não estou usando
        }
    }

    int mapLine;
    int mapColumn;
    int iCanHandlePersonagemFlag = true;
    int iCanHandlePersonagemCount = 2;

    spaceControlPersonagem.setPristine(true);
    spaceControlPersonagem.setVariationCount(0);

    for (int line = linesVisionMin; line < linesVisionMax; line++) {
        for (int column = columnsVisionMin; column < columnsVisionMax; column++) {
            value = GAMEMAP[line][column];

            mapLine = line * 10 - 10;
            mapColumn = (column * 20) + MAP_MOVE - 20;

            bool spaceControlPersonagemPristine = spaceControlPersonagem.getPristine();
            bool spaceControlPersonagemIsHandleble = spaceControlPersonagem.isHandleble();

            if (spaceControlPersonagemPristine == false &&
                spaceControlPersonagemIsHandleble == true) {

                personagemHandleDirty(mapLine, mapColumn, value);
            }

            if (
                    iCanHandlePersonagemFlag == true &&
                    iCanHandlePersonagem(mapLine, mapColumn) &&
                    iCanHandlePersonagemCount > 1 &&
                    spaceControlPersonagemPristine == true
                )
                {

                personagemHandle(mapLine, mapColumn, value);

                iCanHandlePersonagemCount--;

                if (iCanHandlePersonagemCount < 0) {
                    iCanHandlePersonagemFlag = false;
                }

                cout << "###################################### \n";
                spaceControlPersonagem.setPristine(false);
            }


            if (value == MAP_FLOOR_INT) {
                if (floorImage) {
                    al_draw_bitmap(floorImage, (column * 20) - 20 + MAP_MOVE, (line * 10), 0);

                    for (int b = 0; b < 19; b++) {
                        allFloor[line * 10 - 10][column * 20 + b + MAP_MOVE] = 1;
                    }


                    position_vertically_floor.x = column * 20;
                    position_vertically_floor.y = (line * 10) - 10;
                    /**
                    provavel para encontrar a colisão no eixo vertical
                    */
                    //array_vertically_floor.push_back(position_vertically_floor);
                }
            }

            if (value == MAP_INFINITE_FLOOR_INT) {
                clayContinueI = ((GAME_HEIGHT - (line * 10)) / 20) + 2;

                for(int i = 0; i <= clayContinueI; i++ ) {

                    if (clayImage) {
                        al_draw_bitmap(clayImage, (column * 20) + MAP_MOVE - 20, 10 + ((line + i) * 10), 0);
                    }
                }
            }
        }
    }


    DEBUG_TIMES_TO_RUN_COUNTER++;
}

int main()
{

    spaceControlPersonagem.teste();

    /**
    Colocar uma variavel flag para apontar quantas vezes o mapa devera ser rederizado
    antes de sair do software.
    Isso para ajudar no debug do jogo.
    */

    /**
    Testando a funcao de fisica do jogo
    */
    double finalPosition1 = PhysicalMUV_S(-2.5, 15.0, 1.0);
    double finalPosition2 = PhysicalMUV_S(-2.5, 15.0, 2.0);
    double finalPosition3 = PhysicalMUV_S(-2.5, 15.0, 3.0);
    double finalPosition4 = PhysicalMUV_S(-2.5, 15.0, 4.0);
    double finalPosition5 = PhysicalMUV_S(-2.5, 15.0, 5.0);
    double finalPosition6 = PhysicalMUV_S(-2.5, 15.0, 6.0);

    double finalPosition7 = PhysicalMUV_S(-2.5, 15.0, 7.0);
    double finalPosition8 = PhysicalMUV_S(-2.5, 15.0, 8.0);
    double finalPosition9 = PhysicalMUV_S(-2.5, 15.0, 9.0);
    double finalPosition10 = PhysicalMUV_S(-2.5, 15.0, 10.0);
    double finalPosition11 = PhysicalMUV_S(-2.5, 15.0, 11.0);
    double finalPosition12 = PhysicalMUV_S(-2.5, 15.0, 12.0);

    printf("Final position %f \n", finalPosition1);
    printf("Final position %f \n", finalPosition2);
    printf("Final position %f \n", finalPosition3);
    printf("Final position %f \n", finalPosition4);
    printf("Final position %f \n", finalPosition5);
    printf("Final position %f \n", finalPosition6);

    printf("Final position %f \n", finalPosition7);
    printf("Final position %f \n", finalPosition8);
    printf("Final position %f \n", finalPosition9);
    printf("Final position %f \n", finalPosition10);
    printf("Final position %f \n", finalPosition11);
    printf("Final position %f \n", finalPosition12);

    array_clouds.clear();

    inicializePersonagem(&Joao);

    defaultLoad();

    al_reserve_samples(10);

    introAudio = al_load_sample("./sounds/intro.ogg");

    if (!introAudio) {
        printf("nao carregaou a musica de introducao");
    }

    joaoJumpSound = al_load_sample("./sounds/jump.ogg");
    if (!joaoJumpSound) {
        printf("nao carregaou o som de efeito do pulo");
    }

    timer = al_create_timer(1.0 / 60.0);
    queue = al_create_event_queue();

    //al_set_new_display_flags(ALLEGRO_FULLSCREEN);

    disp = al_create_display(800, GAME_HEIGHT);
    font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));


    bool done = false;
    bool redraw = true;

    ALLEGRO_EVENT event;

    al_start_timer(timer);

    if(!al_init_image_addon())
    {
        printf("couldn't initialize image addon\n");
        return 1;
    }

    loadingImages();

    ALLEGRO_KEYBOARD_STATE ks;
    #define KEY_SEEN     1
    #define KEY_RELEASED 2

    //unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    //ALLEGRO_MONITOR_INFO monitorInfo;
    //al_get_monitor_info(0, &monitorInfo);
    //al_set_new_display_flags(ALLEGRO_FULLSCREEN);

    /**
    carregando o mapa para o vetor
    */
    string fase1 = "map1.txt";
    loadMap(fase1);

    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER: // Pressionando a tecla
                redraw = true;

                if (cutscene == CUTSCENE::INGAME) {
                    inGamePressing();
                }


                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;


                break;

            case ALLEGRO_EVENT_KEY_DOWN: // key down na tecla
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;

                if (cutscene == CUTSCENE::INGAME) {
                    inGameKeyDown();
                }

                if (cutscene == CUTSCENE::INTRO) {

                    introKeyDown();
                }

                break;
            case ALLEGRO_EVENT_KEY_UP: // key up na tecla

                if (cutscene == CUTSCENE::INGAME) {


                    if(  key[ALLEGRO_KEY_A] || key[ALLEGRO_KEY_D]  ) {


                        if (Joao.state != PERSONAGEM_ACTIONS::FALLEN && Joao.state != PERSONAGEM_ACTIONS::JUMP) {
                            Joao.state = PERSONAGEM_ACTIONS::STOP;
                        }

                        Joao.CURRENT_SPRITE_RUNNING = 0;
                    }
                }

                key[event.keyboard.keycode] &= KEY_RELEASED;

                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue)) // renderiza imagens
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));


            //al_draw_text(font, al_map_rgb(255, 255, 255), 10, 5, 0, "KBC Game v0.0.1");


            if (cutscene == CUTSCENE::INGAME) {

                /*
                if (nightImage) {
                    al_draw_bitmap(nightImage, 0, 0, 0);
                }*/


                // draw moon
                if (moonImage) {
                    al_draw_bitmap(moonImage, 369, 167, 0);
                }


                //moveClouds(MAP_MOVE);

                // drawFloor("map1.txt", MAP_MOVE);

                processDelay();
                drawMap();

                // draw joao
                if (joaoImage) {
                    if (Joao.direction == LEFT && Joao.state == PERSONAGEM_ACTIONS::STOP) {
                        al_draw_bitmap_region(joaoImage, 0, 0, 64, 64, Joao.x - 15, Joao.y - 54, ALLEGRO_FLIP_HORIZONTAL );
                    } else if (Joao.direction == RIGHT && Joao.state == PERSONAGEM_ACTIONS::STOP) {
                        al_draw_bitmap_region(joaoImage, 0, 0, 64, 64, Joao.x - 15, Joao.y - 54, 0);
                    }
                }

                if (Joao.state == PERSONAGEM_ACTIONS::WALKING && Joao.direction == RIGHT && joaoRunningImage) {


                    al_draw_bitmap_region(joaoRunningImage, (Joao.CURRENT_SPRITE_RUNNING * 64), 0, 64, 64, Joao.x - 15, Joao.y - 54, 0);
                }

                if (Joao.state == PERSONAGEM_ACTIONS::WALKING && Joao.direction == LEFT && joaoRunningImage) {
                    al_draw_bitmap_region(joaoRunningImage, (Joao.CURRENT_SPRITE_RUNNING * 64), 0, 64, 64, Joao.x - 15, Joao.y - 54, ALLEGRO_FLIP_HORIZONTAL);
                }

                if (Joao.state == PERSONAGEM_ACTIONS::FALLEN && Joao.direction == LEFT && joaoFallImage) {
                    al_draw_bitmap_region(joaoFallImage, 0, 0, 64, 64, Joao.x - 15, Joao.y - 54, ALLEGRO_FLIP_HORIZONTAL );
                }

                if (Joao.state == PERSONAGEM_ACTIONS::FALLEN && Joao.direction == RIGHT && joaoFallImage) {
                    al_draw_bitmap_region(joaoFallImage, 0, 0, 64, 64, Joao.x - 15, Joao.y - 54, 0 );
                }

                if (Joao.state == PERSONAGEM_ACTIONS::JUMP && Joao.direction == RIGHT && joaoJumpImage) {
                    al_draw_bitmap_region(joaoJumpImage, 0, 0, 64, 64, Joao.x - 15, Joao.y - 54, 0 );
                }

                if (Joao.state == PERSONAGEM_ACTIONS::JUMP && Joao.direction == LEFT && joaoJumpImage) {
                    al_draw_bitmap_region(joaoJumpImage, 0, 0, 64, 64, Joao.x - 15, Joao.y - 54, ALLEGRO_FLIP_HORIZONTAL);
                }



                //gravity_force(&Joao);

                ghosts_action(MAP_MOVE);


                //al_draw_circle(Joao.x, Joao.y, 3, al_map_rgb(255, 255, 255), 1);


                al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 20, 0, "X: %f", Joao.x);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 150, 20, 0, "Y: %f", Joao.y);


                al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 40, 0, "MAP_MOVE: %d", MAP_MOVE);




            }

            if (cutscene == CUTSCENE::INTRO) {
                intro_timer_controller();
                introduction_start(font);
            }

            al_flip_display();
            redraw = false;
        }
    }


    destroyImagesAndAnothers();



    return 0;
}
