#ifndef GAME_H
#define GAME_H
#include "../bin/raylib.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TILE_SIZE 32
#define MAP_WIDTH 64
#define MAP_HEIGHT 64
#define MAX_NPCS 10
#define MAX_ITEMS 6

typedef struct {
    int x, y;
    int hp, mp;
    int virtue;
    char* inventory[MAX_ITEMS];
    int item_count;
} Player;


typedef struct {
    int tiles[MAP_WIDTH][MAP_HEIGHT];
    Texture2D tileset;
} Map;


typedef struct {
    int x, y;
    char* name;
    char* dialogue;
    int active;
    int hp;
} NPC;

typedef struct {
    Camera2D camera;
    Font font;
    Player player;
    Map map;
    NPC npcs[MAX_NPCS];
    int running;
    int in_combat;
    int combat_npc_index;
} Game;

void InitGame(Game *game);
void HandleInput(Game *game);
void UpdateGame(Game *game);
void RenderGame(Game *game);
void CleanupGame(Game *game);
void InitNPCs(Game *game);
void RenderDialogue(Game *game, const char *text);
void StartCombat(Game *game, int npc_index);
void RenderStatus(Game *game);

#endif
