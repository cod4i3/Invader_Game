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
