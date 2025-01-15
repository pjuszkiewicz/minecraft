#version 330 core

out vec4 FragColor;  
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform vec3 lightColor;   // Kolor słońca (np. żółto-pomarańczowy)
uniform vec3 sunCenter;    // Pozycja środka słońca
uniform float sunRadius;

in vec3 fragPos;
  
void main()
{
//     FragColor = texture(ourTexture, TexCoord);
// Obliczanie odległości od środka słońca
    float dist = length(fragPos - sunCenter);
//     float intensity = 1.0 - smoothstep(0.0, sunRadius, dist);
float intensity = 1.0;

    // Gradientowy kolor (jasnożółty w środku, pomarańczowy na krawędziach)
    vec3 gradientColor = mix(vec3(1.0, 0.5, 0.1), lightColor, intensity);

    // Emisja światła - im bliżej środka, tym jaśniej
    vec3 emissive = gradientColor * intensity;

    // Finalny kolor
//     FragColor = vec4(emissive, 1.0);
//     FragColor = vec4(1.0, 1.0, 1.0, 1.0);
FragColor = vec4(1.0, 0.9, 0.4, 1.0);
}
