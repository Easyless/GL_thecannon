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

uniform sampler2D textureFirst;
uniform sampler2D textureSecond;

//유니폼 변수

in vec4 pPos;
in vec4 pColor;
in vec4 pNormal;
in vec2 pUv;
out vec4 color;

void main()
{
    vec4 pragColor = pColor * texture(textureFirst,pUv);
    vec4 thisNormal = texture(textureSecond,pUv);
    color = ambientLight * pragColor;
    color += ambientColor * pragColor;
    color += emissiveColor * pragColor;
    if(lightAffect > 0.01)
    {
        for(int i=0;i<7;i++)
        {
            if(lightStrength[i] > 0.01)
            {
                vec4 normal = normalize(pNormal);
                vec4 lightDir = normalize(lightPosition[i] - pPos);
                float diffuse = max(dot(normal,lightDir), 0.0);
                vec4 diffuseColor = diffuse * lightColor[i] * pragColor;

                vec4 reflectVec = normalize(2.0 * normal * dot(normal, lightDir) - lightDir);
                vec4 viewVector = normalize(eyePosition - pPos);
                float specular = pow(max(dot(reflectVec,viewVector),0.0),shininess);

                if(diffuse < 0)
                {
                    specular = 0.0;
                }

                vec4 specularColor = specular * lightColor[i];

                color += (diffuseColor + specularColor) * lightColor[i] * lightStrength[i] * lightAffect;
            }
        }
    }
    // color = normalize(thisNormal);
}