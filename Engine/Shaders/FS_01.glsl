#version 460 core
out vec4 FragColor;

in vec2 TextureCoords;
in vec3 FragmentPosition;
in vec3 Normal;
in vec3 TangentLightPosition;
in vec3 TangentViewPosition;
in vec3 TangentFragPosition;

uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D Texture3;
uniform sampler2D Texture4;
uniform sampler2D Texture5;
uniform sampler2D Texture6;
uniform sampler2D Texture7;
uniform sampler2D Texture8;
uniform sampler2D Texture9;
uniform sampler2D Texture10;
uniform sampler2D Texture11;
uniform sampler2D Texture12;
uniform sampler2D Texture13;
uniform sampler2D Texture14;

uniform int NTextureAlbedo;
uniform int NTextureNormal;
uniform int NTextureMetalic;
uniform int NTextureRoughness;
uniform int NTextureAmbientOclusion;


uniform float shininess;
uniform vec3 specular_strength;

uniform vec3 light_1_position;
uniform vec3 light_1_color;
uniform float light_1_strength;

void main()
{


    vec3 color = texture(Texture0, TextureCoords).rgb;

    // normal map difuse
    vec3 normalTexture = texture(Texture1, TextureCoords).rgb;
    normalTexture = normalize(normalTexture * 2.0 - 1.0); // 0 -> -1  |  0.5 -> 0  |  1 -> 1
    vec3 tangent_lightDirection = normalize(TangentLightPosition - TangentFragPosition);
    float tangent_Perpendicularity = max(dot(tangent_lightDirection, normalTexture), 0.0);
    vec3 normal_diffuse = (light_1_color * color) * (tangent_Perpendicularity);

    //vec3 diffuse = Perpendicularity * color;
    // specular

//    vec3 reflectDirection = reflect(-tangent_lightDirection, normalTexture);
//    vec3 FullReflectionDiscrepancy = normalize(reflectDirection + TangentViewPosition);
//    float specularity = pow(max(dot(normalTexture, FullReflectionDiscrepancy), 0.0), 256);
//    vec3 specular = specularity * texture(Texture2, TextureCoords).rgb;

   
    vec3 viewDir    = normalize(TangentViewPosition - TangentFragPosition);
    vec3 halfwayDir = normalize(tangent_lightDirection + viewDir);
    float specularity = pow(max(dot(normalTexture, halfwayDir), 0.0), 128);
    vec3 specular = specularity * texture(Texture2, TextureCoords).rgb;


    FragColor = vec4(specular + normal_diffuse, 1);
    //FragColor = vec4(normal_diffuse, 1);

}