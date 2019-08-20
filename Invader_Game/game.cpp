#include "Game.h"

void GameInit(Game game){
    game.width = buffer_width;
    game.height = buffer_height;
    game.num_aliens = 55;
    game.aliens = new Alien[game.num_aliens];
    
    game.player.x = 112 - 5;
    game.player.y = 32;
    
    game.player.life = 3;
}

