#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aOffset;
layout (location = 3) in int visibilityMask; // Mask widoczności ścian (6 bitów)


out vec2 TexCoord;
uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    gl_Position = projection * view * vec4(aPos + aOffset, 1.0);
    TexCoord = aTexCoord;
}
