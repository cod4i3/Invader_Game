#version 330
uniform sampler2D buffer;
noperspective in vec2 TexCoord;
out vec3 outColor;

void main(){
    outColor = texture(buffer,TexCoord).rbg;
}
