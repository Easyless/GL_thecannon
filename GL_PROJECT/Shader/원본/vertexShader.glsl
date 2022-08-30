#version 330 core
uniform mat4x4 worldTransform;
uniform mat4x4 viewTransform;
uniform mat4x4 projTransform;
uniform vec4 diffuseColor;
uniform vec4 eyePosition;

uniform vec4 ambientLight;
uniform vec4 lightPosition[7];
uniform vec4 lightColor[7];
uniform float lightStrength[7];

layout(location = 0) in vec4 vPos;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec4 vNormal;

out vec4 pPos;
out vec4 pColor;
out vec4 pNormal;

void main()
{
    gl_Position = projTransform * viewTransform * worldTransform * vPos;
    pPos = worldTransform * vPos;
    pNormal = normalize(worldTransform * vNormal);
    pColor = diffuseColor * (vColor);

    
}