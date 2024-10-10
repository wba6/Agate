#version 330 core
layout (location = 0) in vec3 aPos;        // Vertex positions
layout (location = 1) in vec3 aNormal;     // Vertex normals
layout (location = 2) in vec2 aTexCoords;  // Vertex texture coordinates
layout (location = 3) in vec3 aTangent;    // Vertex tangents
layout (location = 4) in vec3 aBitangent;  // Vertex bitangents

out VS_OUT {
    vec3 FragPos;        // Position of the fragment in world space
    vec2 TexCoords;      // Texture coordinates
    mat3 TBN;            // Tangent-Bitangent-Normal matrix for normal mapping
} vs_out;

// Uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Calculate world space position of the vertex
    vec3 FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.FragPos = FragPos;

    // Pass texture coordinates to fragment shader
    vs_out.TexCoords = aTexCoords;

    // Create TBN matrix for transforming to tangent space
    vec3 T = normalize(mat3(model) * aTangent);
    vec3 B = normalize(mat3(model) * aBitangent);
    vec3 N = normalize(mat3(model) * aNormal);
    vs_out.TBN = mat3(T, B, N);

    // Final vertex position
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
