
bool npc_check_possible_active_npc(int columnsVisionMin, int hero_column, int hero_line, int npc_column, int npc_line) {

    return ((columnsVisionMin + hero_column) >= (npc_column - 1) && (columnsVisionMin + hero_column) <= (npc_column + 1) && (hero_line + 1) == npc_line);
}

bool npc_can_i_desactive_npc(int columnsVisionMin, int hero_column, int hero_line, int npc_column, int npc_line) {
    return ((columnsVisionMin + hero_column) < (npc_column - 1) || (columnsVisionMin + hero_column) > (npc_column + 1) || (hero_line + 1) != npc_line);
}

void npc_interact() {
    if (NPC_ACTIVE_INDEX == -1) {
        cout << "nenhum npc para interagir" << endl;
    } else {
        const NPC_PERSONAGEM npc_personage = ARRAY_NPC[NPC_ACTIVE_INDEX];
        cout << "Olá " << npc_personage.name << ", podemos conversar?" << endl;
    }
}
