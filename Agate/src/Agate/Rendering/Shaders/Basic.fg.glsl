#version 330 core
out vec4 FragColor;

in vec4 colors;
void main()
{
    FragColor = vec4(colors);
}
