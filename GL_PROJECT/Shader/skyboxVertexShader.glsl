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

layout(location = 0) in vec4 vPos;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec4 vNormal;
layout(location = 3) in vec2 vUv;

out vec4 pPos;
out vec4 pColor;
out vec4 pNormal;
out vec2 pUv;
out vec3 texCrood;

void main()
{
    gl_Position = (projTransform * mat4(mat3(viewTransform)) * vPos).xyww;
    texCrood = vec3(vPos.x,vPos.y,vPos.z);
}