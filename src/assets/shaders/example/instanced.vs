#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in mat4 aOffset;
layout (location = 6) in vec2 uvOffset;
layout (location = 7) in float ao;
layout (location = 8) in vec3 aNormal;

out vec3 FragNormal;
out vec2 TexCoord;
out vec3 Normal;

out float ambientOcclusion;
out vec3 FragPos;
uniform vec2 uvScale;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;

void main()
{
    ambientOcclusion = ao;
    vec4 pos = aOffset * vec4(aPos, 1.0);

    gl_Position = projection * view * pos;
    TexCoord = uvOffset + aTexCoord * uvScale;

    Normal = mat3(transpose(inverse(aOffset))) * aNormal;
    FragNormal = mat3(transpose(inverse(aOffset))) * aPos;
    FragPos = vec3(aOffset * vec4(aPos, 1.0));
}
