#version 330 core

struct Light {
    //vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


in vec2 TexCoord;
in vec4 FragPosLightSpace;
in vec3 Normal;
in vec3 FragPos;

in float ambientOcclusion;

out vec4 FragColor;

uniform sampler2D shadowMap;
uniform sampler2D ourTexture;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform Light light;

void main()
{
    vec3 normal = normalize(Normal);
    vec3 lightDirNorm = normalize(light.direction);

    vec3 color = texture(ourTexture, TexCoord).rgb;
    float diff = max(dot(normal, -lightDirNorm), 0.0);
    vec3 lighting = color * (0.3 + 0.7 * diff);
//     FragColor = vec4(lighting, 1.0);
    FragColor = vec4(normalize(normal) * 0.5 + 0.5, 1.0);
}
