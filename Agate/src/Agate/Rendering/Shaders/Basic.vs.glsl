#version 410 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec4 Color;
uniform vec4 Ucolors;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec4 colors;

void main(){
    gl_Position = vec4(Pos, 1.0);
    colors = Color;
}

