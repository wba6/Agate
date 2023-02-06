#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

out vec3 FragPos;
out vec3 Normal;
out vec3 lightpos;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    FragPos = vec3(model * vec4(aPos, 1.0));

    //this is very expensive
    Normal = mat3(transpose(inverse(model))) * aNormal;

    lightpos = vec3(model * vec4(lightPos, 1.0));
}