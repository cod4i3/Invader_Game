#include "controller.h"

void player_controller(int player_move_dir, Game& game, Sprite& player_sprite){
    if(player_move_dir != 0)
    {
        if(game.player.x + player_sprite.width + player_move_dir >= game.width)
        {
            game.player.x = game.width - player_sprite.width;
        }
        else if((int)game.player.x + player_move_dir <= 0)
        {
            game.player.x = 0;
        }
        else game.player.x += player_move_dir;
    }
}

void bullet_controller(Game& game, Sprite& bullet_sprite, int bi){
    game.bullets[bi].y += game.bullets[bi].dir;
    if(game.bullets[bi].y >= game.height ||
       game.bullets[bi].y < bullet_sprite.height)
    {
        game.bullets[bi] = game.bullets[game.num_bullets - 1];
        --game.num_bullets;
    }
}
