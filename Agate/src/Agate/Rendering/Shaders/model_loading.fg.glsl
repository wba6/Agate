#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{
    vec4 ambient = vec4(0.2, 0.2, 0.2, 1.0);
    vec4 textureColor = texture(texture_diffuse1, TexCoords);
    FragColor = ambient * textureColor;
}
