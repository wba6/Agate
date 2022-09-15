#version 410 core
layout (location = 0) in vec3 Pos;

uniform vec4 Ucolors;
uniform mat4 rotation;
out vec4 colors;

void main(){
    gl_Position = vec4(Pos, 1.0) * rotation;
    colors = Ucolors;

}
