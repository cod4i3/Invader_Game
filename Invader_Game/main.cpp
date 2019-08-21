#include "check.h"
#include "shader.h"
#include "texture.h"
#include "buffer.h"
#include "sprite.h"
#include "game.h"
#include "controller.h"

int main(){
    const size_t buffer_width = 224;
    const size_t buffer_height = 256;
    int player_move_dir = 1;
    
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
    
    Sprite player_sprite;
    PlayerInit(player_sprite);
    Sprite alien_sprite0;
    alien_spriteInit0(alien_sprite0);
    Sprite alien_sprite1;
    alien_spriteInit1(alien_sprite1);
    SpriteAnimation* alien_animation = new SpriteAnimation;
    alien_animationInit(alien_animation);
    alien_animation->frames = new Sprite*[2];
    alien_animation->frames[0] = &alien_sprite0;
    alien_animation->frames[1] = &alien_sprite1;
    
    Game game;
    gameInit(game, buffer_width, buffer_height);
    game.aliens = new Alien[game.num_aliens];
    
    
    for(size_t yi = 0; yi < 5; ++yi)
    {
        for(size_t xi = 0; xi < 11; ++xi)
        {
            game.aliens[yi * 11 + xi].x = 16 * xi + 20;
            game.aliens[yi * 11 + xi].y = 17 * yi + 128;
        }
    }
    
    while(!glfwWindowShouldClose(window)){
        buffer_clear(&buffer, clear_color);
        
        for(size_t ai = 0; ai < game.num_aliens; ++ai)
        {
            const Alien& alien = game.aliens[ai];
            size_t current_frame = alien_animation->time / alien_animation->frame_duration;
            const Sprite& sprite = *alien_animation->frames[current_frame];
            buffer_draw_sprite(&buffer, sprite, alien.x, alien.y, rgb_to_uint32(128, 0, 0));
        }
        
        buffer_draw_sprite(&buffer, player_sprite, game.player.x, game.player.y, rgb_to_uint32(128, 0, 0));
        ++alien_animation->time;

        if(alien_animation->time == alien_animation->num_frames * alien_animation->frame_duration)
        {
            if(alien_animation->loop) alien_animation->time = 0;
            else
            {
                delete alien_animation;
                alien_animation = nullptr;
            }
        }
        
        glTexSubImage2D(
                        GL_TEXTURE_2D, 0, 0, 0,
                        buffer.width, buffer.height,
                        GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,
                        buffer.data
                        );
        
        player_move_dir = player_controller(player_move_dir, game, player_sprite);
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    glDeleteVertexArrays(1, &fullscreen_triangle_vao);
    
    delete[] alien_sprite0.data;
    delete[] alien_sprite1.data;
    delete[] alien_animation->frames;
    delete[] buffer.data;
    delete[] game.aliens;
    
    delete alien_animation;
    
    return 0;
}
