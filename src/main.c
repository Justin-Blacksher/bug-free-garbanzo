#include "game.h"

int main(void) {

    Game game = {0};
    InitGame(&game);
    if (!game.running) return 1;

    while (game.running) {
        HandleInput(&game);
        UpdateGame(&game);
        RenderGame(&game);
        
    }
    CleanupGame(&game);
    return 0;
    
}
