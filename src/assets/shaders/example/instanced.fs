#version 330 core

in vec3 FragNormal;
in vec2 TexCoord;

in float ambientOcclusion;
out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec3 lightDirection;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0);

    vec3 normal = normalize(FragNormal);

//     FragColor = texture(ourTexture, TexCoord);

    float intensity = max(dot(normal, normalize(lightDirection)), 0.75);
    vec4 texColor = texture(ourTexture, TexCoord);


    vec3 result = texColor.rgb * ambient;
    FragColor = vec4(result, texColor.a);
}
