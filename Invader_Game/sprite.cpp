#include "sprite.h"

void PlayerInit(Sprite& player_sprite){
    player_sprite.width = 11;
    player_sprite.height = 7;
    player_sprite.data = new uint8_t[77]
    {
        0,0,0,0,0,1,0,0,0,0,0, // .....@.....
        0,0,0,0,1,1,1,0,0,0,0, // ....@@@....
        0,0,0,0,1,1,1,0,0,0,0, // ....@@@....
        0,1,1,1,1,1,1,1,1,1,0, // .@@@@@@@@@.
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
    };
}

void alien_spriteInit0(Sprite& alien_sprite){
    alien_sprite.width = 11;
    alien_sprite.height = 8;
    alien_sprite.data = new uint8_t[11 * 8]
    {
        0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
        0,0,0,1,0,0,0,1,0,0,0, // ...@...@...
        0,0,1,1,1,1,1,1,1,0,0, // ..@@@@@@@..
        0,1,1,0,1,1,1,0,1,1,0, // .@@.@@@.@@.
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        1,0,1,1,1,1,1,1,1,0,1, // @.@@@@@@@.@
        1,0,1,0,0,0,0,0,1,0,1, // @.@.....@.@
        0,0,0,1,1,0,1,1,0,0,0  // ...@@.@@...
    };
}

void alien_spriteInit1(Sprite& alien_sprite){
    alien_sprite.width = 11;
    alien_sprite.height = 8;
    alien_sprite.data = new uint8_t[88]
    {
        0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
        1,0,0,1,0,0,0,1,0,0,1, // @..@...@..@
        1,0,1,1,1,1,1,1,1,0,1, // @.@@@@@@@.@
        1,1,1,0,1,1,1,0,1,1,1, // @@@.@@@.@@@
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        0,1,1,1,1,1,1,1,1,1,0, // .@@@@@@@@@.
        0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
        0,1,0,0,0,0,0,0,0,1,0  // .@.......@.
    };
}

void alien_animationInit(SpriteAnimation*& alien_animation){
    alien_animation->loop = true;
    alien_animation->num_frames = 2;
    alien_animation->frame_duration = 10;
    alien_animation->time = 0;
}

void buffer_draw_sprite(Buffer* buffer, const Sprite& sprite,
                        size_t x, size_t y, uint32_t color
                        ){
    for(size_t xi = 0; xi < sprite.width; ++xi)
    {
        for(size_t yi = 0; yi < sprite.height; ++yi)
        {
            size_t sy = sprite.height - 1 + y - yi;
            size_t sx = x + xi;
            if(sprite.data[yi * sprite.width + xi] &&
               sy < buffer->height && sx < buffer->width)
            {
                buffer->data[sy * buffer->width + sx] = color;
            }
        }
    }
}

void drawAlian(Buffer buffer){
    Sprite alien_sprite;
    alien_sprite.width = 11;
    alien_sprite.height = 8;
    alien_sprite.data = new uint8_t[11 * 8]
    {
        0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
        0,0,0,1,0,0,0,1,0,0,0, // ...@...@...
        0,0,1,1,1,1,1,1,1,0,0, // ..@@@@@@@..
        0,1,1,0,1,1,1,0,1,1,0, // .@@.@@@.@@.
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        1,0,1,1,1,1,1,1,1,0,1, // @.@@@@@@@.@
        1,0,1,0,0,0,0,0,1,0,1, // @.@.....@.@
        0,0,0,1,1,0,1,1,0,0,0  // ...@@.@@...
    };
    
    buffer_draw_sprite(&buffer, alien_sprite, 112, 128, rgb_to_uint32(128, 0, 0));
    
    glTexSubImage2D(
                    GL_TEXTURE_2D, 0, 0, 0,
                    buffer.width, buffer.height,
                    GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,
                    buffer.data
                    );
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void drawPlayer(Buffer buffer){
    Sprite player_sprite;
    player_sprite.width = 11;
    player_sprite.height = 7;
    player_sprite.data = new uint8_t[77]
    {
        0,0,0,0,0,1,0,0,0,0,0, // .....@.....
        0,0,0,0,1,1,1,0,0,0,0, // ....@@@....
        0,0,0,0,1,1,1,0,0,0,0, // ....@@@....
        0,1,1,1,1,1,1,1,1,1,0, // .@@@@@@@@@.
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
    };
    
    buffer_draw_sprite(&buffer, player_sprite, 112, 128, rgb_to_uint32(128, 0, 0));
    glTexSubImage2D(
                    GL_TEXTURE_2D, 0, 0, 0,
                    buffer.width, buffer.height,
                    GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,
                    buffer.data
                    );
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}


