#include "shader.h"

// シェーダオブジェクトのコンパイル結果を表示する
// shader: シェーダオブジェクト名
// str:    コンパイルエラーが発生した場所を示す文字列

GLboolean printShaderInfoLog(GLuint shader,const char *str){
    //コンパイル結果を取得する
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) std :: cerr << "Compile Error in " << str << std::endl;
    
    //シェーダのコンパイル時のログの長さを取得する
    GLsizei bufSize;
    glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&bufSize);
    
    if(bufSize > 1){
        //シェーダのコンパイル時のログの内容を取得する
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetShaderInfoLog(shader,bufSize,&length,&infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }
    
    return static_cast<GLboolean>(status);
}

//プログラムオブジェクトのリンク結果をg表示する
// program:プログラムオブジェクト名

GLboolean printProgramInfoLog(GLuint program){
    //リンク結果を取得する
    GLint status;
    glGetProgramiv(program,GL_LINK_STATUS,&status);
    if(status == GL_FALSE) std::cerr << "Link Error." << std::endl;
    
    //シェーダのリンク時のログの長さを取得する
    GLsizei bufsize;
    glGetProgramiv(program,GL_INFO_LOG_LENGTH,&bufsize);
    
    if(bufsize > 1){
        //シェーダのリンク時のログの内容を取得する
        std::vector<GLchar> infoLog(bufsize);
        GLsizei length;
        glGetProgramInfoLog(program,bufsize,&length,&infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }
    
    return static_cast<GLboolean>(status);
}


GLuint createProgram(const char *vsrc, const char *fsrc){
    const GLuint program(glCreateProgram());
    
    // バーテックスシェーダ組み込み
    if(vsrc != NULL){
        const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
        glShaderSource(vobj,1,&vsrc,NULL);
        glCompileShader(vobj);
        
        if(printShaderInfoLog(vobj,"vertex shader"))
            glAttachShader(program,vobj);
        glDeleteShader(vobj);
        
    }
    
    // フラグメントシェーダ組み込み
    if(fsrc != NULL){
        const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
        glShaderSource(fobj,1,&fsrc,NULL);
        glCompileShader(fobj);
        
        if(printShaderInfoLog(fobj,"fragment shader"))
            glAttachShader(program,fobj);
        glDeleteShader(fobj);
    }
    
    glLinkProgram(program);
    
    //作成したプログラムオブジェクトを返す
    if(printProgramInfoLog(program))
        return program;
    
    glDeleteProgram(program);
    return 0;
}

bool readShaderSource(const char *name,std::vector<GLchar> &buffer){
    //ファイル名がNULL
    if(name == NULL) return false;
    
    //ソースファイルを開く
    std::ifstream file(name,std::ios::binary);
    if(file.fail()){
        //開けなかった場合
        std::cerr << "Error: Can't open source file: " << name << std::endl;
        return false;
    }
    
    //ファイルの末尾に移動し現在位置（＝ファイルサイズ）を得る
    file.seekg(0L,std::ios::end);
    GLsizei length = static_cast<GLsizei>(file.tellg());
    
    //ファイルサイズのメモリを確保
    buffer.resize(length + 4);
    
    //ファイルを先頭から読み込む
    file.seekg(0L,std::ios::beg);
    file.read(buffer.data(),length);
    buffer[length] = '\n';
    
    if(file.fail()){
        //上手く読み込めなかった
        std::cerr << "Error: Could not read source file" << name << std::endl;
        file.close();
        return false;
    }
    
    //読み込み成功
    file.close();
    return true;
}

GLuint loadProgram(const char *vert,const char *frag){
    
    //シェーダのソースファイルを読み込む
    std::vector<GLchar> vsrc;
    const bool vstat(readShaderSource(vert, vsrc));
    std::vector<GLchar> fsrc;
    const bool fstat(readShaderSource(frag, fsrc));
    
    //プログラムオブジェクトを作成する
    return vstat && fstat ? createProgram(vsrc.data(), fsrc.data()) : 0;
}
