#include "game.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void InitGame(Game *game) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mountain Hollow");
    SetTargetFPS(60);
    game->camera = (Camera2D){0};
    game->camera.zoom = 1.0f;
    game->camera.offset = (Vector2){SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f};

    game->font = LoadFont("assets/ManufacturingConsent-Regular.ttf");
    if (game->font.texture.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load font");
        return;
    }

    game->map.tileset = LoadTexture("assets/tiles.png");
    if (game->map.tileset.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load Tileset");
        return;
    }

    game->player.x = 32;
    game->player.y = 32;
    game->player.hp = 100;
    game->player.mp = 50;
    game->player.virtue = 0;
    game->player.item_count = 0;
    for (int i = 0; i < MAX_ITEMS; i++) {
        game->player.inventory[i] = NULL;
    }

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1) {
                game->map.tiles[x][y] = 2;
                
            } else if (rand() % 10 < 3) {
                game->map.tiles[x][y] = 1;

            } else {
                game->map.tiles[x][y] = 0;
            }
        }
    }
    game->map.tiles[33][33] = 3;

    InitNPCs(game);
    game->in_combat = 0;
    game->running = 1;
    
}

void InitNPCs(Game *game) {

    game->npcs[0].x = 34;
    game->npcs[0].y = 32;
    game->npcs[0].name = strdup("KriminalManimal");
    game->npcs[0].dialogue = strdup("Ride the Fried Circuit Membrane");
    game->npcs[0].active = 1;
    game->npcs[0].hp = 0;

    game->npcs[1].x = 36;
    game->npcs[1].y = 32;
    game->npcs[1].name = strdup("BudBird");
    game->npcs[1].dialogue = strdup("Blaze With me homie!");
    game->npcs[1].active = 1;
    game->npcs[1].hp = 50;

    game->npcs[2].x = 38;
    game->npcs[2].y = 32;
    game->npcs[2].name = strdup("DoorDasher");
    game->npcs[2].dialogue = strdup("Fight me for your food punk!");
    game->npcs[2].active = 1;
    game->npcs[2].hp = 70;

    game->npcs[3].x = 40;
    game->npcs[3].y = 32;
    game->npcs[3].name = strdup("LizardLorde");
    game->npcs[3].dialogue = strdup("Collect what you think you could be useful. Don't bring back old poisoned clues home");
    game->npcs[3].active = 1;
    game->npcs[3].hp = 1000;

    for (int i = 2; i < MAX_NPCS; i++) {
        game->npcs[i].active = 0;
    }
}

void RenderDialogue(Game *game, const char *text) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTextEx(game->font, text, (Vector2){SCREEN_WIDTH/4.0f, SCREEN_HEIGHT-50.0f}, 16, 1, WHITE);
    EndDrawing();
    WaitTime(2.0);
}

void StartCombat(Game *game, int npc_index) {
    game->in_combat = 1;
    game->combat_npc_index = npc_index;
    char msg[100];
    snprintf(msg, 100, "Time for you to whack %s!", game->npcs[npc_index].name);
    RenderDialogue(game, msg);
}

void RenderStatus(Game *game) {
    char status[200];
    snprintf(status, 200, "HP: %d MP: %d Virtue: %d Items: %d", game->player.hp,game->player.mp, game->player.virtue, game->player.item_count);
    DrawTextEx(game->font, status, (Vector2){10, 10}, 16, 1, WHITE);
}

void HandleInput(Game *game) {
    if (WindowShouldClose()) {
        game->running = 0;
        return;
    }

    if (game->in_combat) {
        if (IsKeyPressed(KEY_A)) {
            NPC* enemy = &game->npcs[game->combat_npc_index];
            enemy->hp -= 10;
            char msg[100];
            snprintf(msg, 100, "BAM! You hit %s for 10 damage! HP: %d", enemy->name, enemy->hp);
            RenderDialogue(game, msg);
            if (enemy->hp <= 0) {
                snprintf(msg, 100, "Its FU Thursday for %s", enemy->name);
                RenderDialogue(game, msg);
                enemy->active = 0;
                game->in_combat = 0;
                game->player.virtue--;
            }else{
                game->player.hp -= 5;
                snprintf(msg, 100, "%s is doing the needful on your arse! -5 Dam", enemy->name);
                RenderDialogue(game, msg);
                if (game->player.hp <= 0) {
                    RenderDialogue(game, "You sucked and you died");
                    game->running = 0;
                }
            }
        }
    }else{
        int new_x = game->player.x, new_y = game->player.y;
        if (IsKeyPressed(KEY_UP)) new_y--;
        if (IsKeyPressed(KEY_DOWN)) new_y++;
        if (IsKeyPressed(KEY_LEFT)) new_x--;
        if (IsKeyPressed(KEY_RIGHT)) new_x++;
        if (IsKeyPressed(KEY_SPACE)) {}
    }
            
