#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec2 TextureCoords;
out vec3 FragmentPosition;
out vec3 Normal;
out vec3 TangentLightPosition;
out vec3 TangentViewPosition;
out vec3 TangentFragPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 view_position;
uniform vec3 light_1_position;

void main()
{
    TextureCoords = aTexCoords;
    FragmentPosition = vec3(model * vec4(aPos, 1.0));
    Normal = aNormal;
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(aNormal, 0.0)));
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    TangentLightPosition = TBN * light_1_position;
    TangentViewPosition  = TBN * view_position;
    TangentFragPosition  = TBN * FragmentPosition;


    gl_Position = projection * view * model * vec4(aPos, 1.0);
}