#include "check.h"
#include "shader.h"
#include "texture.h"
#include "buffer.h"
#include "sprite.h"
#include "game.h"
#include "controller.h" 

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
int move_dir = 0;
bool fire_pressed = true;



int main(){
    const size_t buffer_width = 224;
    const size_t buffer_height = 256;
    
    if(!glfwInit()) return -1;
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
    
    glfwSetKeyCallback(window, key_callback);
    
    
    
    Sprite player_sprite;
    PlayerInit(player_sprite);
    
    Sprite alien_sprites[6];
    Sprite alien_death_sprite;
    alien_spriteInit0(alien_sprites[0]);
    alien_spriteInit1(alien_sprites[1]);
    alien_spriteInit2(alien_sprites[2]);
    alien_spriteInit3(alien_sprites[3]);
    alien_spriteInit4(alien_sprites[4]);
    alien_spriteInit5(alien_sprites[5]);
    alien_death_spriteInit(alien_death_sprite);
    
    SpriteAnimation alien_animation[3];
    for(size_t i = 0; i < 3; ++i)
    {
        alien_animation[i].loop = true;
        alien_animation[i].num_frames = 2;
        alien_animation[i].frame_duration = 10;
        alien_animation[i].time = 0;
        
        alien_animation[i].frames = new Sprite*[2];
        alien_animation[i].frames[0] = &alien_sprites[2 * i];
        alien_animation[i].frames[1] = &alien_sprites[2 * i + 1];
    }
    
    Sprite bullet_sprite;
    bullet_spriteInit(bullet_sprite);
    
    Game game;
    gameInit(game, buffer_width, buffer_height);
    game.num_bullets = 1;
    game.num_aliens = 55;
    game.aliens = new Alien[game.num_aliens];
    
    // 並んでるAlienを用意
    for(size_t yi = 0; yi < 5; ++yi)
    {
        for(size_t xi = 0; xi < 11; ++xi)
        {
            Alien& alien = game.aliens[yi * 11 + xi];
            alien.type = (5 - yi) / 2 + 1;
            
            const Sprite& sprite = alien_sprites[2 * (alien.type - 1)];
            
            alien.x = 16 * xi + 20 + (alien_death_sprite.width - sprite.width)/2;
            alien.y = 17 * yi + 128;
        }
    }
    
    // 死亡カウンター
    uint8_t* death_counters = new uint8_t[game.num_aliens];
    for(size_t i = 0; i < game.num_aliens; ++i) death_counters[i] = 10;
    
    
    int player_move_dir = 0;
    while(!glfwWindowShouldClose(window)){
        buffer_clear(&buffer, clear_color);
        
        // 描画
        for(size_t ai = 0; ai < game.num_aliens; ++ai)
        {
            if(!death_counters[ai]) continue;
            const Alien& alien = game.aliens[ai];
            if(alien.type == ALIEN_DEAD)
            {
                buffer_draw_sprite(&buffer, alien_death_sprite, alien.x, alien.y, rgb_to_uint32(128, 0, 0));
            }
            else
            {
                const SpriteAnimation& animation = alien_animation[alien.type - 1];
                size_t current_frame = animation.time / animation.frame_duration;
                const Sprite& sprite = *animation.frames[current_frame];
                buffer_draw_sprite(&buffer, sprite, alien.x, alien.y, rgb_to_uint32(128, 0, 0));
            }
        }
        
        for(size_t bi = 0; bi < game.num_bullets; ++bi)
        {
            const Bullet bullet = game.bullets[bi];
            const Sprite& sprite = bullet_sprite;
            buffer_draw_sprite(&buffer, sprite, bullet.x, bullet.y, rgb_to_uint32(128, 0, 0));
        }
        
        buffer_draw_sprite(&buffer, player_sprite, game.player.x, game.player.y, rgb_to_uint32(128, 0, 0));
        
        
        //アニメーションの更新
        for(size_t i = 0; i < 3; ++i)
        {
            ++alien_animation[i].time;
            if(alien_animation[i].time == alien_animation[i].num_frames * alien_animation[i].frame_duration)
            {
                alien_animation[i].time = 0;
            }
        }
        
        glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, buffer.width, buffer.height,
                         GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, buffer.data);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        
        
        glfwSwapBuffers(window);
        
        for(size_t ai = 0; ai < game.num_aliens; ++ai)
        {
            const Alien& alien = game.aliens[ai];
            if(alien.type == ALIEN_DEAD && death_counters[ai])
            {
                --death_counters[ai];
            }
        }
        
        
        
        // 弾のシミュレーション
        for(size_t bi = 0; bi < game.num_bullets;)
        {
            bullet_controller(game, bullet_sprite, bi);
            for(size_t ai = 0; ai < game.num_aliens; ++ai)
            {
                const Alien& alien = game.aliens[ai];
                if(alien.type == ALIEN_DEAD) continue;
                
                const SpriteAnimation& animation = alien_animation[alien.type - 1];
                size_t current_frame = animation.time / animation.frame_duration;
                const Sprite alien_sprite = *animation.frames[current_frame];
                bool overlap = sprite_overlap_check(bullet_sprite, game.bullets[bi].x, game.bullets[bi].y,
                                                    alien_sprite,  alien.x,            alien.y);
                if(overlap)
                {
                    game.aliens[ai].type = ALIEN_DEAD;
                    // NOTE: Hack to recenter death sprite
                    game.aliens[ai].x -= (alien_death_sprite.width - alien_sprite.width)/2;
                    game.bullets[bi] = game.bullets[game.num_bullets - 1];
                    --game.num_bullets;
                    continue;
                }
            }
            ++bi;
        }
        
        
        player_move_dir = move_dir * 2;
        player_controller(player_move_dir, game, player_sprite);
        // イベントの途中
        if(fire_pressed && game.num_bullets < GAME_MAX_BULLETS)
        {
            game.bullets[game.num_bullets].x = game.player.x + player_sprite.width / 2;
            game.bullets[game.num_bullets].y = game.player.y + player_sprite.height;
            game.bullets[game.num_bullets].dir = 2;
            ++game.num_bullets;
        }
        fire_pressed = false;
        
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glDeleteVertexArrays(1, &fullscreen_triangle_vao);
    
    for(size_t i = 0; i < 6; ++i)
    {
        delete[] alien_sprites[i].data;
    }
    
    delete[] alien_death_sprite.data;
    
    for(size_t i = 0; i < 3; ++i)
    {
        delete[] alien_animation[i].frames;
    }
    delete[] buffer.data;
    delete[] game.aliens;
    delete[] death_counters;
    
    return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_RIGHT){
        if(action == GLFW_PRESS) move_dir += 1;
        else if(action == GLFW_RELEASE) move_dir -= 1;
    }
    if (key == GLFW_KEY_LEFT){
        if(action == GLFW_PRESS) move_dir -= 1;
        else if(action == GLFW_RELEASE) move_dir += 1;
    }
    if (key == GLFW_KEY_SPACE){
        if(action == GLFW_RELEASE) fire_pressed = true;
    }
}
