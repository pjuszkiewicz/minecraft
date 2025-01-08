#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in mat4 aOffset;

out vec2 TexCoord;
uniform mat4 transform;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 pos = aOffset * vec4(aPos, 1.0);
    gl_Position = projection * view * pos;
    TexCoord = aTexCoord;
}
