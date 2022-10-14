
int FLAH_INTRODUCTION_AUDIO = 0;
int INTRODUCTION_PRESTINY = 0;
int TITLE_KID_BOY_ANIMATION_VELOCITY = 0;
int TITLE_KID_BOY_ANIMATION_POSITION = 300;


//CLOUD_STRUCT arra1[2];


vector<GHOST_STRUCT> array_ghost;

void drawTreenAndFloor() {

    if (tree2Image) {
        al_draw_bitmap(tree2Image, -40, (450 - tree2ImageHeight), 0);
        al_draw_bitmap(tree2Image, 50, (450 - tree2ImageHeight), 0);
        al_draw_bitmap(tree2Image, 120, (450 - tree2ImageHeight), 0);
        al_draw_bitmap(tree2Image, 190, (450 - tree2ImageHeight), 0);
        al_draw_bitmap(tree2Image, 260, (450 - tree2ImageHeight), 0);
        al_draw_bitmap(tree2Image, 330, (450 - tree2ImageHeight), 0);
        al_draw_bitmap(tree2Image, 400, (450 - tree2ImageHeight), 0);
        al_draw_bitmap(tree2Image, 470, (450 - tree2ImageHeight), 0);
        al_draw_bitmap(tree2Image, 540, (450 - tree2ImageHeight), 0);
        al_draw_bitmap(tree2Image, 610, (450 - tree2ImageHeight), 0);
        al_draw_bitmap(tree2Image, 680, (450 - tree2ImageHeight), 0);
        al_draw_bitmap(tree2Image, 750, (450 - tree2ImageHeight), 0);
        al_draw_bitmap(tree2Image, 820, (450 - tree2ImageHeight), 0);
    }

    if (tree1Image) {
        al_draw_bitmap(tree1Image, 19, (450 - tree1ImageHeight), 0);
        al_draw_bitmap(tree1Image, 259, (450 - tree1ImageHeight), 0);
        al_draw_bitmap(tree1Image, 601, (450 - tree1ImageHeight), 0);
    }



    for(int i = 0; i < 40; i++) {
        if (floorImage) {
            al_draw_bitmap(floorImage, (20 * i), 450, 0);
        }

    }

    for(int i = 0; i < 40; i++) {
            if (floor3Image) {
                al_draw_bitmap(floor3Image, (20 * i), 470, 0);
            }

    }

    for(int i = 0; i < 40; i++) {
            if (floor3Image) {
                al_draw_bitmap(floor3Image, (20 * i), 490, 0);
            }

    }

    for(int i = 0; i < 40; i++) {
            if (floor3Image) {
                al_draw_bitmap(floor3Image, (20 * i), 510, 0);
            }

    }

    for(int i = 0; i < 40; i++) {
            if (floor3Image) {
                al_draw_bitmap(floor3Image, (20 * i), 530, 0);
            }

    }

    for(int i = 0; i < 40; i++) {
            if (floor3Image) {
                al_draw_bitmap(floor3Image, (20 * i), 550, 0);
            }

    }

    for(int i = 0; i < 40; i++) {
            if (floor3Image) {
                al_draw_bitmap(floor3Image, (20 * i), 570, 0);
            }

    }

    for(int i = 0; i < 40; i++) {
            if (floor3Image) {
                al_draw_bitmap(floor3Image, (20 * i), 590, 0);
            }

    }

    for(int i = 0; i < 40; i++) {
            if (floor3Image) {
                al_draw_bitmap(floor3Image, (20 * i), 610, 0);
            }

    }
}


void animate_kid_boy_title() {

    float opacity = TITLE_KID_BOY_ANIMATION_VELOCITY * 0.03;
    if (opacity >= 1) {
        opacity = 1;
    }

    // s = so + vo * t + (a*t*t) / 2

    if (TITLE_KID_BOY_ANIMATION_POSITION > 129) {
        TITLE_KID_BOY_ANIMATION_POSITION = (TITLE_KID_BOY_ANIMATION_POSITION + (0 * introTime) + ((-1 * introTime * introTime) / 2));
    }

    if (kidBoyImage) {
        al_draw_tinted_bitmap(kidBoyImage, al_map_rgba_f(opacity, opacity, opacity, opacity), 200, TITLE_KID_BOY_ANIMATION_POSITION, 0);
    }
}

void drawClouds()
{
    ALLEGRO_BITMAP* cloudBitmap;
    string fileName;
    char *cstr;

    //fileName = array_clouds[0].fileName;
    //cout << fileName << endl;

    for (int i = 0; i < array_clouds.size(); i++) {

       fileName = array_clouds[i].fileName;
       cstr = new char[fileName.length() + 1];
       strcpy(cstr, fileName.c_str());

       cloudBitmap = al_load_bitmap(cstr);

        if (cloudBitmap) {
            al_draw_bitmap(cloudBitmap, (array_clouds[i].x - ((introTime * array_clouds[i].moveSpeed) / 5)), array_clouds[i].y, 0);
       }

       delete [] cstr;
    }
}

void draw_ghost()
{
    //string file2;
    //char *cstr;
    //int vectorsize = array_ghost.size();

    for (int i = 0; i < array_ghost.size(); i++) {
        //file2 = array_ghost[i].fileName;
        //cstr = new char[fileName.length() + 1];

        //array_ghost[i].timer = TITLE_KID_BOY_ANIMATION_VELOCITY;
        if (array_ghost[i].x > -40) {
            animate_ghost(&array_ghost[i]);
        }


        //cout << file2 << endl;
    }
}


void introduction_start(ALLEGRO_FONT* font)
{
    //al_draw_bitmap(nightImage, 0, 0, 0);
    //al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 20, 0, "Timer: %f", introTime);

    if (INTRODUCTION_PRESTINY == 0) {
        CLOUD_STRUCT cloud_1;
        CLOUD_STRUCT cloud_2;

        GHOST_STRUCT ghost_1;
        GHOST_STRUCT ghost_2;

        al_play_sample(introAudio, 0.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, &intro_sound_kbc);

        cloud_1.x = 700;
        cloud_1.y = 119;
        cloud_1.fileName = "./images/cloud_1.png";
        cloud_1.height = 57;
        cloud_1.width = 133;
        cloud_1.moveSpeed = 10;

        cloud_2.x = 249;
        cloud_2.y = 200;
        cloud_2.fileName = "./images/cloud_2.png";
        cloud_2.height = 57;
        cloud_2.width = 133;
        cloud_2.moveSpeed = 2;

        //cout << cloud_2.fileName << endl;

        //arra1[1] = cloud_1;
        //arra1[2] = cloud_2;

        array_clouds.push_back(cloud_1);
        array_clouds.push_back(cloud_2);


        ghost_1.x = 500;
        ghost_1.y = 450 - ghost_1.height;
        ghost_1.fileName = "./images/ghost.png";
        ghost_1.speed = 0.5;

        ghost_2.x = 700;
        ghost_2.y = 450 - ghost_2.height;
        ghost_2.fileName = "./images/ghost.png";
        ghost_2.speed = 0.9;

        array_ghost.push_back(ghost_1);
        array_ghost.push_back(ghost_2);

        //array_ghost[0] = ghost_1;
        //array_ghost[2] = ghost_2;
    }

    draw_ghost();
    drawTreenAndFloor();
    drawClouds();


    if (houseAbandonedImage) {
        al_draw_bitmap(houseAbandonedImage, 320, (450 - houseAbandonedImageHeight), 0);

    }

    if (jowImage) {
        al_draw_bitmap_region(jowImage, 0, 0, 80, 80, 350, (450 - 80), 0);
    }

    if (joaoImage) {
        al_draw_bitmap_region(joaoImage, 0, 0, 64, 64, 310, (450 - 64), 0);
    }

    if (gleisonImage) {
        al_draw_bitmap_region(gleisonImage, 0, 0, 64, 64, 460, (450 - 64), 0);
    }

    if (pedroImage) {
        al_draw_bitmap_region(pedroImage, 0, 0, 64, 64, 410, (450 - 64), 0);
    }

    animate_kid_boy_title();


    if (ghostImage) {
        //al_draw_bitmap(ghostImage, 200, 150, 0);
    }

    al_draw_bitmap(moonImage, 30, 30, 0);

    INTRODUCTION_PRESTINY = 1;

    if (introTime % 2 == 0) {
        al_draw_text(font, al_map_rgb(255, 255, 255), 285, 550, 0, "Aperte \"Espaco\" para continuar");
    }

}



// ajustando os timers
void intro_timer_controller()
{


    if (introDelayTitleKidBoyAnimate < 7) {
        introDelayTitleKidBoyAnimate = introDelayTitleKidBoyAnimate + 1;
    } else {
        introDelayTitleKidBoyAnimate = 0;
        TITLE_KID_BOY_ANIMATION_VELOCITY = TITLE_KID_BOY_ANIMATION_VELOCITY + 1;
    }

    if (introDelayInitial < 55) {
        introDelayInitial = introDelayInitial + 1;
    } else {
        introDelayInitial = 0;
        introTime = introTime + 1;
    }
}
