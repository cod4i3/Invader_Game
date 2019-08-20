#pragma once
#include <cstdlib>
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdint>


struct Buffer
{
    size_t  width, height;
    uint32_t* data; //2^8  = 256 , RGB値
};
uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b);
void buffer_clear(Buffer* buffer, uint32_t color);

