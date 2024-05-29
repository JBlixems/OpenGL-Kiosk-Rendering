#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 Color;

uniform sampler2D texture_diffuse;
uniform bool useColor;

void main()
{
    vec3 texColor = texture(texture_diffuse, TexCoords).rgb;
    vec3 finalColor = texColor * Color;
    FragColor = vec4(finalColor, 1.0);
}
