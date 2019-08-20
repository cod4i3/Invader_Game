#pragma once
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "sprite.h"

struct Game
{
    size_t width, height;
    size_t num_aliens;
    Alien* aliens;
    Player player;
};

