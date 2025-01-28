#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in mat4 aOffset;
layout (location = 6) in vec2 uvOffset;
layout (location = 7) in float ao;
layout (location = 8) in vec3 aNormal;

out vec3 FragNormal;
out vec3 FragPos;
out vec2 TexCoord;
out vec3 Normal;
out vec4 FragPosLightSpace;

out float ambientOcclusion;
uniform vec2 uvScale;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
    ambientOcclusion = ao;

    vec4 model = aOffset * vec4(aPos, 1.0);

    FragPos = vec3(model);
    //Normal = mat3(transpose(inverse(mat3(aOffset)))) * aNormal;
    Normal = aNormal;
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);

    TexCoord = uvOffset + aTexCoord * uvScale;

    gl_Position = projection * view * model;
}
