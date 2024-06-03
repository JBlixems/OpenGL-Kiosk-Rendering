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
in vec4 Color; 

out vec4 FragColor;

uniform DirLight dirLight;
uniform Material material;
uniform sampler2D texture_diffuse;
uniform bool useColor;
uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 color = Color.rgb;
    vec3 lightDir = -light.direction;
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * color;
    vec3 diffuse = light.diffuse * (diff * color);
    vec3 specular = light.specular * (spec * color);

    return (ambient + diffuse + specular);
}

void main()
{
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = CalcDirLight(dirLight, Normal, viewDir);

    if(useColor){
        FragColor = vec4(result, Color.a);
    }else{
        vec4 textureColor = texture(texture_diffuse, TexCoords);
        FragColor = textureColor * vec4(result, Color.a);
    }
}
