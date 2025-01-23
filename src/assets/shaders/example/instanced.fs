#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

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


uniform Material material;
uniform Light light;

// float ShadowCalculation(vec4 fragPosLightSpace)
// {
//     // perform perspective divide
//     vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
//     // transform to [0,1] range
//     projCoords = projCoords * 0.5 + 0.5;
//     // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
//     float closestDepth = texture(shadowMap, projCoords.xy).r;
//     // get depth of current fragment from light's perspective
//     float currentDepth = projCoords.z;
//     // check whether current frag pos is in shadow
//     float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;
//
//     return shadow;
// }


float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir) {
    // Przemieniamy z [-1, 1] na [0, 1]:
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    // Pobieramy głębokość z mapy cieni
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    // Liczymy bias w zależności od kąta światło-normalna
    float bias = max(0.005 * (1.0 - dot(normal, -lightDir)), 0.002);

    // Sprawdzamy, czy fragment jest w cieniu
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    // Ignorujemy fragmenty poza zakresem mapy głębokości
    if (projCoords.z > 1.0) {
        shadow = 0.0;
    }

    return shadow;
}

void main()
{
    vec3 normal = normalize(Normal);
    vec3 lightDirNorm = normalize(light.direction);

    vec3 color = texture(ourTexture, TexCoord).rgb;

    float shadow = ShadowCalculation(FragPosLightSpace, normal, light.direction);

    FragColor = (1.0 - shadow) * vec4(color, 1.0f);
//     vec3 normal = normalize(Normal);
//     vec3 lightColor = vec3(1.0);
//     // ambient
//     vec3 ambient = 0.15 * lightColor;
//     // diffuse
//     vec3 lightDir = normalize(lightPos - FragPos);
//     float diff = max(dot(lightDir, normal), 0.0);
//     vec3 diffuse = diff * lightColor;
//     // specular
//     vec3 viewDir = normalize(viewPos - FragPos);
//     float spec = 0.0;
//     vec3 halfwayDir = normalize(lightDir + viewDir);
//     spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
//     vec3 specular = spec * lightColor;
//     // calculate shadow
//     float shadow = ShadowCalculation(FragPosLightSpace);
//     vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
//
//     FragColor = vec4(lighting, 1.0);
//     vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;
//
//     // diffuse
//     vec3 norm = normalize(Normal);
//     // vec3 lightDir = normalize(light.position - FragPos);
//     vec3 lightDir = normalize(-light.direction);
//     float diff = max(dot(norm, lightDir), 0.0);
//     vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;
//
//     // specular
//     vec3 viewDir = normalize(viewPos - FragPos);
//     vec3 reflectDir = reflect(-lightDir, norm);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//     vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;
//
//     vec3 result = ambient + diffuse + specular;
//
//     FragColor = vec4(result, 1.0);

//     float ambientStrength = 0.1;
//     vec3 ambient = ambientStrength * vec3(1.0);
//
//     vec3 norm = normalize(Normal);
//     vec3 lightDir = normalize(-light.direction);
//
//     vec4 texColor = texture(ourTexture, TexCoord);
//
//     vec3 result = texColor.rgb;
//     FragColor = vec4(result, 1.0);
}
