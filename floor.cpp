

typedef struct FLOOR
{
    float x, y;
    float width, height;

} FLOOR;


/**
drawFloor abandonado
*/
void drawFloor(string mapFileName, int MAP_MOVE) {

    int clayContinueI;
    CLOUD_STRUCT cloud_1;

    while(!cloudImage) {
        cloudImage = al_load_bitmap("./images/cloud_1.png");
    }

    while(!houseImage) {
        houseImage = al_load_bitmap("./images/house.png");
    }

    while (!floorImage) {
        floorImage = al_load_bitmap("./images/floor2.png");
    }

    while (!clayImage) {
        clayImage = al_load_bitmap("./images/clay.png");
    }

    std::ifstream file(mapFileName);
    int currentLine = 1;
    int currentColumn = -1;

    string filename(mapFileName);
    vector<char> bytes;

    FILE* input_file = fopen(filename.c_str(), "r");
    if (input_file == nullptr) {}

    unsigned char character = 0;

    VERTICALLY_FLOOR position_vertically_floor;


    // zera as posicoes tanto do chao, quanto do chao na vertical
    for (int i = 0; i < 1999; i++) {
        for (int j = 0; j < 1999; j++) {
            allFloor[i][j] = 0; // parece que uso para identificar colisões
            allVerticallyFloor[i][j] = 0; // parece que não estou usando
        }
    }

    //position_vertically_floor.x = 0;
    //position_vertically_floor.y = 0;
    array_vertically_floor.clear();

    while (!feof(input_file)) {

        character = getc(input_file);
        if (character == '\n') {
            currentLine++;
            currentColumn = -1;
        }


        int mapLimit = (currentColumn * 20) + 20 + MAP_MOVE;

        if (mapLimit < 30) {
            currentColumn++;
            continue;
        }

        if (mapLimit > 860) {
            continue;
        }

        // Draw the house
        if (character == 'c' &
            ((currentColumn * 20) + MAP_MOVE) >= (-1 * HOUSE_1_WIDTH) &
            ((currentColumn * 20) + MAP_MOVE) <= (800 + HOUSE_1_WIDTH) ) {
            if (houseImage) {
                al_draw_bitmap(houseImage, (currentColumn * 20) + MAP_MOVE, (currentLine * 10) - HOUSE_1_HEIGTH, 0);
            }
        }

        // draw floor


        if (
                mapLimit >= 30 &
                mapLimit <= 800
            ) {

            if (character == '#') {

                if (floorImage) {
                    al_draw_bitmap(floorImage, (currentColumn * 20) + MAP_MOVE, (currentLine * 10), 0);
                }


                /**
                aqui eu marco 1 no "chão", para encontrar a colisão lá na frente
                */
                for (int b = 0; b < 19; b++) {
                    allFloor[currentLine * 10 - 10][currentColumn * 20 + b + MAP_MOVE] = 1;
                }

                position_vertically_floor.x = currentColumn * 20;
                position_vertically_floor.y = (currentLine * 10) - 10;

                /**
                provavel para encontrar a colisão no eixo vertical
                */
                array_vertically_floor.push_back(position_vertically_floor);
            }

            if (character == 'v') {
                clayContinueI = ((GAME_HEIGHT - (currentLine * 10)) / 20) + 2;

                for(int i = 0; i <= clayContinueI; i++ ) {

                    if (clayImage) {
                        al_draw_bitmap(clayImage, (currentColumn * 20) + MAP_MOVE, 10 + ((currentLine + i) * 10), 0);
                    }
                }
            }
        }


       currentColumn++;
    }

    fclose(input_file);
    PRISTINY_VERTICALLY_FLOOR = false;
}
