


void moveClouds(int MAP_MOVE = 0)
{

    ALLEGRO_BITMAP* cloudBitmap;
    string fileName;
    char *cstr;
    float cloudColumnPosition;

    //cout << array_clouds.size() << endl;

    for (int i = 0; i < array_clouds.size(); i++) {

        fileName = array_clouds[i].fileName;
        cstr = new char[fileName.length() + 1];
        strcpy(cstr, fileName.c_str());

        cloudColumnPosition = (array_clouds[i].x * 10) + MAP_MOVE;


        cloudBitmap = al_load_bitmap(cstr);
        if (cloudBitmap && cloudColumnPosition > -200) {

            al_draw_bitmap(cloudBitmap, ((array_clouds[i].x * 10) + MAP_MOVE) / 2, array_clouds[i].y * 10, 0);
            array_clouds[i].x = array_clouds[i].x - array_clouds[i].speed;
        }

        delete [] cstr;
    }
}

void loadCloudsPosition(string mapFileName)
{
    CLOUD_STRUCT newCloud;
    std::ifstream file(mapFileName);
    int currentLine = 1;
    int currentColumn = -1;

    string filename(mapFileName);
    //vector<char> bytes;

    FILE* input_file = fopen(filename.c_str(), "r");
    if (input_file == nullptr) {}

    unsigned char character = 0;

    while (!feof(input_file)) {
       character = getc(input_file);

        if (character == '\n') {
            currentLine++;
            currentColumn = -1;
        }

        if (character == 'n') {
            newCloud.x = currentColumn;
            newCloud.y = currentLine;
            newCloud.height = 57;
            newCloud.width = 133;
            newCloud.fileName = "./images/cloud_1.png";
            newCloud.speed = 0.01;

            array_clouds.push_back(newCloud);
        }

        currentColumn++;
    }

    fclose (input_file);
}
