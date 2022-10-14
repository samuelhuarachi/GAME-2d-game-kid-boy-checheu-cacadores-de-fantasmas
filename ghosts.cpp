typedef struct GHOST_STRUCT
{
    float x, y;
    float width = 32, height = 25;
    string fileName;
    float speed = 0.05;
    float rangeMax = 40;
    float range = 20;
    float initialRange = 0;
    float distance = 60;
    float initialDistance = 60;
    float timer;
    float life = 100;
    float directionSide = -1;

} GHOST_STRUCT;

vector<GHOST_STRUCT> array_ghosts;


void animate_ghost(GHOST_STRUCT *ghost)
{
    ALLEGRO_BITMAP *ghostBitmap;
    char *cstr;
    string fileName = ghost->fileName;

    cstr = new char[fileName.length() + 1];
    strcpy(cstr, fileName.c_str());
    ghostBitmap = al_load_bitmap(cstr);

    if (ghostBitmap) {
        al_draw_bitmap(ghostBitmap, ghost->x, ghost->y, 0);
        ghost->x = ghost->x - ghost->speed;
    }

    delete [] cstr;
    //al_destroy_bitmap(ghostBitmap);
}

void loadGhostsPosition(string mapFileName) {
    GHOST_STRUCT newGhost;
    std::ifstream file(mapFileName);
    int currentLine = 1;
    int currentColumn = -1;

    string filename(mapFileName);

    FILE* input_file = fopen(filename.c_str(), "r");
    if (input_file == nullptr) {}

    unsigned char character = 0;

    while (!feof(input_file)) {
       character = getc(input_file);

        if (character == '\n') {
            currentLine++;
            currentColumn = -1;
        }

        if (character == 'f') {
            newGhost.x = currentColumn;
            newGhost.y = currentLine;
            newGhost.fileName = "./images/ghost.png";
            newGhost.life = 100;

            array_ghosts.push_back(newGhost);
        }

        currentColumn++;
    }

    fclose (input_file);
}


void ghosts_action(int MAP_MOVE = 0)
{

    ALLEGRO_BITMAP* cloudBitmap;
    string fileName;
    char *cstr;
    float cloudColumnPosition;


    for (int i = 0; i < array_ghosts.size(); i++) {

        fileName = array_ghosts[i].fileName;
        cstr = new char[fileName.length() + 1];
        strcpy(cstr, fileName.c_str());

        //cloudColumnPosition = (array_ghosts[i].x * 10) + MAP_MOVE;

        cloudBitmap = al_load_bitmap(cstr);
        if (cloudBitmap) {

            al_draw_bitmap(cloudBitmap, array_ghosts[i].x * 20 + MAP_MOVE, (array_ghosts[i].y * 10) - array_ghosts[i].height, 0);


            //rangeMax

            if (array_ghosts[i].range >= 0) {
                array_ghosts[i].x = array_ghosts[i].x - array_ghosts[i].speed;
                array_ghosts[i].range = array_ghosts[i].range - 1;
            } else {

            }


        }

        delete [] cstr;
    }
}
