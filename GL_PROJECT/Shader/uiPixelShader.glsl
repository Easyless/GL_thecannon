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

in vec4 pPos;
in vec2 pUv;
out vec4 color;

void main()
{
    // color = objectColor * texture(textureFirst,pUv);
    color = objectColor * texture(textureFirst,pUv);
    // if (color.a < 0.1)
    // {
    //     discard;
    // }
}