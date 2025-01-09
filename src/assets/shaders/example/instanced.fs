#version 330 core

in vec3 FragNormal;
in vec2 TexCoord;

in float ambientOcclusion;
out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec3 lightDirection;

void main()
{
    vec3 normal = normalize(FragNormal);

//     FragColor = texture(ourTexture, TexCoord);

    float intensity = max(dot(normal, normalize(lightDirection)), 0.75);
    vec4 texColor = texture(ourTexture, TexCoord);
    FragColor = vec4(texColor.rgb * intensity, texColor.a);
}
