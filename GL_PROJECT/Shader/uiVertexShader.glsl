#version 330 core
//유니폼 변수
uniform mat4x4 worldTransform;
uniform mat4x4 viewTransform;
uniform mat4x4 projTransform;

uniform vec4 objectColor;
uniform mat4 textureTrasform;

uniform sampler2D textureFirst;
uniform sampler2D textureSecond;

//유니폼 변수

layout(location = 0) in vec4 vPos;
layout(location = 1) in vec2 vUv;

out vec4 pPos;
out vec2 pUv;

void main()
{
    // gl_Position = projTransform * viewTransform * worldTransform * vPos;
    gl_Position = projTransform * worldTransform * vPos;
    pUv = (textureTrasform * vec4(vUv,0.0,1.0)).xy;
}