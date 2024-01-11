


void phase_1_boot() {
    cout << "Phase 1 booted" << endl;

    NPC_PERSONAGEM npc_personage;
    npc_personage.column = 71;
    npc_personage.line = 50;
    npc_personage.fileName = "./images/frog.png";
    npc_personage.life = 100;

    ARRAY_NPC.push_back(npc_personage);

    /* NPC_PERSONAGEM npc_personage2;
    npc_personage2.column = 71;
    npc_personage2.line = 50;
    npc_personage2.fileName = "./images/frog.png";
    npc_personage2.life = 100;

    ARRAY_NPC.push_back(npc_personage2);

    NPC_PERSONAGEM npc_personage3;
    npc_personage3.column = 73;
    npc_personage3.line = 50;
    npc_personage3.fileName = "./images/frog.png";
    npc_personage3.life = 100;

    ARRAY_NPC.push_back(npc_personage3);

    NPC_PERSONAGEM npc_personage4;
    npc_personage4.column = 75;
    npc_personage4.line = 50;
    npc_personage4.fileName = "./images/frog.png";
    npc_personage4.life = 100;

    ARRAY_NPC.push_back(npc_personage4);

    NPC_PERSONAGEM npc_personage5;
    npc_personage5.column = 77;
    npc_personage5.line = 50;
    npc_personage5.fileName = "./images/frog.png";
    npc_personage5.life = 100;

    ARRAY_NPC.push_back(npc_personage5);

    NPC_PERSONAGEM npc_personage6;
    npc_personage6.column = 79;
    npc_personage6.line = 50;
    npc_personage6.fileName = "./images/frog.png";
    npc_personage6.life = 100;

    ARRAY_NPC.push_back(npc_personage6);

    NPC_PERSONAGEM npc_personage7;
    npc_personage7.column = 81;
    npc_personage7.line = 50;
    npc_personage7.fileName = "./images/frog.png";
    npc_personage7.life = 100;

    ARRAY_NPC.push_back(npc_personage7); */
}

void phase_1_draw_npc() {
    int columnsVisionMin = ((MAP_MOVE * -1) / 20) + 1;
    int columnsVisionMax = 41 + ((MAP_MOVE * -1) / 20) + 1;
    int linesVisionMin = 0;
    int linesVisionMax = 60;
    ALLEGRO_BITMAP* frogImage;
    string fileName;
    char *cstr;

    for (int i = 0; i < ARRAY_NPC.size(); i++) {
        const NPC_PERSONAGEM npc_personage = ARRAY_NPC[i];
        const int npc_column = npc_personage.column;

        if (npc_column >= columnsVisionMin - 1 && npc_column <= columnsVisionMax) {
            fileName = npc_personage.fileName;
            cstr = new char[fileName.length() + 1];
            strcpy(cstr, fileName.c_str());
            frogImage = al_load_bitmap(cstr);

            al_draw_bitmap(frogImage, ARRAY_NPC[i].column * 20 + MAP_MOVE, (ARRAY_NPC[i].line * 10) - 22, 0);
        }
    }
}
