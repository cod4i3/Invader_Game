#pragma once
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "buffer.h"

struct Sprite
{
    size_t width, height;
    uint8_t* data;
};

struct SpriteAnimation
{
    bool loop;
    size_t num_frames;
    size_t frame_duration;
    size_t time;
    Sprite** frames;
};

struct Alien
{
    size_t x, y;
    uint8_t type;
};

struct Player
{
    size_t x, y;
    size_t life;
};

void PlayerInit(Sprite& player_sprite);
void alien_spriteInit0(Sprite& alien_sprite);
void alien_spriteInit1(Sprite& alien_sprite);
void alien_animationInit(SpriteAnimation*& alian_animation);

void buffer_draw_sprite(Buffer* buffer, const Sprite& sprite,
                        size_t x, size_t y, uint32_t color);
void drawAlian(Buffer buffer);
void drawPlayer(Buffer buffer);
