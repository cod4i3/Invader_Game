#pragma once
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "buffer.h"

enum AlienType: uint8_t
{
    ALIEN_DEAD   = 0,
    ALIEN_TYPE_A = 1,
    ALIEN_TYPE_B = 2,
    ALIEN_TYPE_C = 3
};

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

struct Bullet
{
    size_t x,y;
    int dir;
};

void PlayerInit(Sprite& player_sprite);
void alien_spriteInit0(Sprite& alien_sprite);
void alien_spriteInit1(Sprite& alien_sprite);
void alien_spriteInit2(Sprite& alien_sprite);
void alien_spriteInit3(Sprite& alien_sprite);
void alien_spriteInit4(Sprite& alien_sprite);
void alien_spriteInit5(Sprite& alien_sprite);
void alien_death_spriteInit(Sprite& alien_sprite);
void alien_animationInit(SpriteAnimation*& alian_animation);
void bullet_spriteInit(Sprite& bullet);

void buffer_draw_sprite(Buffer* buffer, const Sprite& sprite,
                        size_t x, size_t y, uint32_t color);
void drawAlian(Buffer buffer);
void drawPlayer(Buffer buffer);
