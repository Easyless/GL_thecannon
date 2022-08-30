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

in vec4 pPos;
in vec4 pColor;
in vec4 pNormal;
out vec4 color;

void main()
{
    color = ambientLight * pColor;
    for(int i=0;i<7;i++)
    {
        if(lightStrength[i] > 0.01)
        {
            vec4 normal = normalize(pNormal);
            vec4 lightDir = normalize(lightPosition[i] - pPos);
            float diffuse = max(dot(normal,lightDir), 0.0);
            vec4 diffuseColor = diffuse * lightColor[i] * pColor;

            int sh = 4;
            vec4 reflectVec = normalize(2.0 * normal * dot(normal, lightDir) - lightDir);
            vec4 viewVector = normalize(eyePosition - pPos);
            float specular = pow(max(dot(reflectVec,viewVector),0.0),sh);

            if(diffuse < 0)
            {
                specular = 0.0;
            }

            vec4 specularColor = specular * lightColor[i];

            color += (diffuseColor + specularColor) * lightColor[i] * lightStrength[i];
        }
    }
}