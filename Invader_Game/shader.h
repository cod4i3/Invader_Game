#pragma once
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdint>

// シェーダオブジェクトのコンパイル結果を表示する
// shader: シェーダオブジェクト名
// str:    コンパイルエラーが発生した場所を示す文字列
GLboolean printShaderInfoLog(GLuint shader,const char *str);
//プログラムオブジェクトのリンク結果を表示する
GLboolean printProgramInfoLog(GLuint program);
GLuint createProgram(const char *vsrc, const char *fsrc);
bool readShaderSource(const char *name,std::vector<GLchar> &buffer);

// 最終的にはこれを使う
GLuint loadProgram(const char *vert,const char *frag);
