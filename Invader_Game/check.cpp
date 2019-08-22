#include "check.h"

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error.%s\n", description);
}

void version_show(){
    int glVersion[2] = {-1, 1};
    glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
    printf("Using OpenGL: %d.%d\n",glVersion[0],glVersion[1]);
}

bool sprite_overlap_check(Sprite sp_a, size_t x_a, size_t y_a,
                          Sprite sp_b, size_t x_b, size_t y_b)
{
    if(x_a < x_b + sp_b.width && x_a + sp_a.width > x_b &&
       y_a < y_b + sp_b.height && y_a + sp_a.height > y_b)
    {
        return true;
    }
    
    return false;
}
