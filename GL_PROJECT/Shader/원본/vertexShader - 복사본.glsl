#version 330 core

uniform mat4x4 worldTransform;
uniform mat4x4 viewTransform;
uniform mat4x4 projTransform;
uniform vec4 diffuseColor;

layout(location = 0) in vec4 vPos;
layout(location = 1) in vec4 vColor;

out vec4 pColor;

void main()
{
    gl_Position = projTransform * viewTransform * worldTransform * vPos;
    pColor = diffuseColor * (vColor);
}