#version 330 core

in vec3 FragNormal;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

in float ambientOcclusion;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0);

    vec3 normal = normalize(FragNormal);


//     float intensity = max(dot(normal, normalize(lightDirection)), 0.75);


    vec4 texColor = texture(ourTexture, TexCoord);

    vec3 result = texColor.rgb * ambientOcclusion;
    FragColor = vec4(result, 1.0);
//     FragColor = texture(ourTexture, TexCoord);


//
//     vec3 norm = normalize(Normal);
// //     vec3 lightDir = normalize(lightPos - FragPos);
//     vec3 lightDir = normalize(-lightPos);
//
//     float diff = max(dot(norm, lightDir), 0.0);
//     vec3 diffuse = diff * vec3(1.0);
//
//     float specularStrength = 1.0;
//     vec3 viewDir = normalize(viewPos - FragPos);
//     vec3 reflectDir = reflect(-lightDir, norm);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//     vec3 specular = specularStrength * spec * vec3(1.0);
//
//     vec3 result = texColor.rgb * (ambient + diffuse + specular);
//     FragColor = vec4(result, 1.0);
}
