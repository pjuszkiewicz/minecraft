#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


out vec3 fragPos;
out vec3 fragNormal;

void main()
{
    vec4 pos = model * vec4(aPos, 1.0);
    gl_Position = projection * view * pos;
    TexCoord = aTexCoord;

    fragPos = vec3(model * vec4(aPos, 1.0));
    //fragNormal = mat3(transpose(inverse(model))) * aNormal;
}
