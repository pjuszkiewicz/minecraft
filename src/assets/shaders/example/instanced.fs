#version 330 core

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

void main()
{
//     vec3 normal = normalize(Normal);
//     vec3 lightDirNorm = normalize(light.direction);
//     vec3 color = texture(ourTexture, TexCoord).rgb;
//     FragColor = vec4(color, 1.0);


    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos); // Kierunek do światła

    float brightness = max(dot(normal, lightDir), 0.0); // Oświetlenie punktowe

    vec3 color = texture(ourTexture, TexCoord).rgb;
    vec3 lighting = color * (0.3 + 0.7 * brightness); // Podstawa + wpływ światła

    FragColor = vec4(lighting, 1.0);


}
