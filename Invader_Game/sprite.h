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

void buffer_draw_sprite(Buffer* buffer, const Sprite& sprite,
                        size_t x, size_t y, uint32_t color);
void drawAlian(Buffer buffer);
