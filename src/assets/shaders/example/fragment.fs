#version 330 core

out vec4 FragColor;  
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform vec3 lightColor;   // Kolor słońca (np. żółto-pomarańczowy)
uniform vec3 sunCenter;    // Pozycja środka słońca
uniform float sunRadius;

in vec3 fragPos;

uniform vec3 color;

void main()
{
FragColor = vec4(color, 1.0);
// FragColor = vec4(1.0, 0.9, 0.4, 1.0);
}
