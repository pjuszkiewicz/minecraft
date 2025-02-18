#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform sampler2D texture1;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 WorldPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    WorldPos = vec3(model * vec4(aPos, 1.0));
    Normal = normalize(aNormal);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);

    vec4 pos = model * vec4(aPos, 1.0);
    gl_Position = projection * view * pos;

}