#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;        // Position of the fragment in world space
    vec2 TexCoords;      // Texture coordinates
    mat3 TBN;            // Tangent-Bitangent-Normal matrix for normal mapping
} fs_in;

// Material structure with arrays of sampler2D
struct Material {
    sampler2D texture_diffuse[8];
    int num_diffuse;

    sampler2D texture_specular[8];
    int num_specular;

    sampler2D texture_normal[8];
    int num_normal;

    sampler2D texture_height[8];
    int num_height;
};

uniform Material material;

// Point Light structure
struct PointLight {
    vec3 Position;
    vec3 Color;
    float Intensity;

// Attenuation factors
    float Constant;
    float Linear;
    float Quadratic;
};

uniform PointLight pointLight;

// Camera position
uniform vec3 viewPos;

void main()
{
    // Initialize material colors
    vec3 diffuseColor = vec3(0.0);
    vec3 specularColor = vec3(0.0);
    vec3 normal = vec3(0.0, 0.0, 1.0);

    // Accumulate diffuse textures
    for(int i = 0; i < material.num_diffuse; i++) {
        diffuseColor += vec3(texture(material.texture_diffuse[i], fs_in.TexCoords));
    }
    if(material.num_diffuse > 0)
    diffuseColor /= float(material.num_diffuse); // Average if multiple

    // Accumulate specular textures
    for(int i = 0; i < material.num_specular; i++) {
        specularColor += vec3(texture(material.texture_specular[i], fs_in.TexCoords));
    }
    if(material.num_specular > 0)
    specularColor /= float(material.num_specular); // Average if multiple

    // Accumulate normal maps
    for(int i = 0; i < material.num_normal; i++) {
        vec3 normMap = texture(material.texture_normal[i], fs_in.TexCoords).rgb;
        normMap = normalize(normMap * 2.0 - 1.0); // Transform from [0,1] to [-1,1]
        normal += normMap * (1.0 / float(material.num_normal));
    }
    if(material.num_normal > 0)
    normal = normalize(normal); // Normalize the final normal

    // Ambient lighting
    vec3 ambient = 0.1 * pointLight.Color * diffuseColor;

    // Diffuse lighting
    vec3 lightDir = normalize(pointLight.Position - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * pointLight.Color * diffuseColor;

    // Specular lighting
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * pointLight.Color * specularColor;

    // Attenuation
    float distance    = length(pointLight.Position - fs_in.FragPos);
    float attenuation = 1.0 / (pointLight.Constant + pointLight.Linear * distance +
    pointLight.Quadratic * (distance * distance));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    // Combine results
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
