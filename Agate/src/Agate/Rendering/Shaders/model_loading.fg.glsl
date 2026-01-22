#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
// uniform vec3 lightPos; // Ideally, pass this from C++

void main()
{
    // (Hardcoded for now, but ideally pass as uniform)
    vec3 lightPos = vec3(0.0, 10.0, 10.0); 

    // Calculate Light Direction
    // Direction = Target (Light) - Source (Fragment)
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos); 

    // Calculate Diffuse Impact
    // Dot product gives -1 to 1. Max clamps it to 0.0 (no negative light)
    float diff = max(dot(norm, lightDir), 0.0);

    // Combine
    float ambient = 0.2;
    vec4 textureColor = texture(texture_diffuse1, TexCoords);
    
    // Apply lighting to the texture
    vec3 result = (ambient + diff) * textureColor.rgb;
    
    FragColor = vec4(result, textureColor.a);
}
