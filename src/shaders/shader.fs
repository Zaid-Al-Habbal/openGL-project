#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 viewPos;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;

struct Light {
    // vec3 position; no longer necessary when using directional lights.
    vec3 direction; //for directional lighting.
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main()
{
    //ambient impact:
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
    
    //diffuse impact:
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction); 
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoord)));
    
    //specular impact:
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoord)));

    
    //final color with lighting:
    vec3 res = (ambient + diffuse + specular);
    FragColor = vec4(res, 1.0);
}