#include "controller.h"

int player_controller(int player_move_dir, Game& game, Sprite& player_sprite){
    if(game.player.x + player_sprite.width + player_move_dir >= game.width - 1)
    {
        game.player.x = game.width - player_sprite.width - player_move_dir - 1;
        player_move_dir *= -1;
    }
    else if((int)game.player.x + player_move_dir <= 0)
    {
        game.player.x = 0;
        player_move_dir *= -1;
    }
    else game.player.x += player_move_dir;
    return player_move_dir;
}
