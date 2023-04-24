#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

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


void main()
{    
    FragColor = texture(Texture1, TexCoords);
}