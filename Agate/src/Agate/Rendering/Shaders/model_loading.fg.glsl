#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;

uniform sampler2D texture_diffuse1;
//uniform vec4 lightPosition;


void main()
{
    vec3 lightPosition = vec3(0.0, 0.0, 0.0);
    //Calculate the light direction
    vec3 lightDirection = normalize(lightPosition - vec3(TexCoords, 0.0));

    // Calculate the normal
    float diff = 1 - max(dot(lightDirection, normalize(Normal)), 0.0);

    // Calculate ambient lighting
    float ambient = 0.2;
    vec4 textureColor = texture(texture_diffuse1, TexCoords);
    FragColor = (diff + ambient) * textureColor;
}
