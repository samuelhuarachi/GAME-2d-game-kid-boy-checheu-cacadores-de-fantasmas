

void phase_1_boot() {
    cout << "Phase 1 booted" << endl;

    NPC_PERSONAGEM npc_personage;
    npc_personage.column = 71;
    npc_personage.line = 50;
    npc_personage.fileName = "./images/frog.png";
    npc_personage.life = 100;
    npc_personage.height = 22;
    npc_personage.name = "Sr. Frog";

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

void phase_1_draw_npc(PERSONAGEM *p) {
    int columnsVisionMin = ((MAP_MOVE * -1) / 20) + 1;
    int columnsVisionMax = 41 + ((MAP_MOVE * -1) / 20) + 1;
    int linesVisionMin = 0;
    int linesVisionMax = 60;

    const int hero_line = get_line_in_snapshot_by_hero_y(p->y);
    const int hero_column = get_column_in_snapshot_by_hero_x(p->x);

    al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 140, 0, "hero line: %d", hero_line);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 150, 0, "hero column: %d", hero_column);

    for (int i = 0; i < ARRAY_NPC.size(); i++) {
        const NPC_PERSONAGEM npc_personage = ARRAY_NPC[i];
        const int npc_column = npc_personage.column;

        if (npc_column >= columnsVisionMin - 1 && npc_column <= columnsVisionMax) {
            al_draw_bitmap(AL_BITMAP_SR_FROG, ARRAY_NPC[i].column * 20 + MAP_MOVE, (ARRAY_NPC[i].line * 10) - npc_personage.height, 0);

            // check, for activating someone NPC
            if (NPC_ACTIVE_INDEX < 0 && npc_check_possible_active_npc(columnsVisionMin, hero_column, hero_line, ARRAY_NPC[i].column, ARRAY_NPC[i].line)) {
                NPC_ACTIVE_INDEX = i;
            } else if (NPC_ACTIVE_INDEX != -1 && NPC_ACTIVE_INDEX == i){
                // desactivating NPC if necessary
                if (npc_can_i_desactive_npc(columnsVisionMin, hero_column, hero_line, ARRAY_NPC[i].column, ARRAY_NPC[i].line)) {
                    NPC_ACTIVE_INDEX = -1;
                }
            }
        }
    }
}
