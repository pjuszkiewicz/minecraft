#version 330 core

uniform vec3 viewPos;
uniform mat4 model;

out vec4 FragColor;
in vec2 TexCoord;
in vec3 fragPos;
in vec3 fragNormal;
in vec3 normal;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

void main()
{
    vec3 lightAmbient = vec3(0.4, 0.4, 0.4);
    vec3 lightPosition = vec3(5.0, 5.0, 5.0);
    vec3 lightDiffuse = vec3(1.0, 1.0, 1.0);
    vec3 lightSpecular = vec3(1.0, 1.0, 1.0);

    vec3 ambient = lightAmbient * material.ambient;

    vec3 lightDir = normalize(lightPosition - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = lightDiffuse * (diff * material.diffuse);

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightSpecular * (spec * material.specular);

    FragColor = vec4(ambient + diffuse + specular, 1.0);

    // Flat shading
    //     vec3 edge1 = dFdx(fragPos);
    //     vec3 edge2 = dFdy(fragPos);
    //     vec3 norm = normalize(cross(edge1, edge2));
    //     norm = mat3(transpose(inverse(model))) * norm;

    // Test normalnych
    //     vec3 color = normalize(normal) * 0.5 + 0.5;
    //     FragColor = vec4(color, 1.0);
}
