#include "game.h"

void gameInit(Game& game, size_t buffer_width, size_t buffer_height){
    game.width = buffer_width;
    game.height = buffer_height;
    game.num_aliens = 55;
    game.player.x = 112 - 5;
    game.player.y = 32;
    game.player.life = 3;
}

