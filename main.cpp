/*
Observações:
O personagem anda de 5 em 5, aparentemente
*/
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
#include <cmath>
#include <tuple>
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
#include "menu.cpp"
// tutorial allegro 5 https://github.com/liballeg/allegro_wiki/wiki/Allegro-Vivace%3A-Graphics
// physics 2D => http://chipmunk-physics.net/release/ChipmunkLatest-Docs/#Intro-HelloChipmunk
/**
Essa funcao recebe o eixo x (eixo x, eixo das colunas) do personagem, e
retorna a posicao dele no snapshot do mapa
*/
int get_column_in_snapshot_by_hero_x(float hero_x) {
    int column;
    if (hero_x < 20) {
        column = 0;
    } else {
        column = (int)round(hero_x / 20);
    }

    return column;
}

int get_line_in_snapshot_by_hero_y(float hero_y) {
    float position = hero_y;
    return trunc((position / 10));
}

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

bool am_i_pressing_key(int key) {
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

bool can_i_move(PERSONAGEM *p) {
    /**
    Verificar se tem colisao com as paredes da direita (colisao vertical, apenas com elementos a 1, e 2 nivel do solo);
    */
    int REACH_FLOOR_AJUST_NIVEL_1 = -1;
    int REACH_FLOOR_AJUST_NIVEL_2 = -3;
    int column_snapshot;
    int MAP_AJUST_1 = 1;
    int MAP_AJUST_2 = 2;
    if (p->direction == PERSONAGEM_DIRECTIONS::LEFT) {
        MAP_AJUST_1 = -1;
        MAP_AJUST_2 = 0;
    }

    if (MAP_MOVE == 0) {
        column_snapshot = get_column_in_snapshot_by_hero_x(p->x) + MAP_AJUST_1;
    } else {
        column_snapshot = get_column_in_snapshot_by_hero_x(p->x) + MAP_AJUST_2;
    }

    int line_snapshot_lvl_1 = get_line_in_snapshot_by_hero_y(p->y) + REACH_FLOOR_AJUST_NIVEL_1;
    int line_snapshot_lvl_2 = get_line_in_snapshot_by_hero_y(p->y) + REACH_FLOOR_AJUST_NIVEL_2;
    int map_value_lvl_1 = map_snapshot[line_snapshot_lvl_1][column_snapshot];
    int map_value_lvl_2 = map_snapshot[line_snapshot_lvl_2][column_snapshot];

    if (map_value_lvl_1 == MAP_FLOOR_INT || map_value_lvl_2 == MAP_FLOOR_INT) {
        return false;
    }
    return isNotInLimitOfMovementHorizontally();
}

bool am_i_pressing_right_key() {
    return am_i_pressing_key(key[ALLEGRO_KEY_D]);
}

bool am_i_pressing_left_key() {
    return am_i_pressing_key(key[ALLEGRO_KEY_A]);
}


bool am_i_walking(PERSONAGEM *p) {
    return (p->state == PERSONAGEM_ACTIONS::WALKING);
}

void process_walking(PERSONAGEM *p) {

    /**
    That's part i'm check the floor collision
    **/
    if(isMoveRightOrLeft() &&
       isPersonagemNotFallen() &&
       isPersonagemNotJump()
       ) {

        p->state = PERSONAGEM_ACTIONS::WALKING;

        if (isDelayReadyForAction()) {
            controller_sprite_running(p);
        }

        /**
            floor collision check bellow
        */
        int REACH_FLOOR_AJUST = 2;
        int column_snapshot;
        if (p->direction == PERSONAGEM_DIRECTIONS::LEFT) {
            column_snapshot= get_column_in_snapshot_by_hero_x(p->x);
        } else {
            column_snapshot= get_column_in_snapshot_by_hero_x(p->x + 100.0);
        }

        int line_snapshot = get_line_in_snapshot_by_hero_y(p->y);
        int map_value = map_snapshot[line_snapshot + REACH_FLOOR_AJUST][column_snapshot];
        if (map_value == MAP_AIR_INT) {
            p->state = PERSONAGEM_ACTIONS::FALLEN;
        }
    }

    /**
    that's part i check vertical collision in right
    */
    if (am_i_pressing_right_key()) {
        p->direction = PERSONAGEM_DIRECTIONS::RIGHT;
        if (can_i_move(p)) {
            if (!isMaxLimitMoveRight(p)) {
                 p->x = p->x + 3.5;
            } else {
                MAP_MOVE = MAP_MOVE - MAP_MOVE_SPEED;
            }
        }
    }

    /**
    that's part i check vertical collision in left
    */
    if (am_i_pressing_left_key()) {
        p->direction = PERSONAGEM_DIRECTIONS::LEFT;
        if(can_i_move(p)) {
            if (MAP_MOVE < 0) {
                MAP_MOVE = MAP_MOVE + MAP_MOVE_SPEED;
            } else {
                p->x = p->x - 3.5;
            }
        }
    }
}

// in this point, you are holding some key
void holdingKey() {
    process_walking(&Joao);
}

void inGameKeyDown() {
    if(key[ALLEGRO_KEY_SPACE] &&
       isPersonagemNotJump() &&
       isPersonagemNotFallen())
    {
        Joao.state = PERSONAGEM_ACTIONS::JUMP;
        al_play_sample(SOUND_HERO_JUMP, 0.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, &SOUND_ID_HERO_JUMP);

    } else if(key[ALLEGRO_KEY_ESCAPE]) {
        cutscene = CUTSCENE::MENU;
    }
}

void loadingImages() {
    moonImage = al_load_bitmap("./images/moon4.png");
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
    MENU_BACKGROUND = al_load_bitmap("./images/kid_boy_menu_art.jpg");
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
    al_destroy_bitmap(MENU_BACKGROUND);
    al_destroy_sample(SOUND_HERO_JUMP);

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


void drawMap() {
    while (!floorImage) {
        floorImage = al_load_bitmap("./images/floor2.png");
    }

    int clayContinueI;
    while (!clayImage) {
        clayImage = al_load_bitmap("./images/clay.png");
    }

    int columnsVisionMin = ((MAP_MOVE * -1) / 20) + 1;
    int columnsVisionMax = 41 + ((MAP_MOVE * -1) / 20) + 1;
    int linesVisionMin = 0;
    int linesVisionMax = 60;
    int value;
    int result = GAMEMAP[0][0];

    al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 60, 0, "result %d", result);

    VERTICALLY_FLOOR position_vertically_floor;

    if (DEBUG_TIMES_TO_RUN_COUNTER >= DEBUG_TIMES_TO_RUN &&
        DEBUG_ACTIVATED == true) {
      return;
    }

    /*
    reset map snapshot
    */
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 41; j++) {
            map_snapshot[i][j] = 0;
        }
    }

    int mapLine;
    int mapColumn;
    int iCanHandlePersonagemFlag = true;
    int iCanHandlePersonagemCount = 2;

    /**
    para tratar o evento que irá acontecer quando tem a mudança de linha
    */
    int savePreviewsLine = -1;

    spaceControlPersonagem.setPristine(true);
    spaceControlPersonagem.setVariationCount(0);

    al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 70, 0, "columnsVisionMin %d", columnsVisionMin);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 80, 0, "columnsVisionMax %d", columnsVisionMax);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 90, 0, "columnsVisionDiff %d", columnsVisionMax - columnsVisionMin); // sempre está dando 41
    al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 100, 0, "linesVisionMin %d", linesVisionMin);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 110, 0, "linesVisionMax %d", linesVisionMax);

    for (int line = linesVisionMin; line < linesVisionMax; line++) {
        for (int column = columnsVisionMin; column < columnsVisionMax; column++) {
            value = GAMEMAP[line][column];

            mapLine = line * 10 - 10;
            mapColumn = (column * 20) + MAP_MOVE - 20;

            /*
            don't snapshot when hero stay stopped
            */
            map_snapshot[line][column - columnsVisionMin] = value;

            // desenho o chao
            if (value == MAP_FLOOR_INT) {
                if (floorImage) {
                    al_draw_bitmap(floorImage, (column * 20) - 20 + MAP_MOVE, (line * 10), 0);
                    position_vertically_floor.x = column * 20;
                    position_vertically_floor.y = (line * 10) - 10;
                }
            }

            // desenho a continuidade do chao
            if (value == MAP_INFINITE_FLOOR_INT) {
                clayContinueI = ((GAME_HEIGHT - (line * 10)) / 20) + 2;
                for(int i = 0; i <= clayContinueI; i++ ) {
                    if (clayImage) {
                        al_draw_bitmap(clayImage, (column * 20) + MAP_MOVE - 20, 10 + ((line + i) * 10), 0);
                    }
                }
            }

            savePreviewsLine = line;
        }
    }

    DEBUG_TIMES_TO_RUN_COUNTER++;
}

// tuple for return two answers (// analysis future path)
std::tuple<bool, int> __check_if_exists_future_collision(PERSONAGEM *p, int column) {
    int factor_fallen = 2;
    bool collision = false;

    // 2 - checking path (y axis)
    int positionAjustMinor = get_line_in_snapshot_by_hero_y(p->y);

    // 3 - finding collision
    for (int i = 0; i < factor_fallen; i++) {
        positionAjustMinor = positionAjustMinor + 1;
        int map_value = map_snapshot[positionAjustMinor][column];

        // collision detected
        if (map_value == MAP_FLOOR_INT) {
            collision = true;
            return  std::make_tuple(collision, positionAjustMinor);
        }
    }

    return  std::make_tuple(collision, positionAjustMinor);
}

void processing_hero_fallen() {
    // break pra nao cair infinito
    if (Joao.y >= 1200.0) {
        Joao.y = 1200.0;
        Joao.state = PERSONAGEM_ACTIONS::STOP;
        return;
    }

    // 1- checking column...
    int two_columns_check_1;
    int two_columns_check_2;
    two_columns_check_1 = get_column_in_snapshot_by_hero_x(Joao.x);
    two_columns_check_2 = get_column_in_snapshot_by_hero_x(Joao.x + 19);

    bool collision;
    int positionAjustMinor;
    tie(collision, positionAjustMinor) = __check_if_exists_future_collision(&Joao, two_columns_check_1);

    if (!collision) {
      tie(collision, positionAjustMinor) = __check_if_exists_future_collision(&Joao, two_columns_check_2);
    }

    if (collision) {
        Joao.y = (positionAjustMinor * 10) - 10;
        Joao.state = STOP;
        Joao.time = 0;
    }

    Joao.y = (positionAjustMinor * 10) - 10;
}

int main()
{
    menu_boot();
    /**
    criando uma instancia do meu Helper ...
    */
    spaceControlPersonagem.teste();
    array_clouds.clear();
    inicializePersonagem(&Joao);
    defaultLoad();
    al_reserve_samples(10);
    introAudio = al_load_sample("./sounds/intro.ogg");
    if (!introAudio) {
        printf("nao carregaou a musica de introducao");
    }
    SOUND_HERO_JUMP = al_load_sample("./sounds/jump.ogg");
    if (!SOUND_HERO_JUMP) {
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
            case ALLEGRO_EVENT_TIMER: // Holding key
                redraw = true;
                if (cutscene == CUTSCENE::INGAME) {
                    holdingKey();
                }

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;
                break;

            case ALLEGRO_EVENT_KEY_DOWN: // key down na tecla
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;

                if (cutscene == CUTSCENE::INGAME) {
                    inGameKeyDown();
                } else if (cutscene == CUTSCENE::INTRO) {
                    introKeyDown();
                } else if (cutscene == CUTSCENE::MENU) {
                    menu_keydown();
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
                    al_draw_bitmap(moonImage, 600, 100, 0);
                }
                //moveClouds(MAP_MOVE);
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

                if (Joao.state == PERSONAGEM_ACTIONS::FALLEN) {
                    processing_hero_fallen();
                }

                if (Joao.state == PERSONAGEM_ACTIONS::JUMP) {
                    jumpPersonagem(&Joao);
                }
                //ghosts_action(MAP_MOVE);
                //al_draw_circle(Joao.x + 17.0, Joao.y, 3, al_map_rgb(255, 255, 255), 1);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 20, 0, "X: %f", Joao.x);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 150, 20, 0, "Y: %f", Joao.y);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 40, 0, "MAP_MOVE: %d", MAP_MOVE);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 130, 0, "state: %d", Joao.state);
            } else if (cutscene == CUTSCENE::INTRO) {
                intro_timer_controller();
                introduction_start(font);
            } else if (cutscene == CUTSCENE::MENU) {
                menu_rendering();
            }

            al_flip_display();
            redraw = false;
        }
    }
    destroyImagesAndAnothers();
    return 0;
}
