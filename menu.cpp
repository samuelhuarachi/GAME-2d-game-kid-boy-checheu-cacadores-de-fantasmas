

std::vector<int> MENU_LIST_OPTIONS;

enum MENU_OPTIONS {
    MENU_INTRO,
    MENU_RESUME,
    MENU_EXIT
};

int MENU_OPTION_SELECTED;

void menu_boot() {
    cout << "menu booted" << endl;
    MENU_LIST_OPTIONS.push_back(MENU_OPTIONS::MENU_INTRO);
    MENU_LIST_OPTIONS.push_back(MENU_OPTIONS::MENU_RESUME);
    MENU_LIST_OPTIONS.push_back(MENU_OPTIONS::MENU_EXIT);

    MENU_OPTION_SELECTED = MENU_OPTIONS::MENU_INTRO;
}

void menu_option_previous() {
    if (MENU_OPTION_SELECTED == MENU_OPTIONS::MENU_INTRO) {
        MENU_OPTION_SELECTED = MENU_OPTIONS::MENU_EXIT;
    } else if (MENU_OPTION_SELECTED == MENU_OPTIONS::MENU_EXIT) {
        MENU_OPTION_SELECTED = MENU_OPTIONS::MENU_RESUME;
    } else if (MENU_OPTION_SELECTED == MENU_OPTIONS::MENU_RESUME) {
        MENU_OPTION_SELECTED = MENU_OPTIONS::MENU_INTRO;
    }
}

void menu_option_next() {
    if (MENU_OPTION_SELECTED == MENU_OPTIONS::MENU_INTRO) {
        MENU_OPTION_SELECTED = MENU_OPTIONS::MENU_RESUME;
    } else if (MENU_OPTION_SELECTED == MENU_OPTIONS::MENU_EXIT) {
        MENU_OPTION_SELECTED = MENU_OPTIONS::MENU_INTRO;
    } else if (MENU_OPTION_SELECTED == MENU_OPTIONS::MENU_RESUME) {
        MENU_OPTION_SELECTED = MENU_OPTIONS::MENU_EXIT;
    }
}

void menu_rendering() {
    al_draw_tinted_bitmap(MENU_BACKGROUND, al_map_rgba_f(1, 1, 1, 1), 0, 0, 0);

    int axis_x = 325;
    int axis_y = 200;
    for (int i = 0; i < MENU_LIST_OPTIONS.size(); i++) {
        int option = MENU_LIST_OPTIONS[i];
        if (option == MENU_OPTIONS::MENU_INTRO) {
            if (option == MENU_OPTION_SELECTED) {
                al_draw_text(font, al_map_rgb(234, 234, 28), axis_x, axis_y, 0, "Intro");
            } else {
                al_draw_text(font, al_map_rgb(255, 255, 255), axis_x, axis_y, 0, "Intro");
            }
        } else if (option == MENU_OPTIONS::MENU_RESUME) {
            if (option == MENU_OPTION_SELECTED) {
                al_draw_text(font, al_map_rgb(234, 234, 28), axis_x, axis_y + 20, 0, "Jogar / Continuar");
            } else {
                al_draw_text(font, al_map_rgb(255, 255, 255), axis_x, axis_y + 20, 0, "Jogar / Continuar");
            }
        } else if (option == MENU_OPTIONS::MENU_EXIT) {
            if (option == MENU_OPTION_SELECTED) {
                al_draw_text(font, al_map_rgb(234, 234, 28), axis_x, axis_y + 40, 0, "Sair do jogo");
            } else {
                al_draw_text(font, al_map_rgb(255, 255, 255), axis_x, axis_y + 40, 0, "Sair do jogo");
            }
        }
    }
}

void menu_keydown() {
    if(key[ALLEGRO_KEY_ESCAPE]) {
        cutscene = CUTSCENE::INGAME;
    } else if (key[ALLEGRO_KEY_W]) {
        al_play_sample(SOUND_MENU_SELECT, 0.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, &SOUND_ID_MENU_SELECT);
        menu_option_previous();
    } else if (key[ALLEGRO_KEY_S]) {
        al_play_sample(SOUND_MENU_SELECT, 0.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, &SOUND_ID_MENU_SELECT);
        menu_option_next();
    } else if (key[ALLEGRO_KEY_ENTER]) {
        if (MENU_OPTION_SELECTED == MENU_OPTIONS::MENU_INTRO) {
            cutscene = CUTSCENE::INTRO;
        } else if (MENU_OPTION_SELECTED == MENU_OPTIONS::MENU_RESUME) {
            cutscene = CUTSCENE::INGAME;
        } else if (MENU_OPTION_SELECTED == MENU_OPTIONS::MENU_EXIT) {
            GAME_EXIT = true;
        }
    }
}
