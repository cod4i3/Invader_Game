#pragma once
#include <cstdlib>
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "sprite.h"

void error_callback(int error, const char* description);
void version_show();

bool sprite_overlap_check(Sprite sp_a, size_t x_a, size_t y_a,
                          Sprite ap_b, size_t x_b, size_t y_b);
