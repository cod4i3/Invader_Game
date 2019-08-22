#pragma once
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "sprite.h"
#define GAME_MAX_BULLETS 128


struct Game
{
    size_t width, height;
    size_t num_aliens;
    size_t num_bullets;
    Alien* aliens;
    Player player;
    Bullet bullets[128];
};

void gameInit(Game& game, size_t buffer_width, size_t buffer_height);
