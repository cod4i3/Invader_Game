#include "check.h"
#include "shader.h"
#include "texture.h"
#include "buffer.h"
#include "sprite.h"

int main(){
    const size_t buffer_width = 224;
    const size_t buffer_height = 256;
    
    if(!glfwInit()) return -1;
    atexit(glfwTerminate);
    glfwSetErrorCallback(error_callback);
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "Invader Game", NULL, NULL);
    if(!window){
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //フレームバッファのサイズを調べる
    int fbWidth,fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    //ウィンドウ全体をビューポートに設定する
    glViewport(0, 0, fbWidth, fbHeight);
    
    // GLEW を初期化する
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        // GLEW の初期化に失敗した
        std::cerr << "Can't initialize GLEW" << std::endl;
        return 1;
    }
    glfwSwapInterval(1);
    version_show();
    
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
    
    // Create graphics buffer
    uint32_t clear_color = rgb_to_uint32(0, 128, 0);
    Buffer buffer;
    buffer.width  = buffer_width;
    buffer.height = buffer_height;
    buffer.data   = new uint32_t[buffer.width * buffer.height];
    
    buffer_clear(&buffer, clear_color);
    
    createTexture(buffer);
    
    // Create vao for generating fullscreen triangle
    GLuint fullscreen_triangle_vao;
    glGenVertexArrays(1, &fullscreen_triangle_vao);
    
    //プログラムオブジェクトを作成する
    const GLuint program(loadProgram("vertex.shader","fragment.shader"));
    glUseProgram(program);
    
    GLint location = glGetUniformLocation(program, "buffer");
    glUniform1i(location, 0);
    
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(fullscreen_triangle_vao);
    
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        drawAlian(buffer);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
