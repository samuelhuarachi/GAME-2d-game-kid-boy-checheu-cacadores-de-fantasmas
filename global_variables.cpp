#define ACELERACAO_GRAVIDADE         1
#define MAX_FALL                     10
#define MAX_PERSONAGEM_MOVE_RIGHT    340
#define MAP_MOVE_SPEED               3.5
#define HOUSE_1_WIDTH                160
#define HOUSE_1_HEIGTH               168
#define DELAY_JUMP_JOAO              5
#define GAME_HEIGHT                  600
#define MAX_GLOBAL_DELAY             10
int DEBUG_TIMES_TO_RUN = 5;
int DEBUG_TIMES_TO_RUN_COUNTER = 0;
bool DEBUG_ACTIVATED = false;

#define MAP_FLOOR             '#'
#define MAP_AIR               ' '
#define MAP_GHOST             'f'
#define MAP_INFINITE_FLOOR    'v'
#define MAP_CLOUD             'n'

#define MAP_FLOOR_INT             1
#define MAP_AIR_INT               0
#define MAP_GHOST_INT             4
#define MAP_INFINITE_FLOOR_INT    3
#define MAP_CLOUD_INT             2

#include "SpaceControl.h"

int CURRENT_MAX_GLOBAL_DELAY  = 0;

ALLEGRO_BITMAP* cloudImage;
ALLEGRO_BITMAP* houseImage;
ALLEGRO_BITMAP* floorImage;
ALLEGRO_BITMAP* moonImage;
ALLEGRO_BITMAP* joaoImage;
ALLEGRO_BITMAP* jowImage;
ALLEGRO_BITMAP* gleisonImage;
ALLEGRO_SAMPLE *introAudio;
ALLEGRO_BITMAP* pedroImage;
ALLEGRO_BITMAP* kidBoyImage;
ALLEGRO_BITMAP* ghostImage;
ALLEGRO_BITMAP* houseAbandonedImage;
ALLEGRO_BITMAP* tree1Image;
ALLEGRO_BITMAP* tree2Image;
ALLEGRO_BITMAP* floor3Image;
ALLEGRO_BITMAP* nightImage;
ALLEGRO_BITMAP* clayImage;
ALLEGRO_BITMAP* joaoRunningImage;
ALLEGRO_BITMAP* joaoFallImage;
ALLEGRO_BITMAP* joaoJumpImage;
ALLEGRO_SAMPLE_ID intro_sound_kbc;
ALLEGRO_SAMPLE *joaoJumpSound;


int houseAbandonedImageHeight = 150;
int tree1ImageHeight = 85;
int tree2ImageHeight = 134;
int floorImageHeight = 20;
int floor3ImageHeight = 20;

int allVerticallyFloor[2000][2000];
int allFloor[2000][2000];
int map_snapshot[60][41];
int GAMEMAP[1000][10000];
int DELAY_JUMP_JOAO_CURRENT = 0;
int MAP_MOVE = 0;

string directionCloudMove = "left";

ALLEGRO_TIMER* timer;


bool done = false;
bool redraw = true;

enum CUTSCENE {
    INTRO,
    MENU,
    INGAME
};

CUTSCENE cutscene = INTRO;
int introTime = 0;
int introDelayInitial = 0;
int introDelayTitleKidBoyAnimate = 0;

typedef struct CLOUD_STRUCT
{
    float x, y;
    float width, height;
    string fileName;
    float moveSpeed;
    float speed;
    float perspective;

} CLOUD_STRUCT;


struct VERTICALLY_FLOOR {
    int x;
    int y;
};

vector<CLOUD_STRUCT> array_clouds;
vector<VERTICALLY_FLOOR> array_vertically_floor;

bool PRISTINY_VERTICALLY_FLOOR = true;

unsigned char key[ALLEGRO_KEY_MAX];
ALLEGRO_FONT* font;
ALLEGRO_DISPLAY* disp;
ALLEGRO_EVENT_QUEUE* queue;


SpaceControl spaceControlPersonagem;
