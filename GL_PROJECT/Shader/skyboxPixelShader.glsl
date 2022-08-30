#version 330 core
//유니폼 변수
uniform mat4x4 worldTransform;
uniform mat4x4 viewTransform;
uniform mat4x4 projTransform;
uniform vec4 eyePosition;

//라이트 부분
uniform vec4 ambientLight;
uniform vec4 lightPosition[7];
uniform vec4 lightColor[7];
uniform float lightStrength[7];

//메테리얼 부분
uniform vec4 objectColor;
uniform vec4 diffuseAlbedo;
uniform int shininess;
uniform vec4 emissiveColor;
uniform vec4 ambientColor;
uniform float lightAffect;
uniform vec3 fresnelR0;
uniform float roughness;

uniform mat4 textureTrasform;

uniform samplerCube textureFirst;
uniform sampler2D textureSecond;

//유니폼 변수

in vec4 pPos;
in vec4 pColor;
in vec4 pNormal;
in vec2 pUv;
in vec3 texCrood;

out vec4 color;

void main()
{
    color = texture(textureFirst,texCrood) * objectColor;
}