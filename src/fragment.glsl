#version 330 core

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 Color; // Get the color from the vertex shader

out vec4 FragColor;

uniform DirLight dirLight;
uniform Material material;
uniform sampler2D texture_diffuse;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * Color; // Use vertex color for ambient lighting
    vec3 diffuse = light.diffuse * (diff * Color); // Use vertex color for diffuse lighting
    vec3 specular = light.specular * (spec * material.specular);

    return (ambient + diffuse + specular);
}

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(-FragPos); // Assuming the view position is at the origin
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    vec4 textureColor = texture(texture_diffuse, TexCoords);
    FragColor = textureColor * vec4(result, 1.0);
}
