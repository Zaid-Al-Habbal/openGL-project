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
    vec3 position; //no longer necessary when using directional lights.
    vec3 direction; //for directional lighting.
    //(need both for spotlight)
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Light light;

void main()
{
    vec3 lightDir = normalize(light.position - FragPos); 
    //for spotlight:
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    //ambient impact:
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord)).rgb;
    
    //diffuse impact:
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoord))).rgb;
    
    //specular impact:
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoord))).rgb;

    //calculate the attenuation for point light:
    float dist = length(light.position - FragPos);
    float attenuation = (1.0 / (light.constant + light.linear * dist + 
                            light.quadratic * (dist * dist))) * intensity;

    //for spotlight:
    //final color with lighting:
    diffuse   *= attenuation;
    specular *= attenuation; 
    vec3 res = ambient + diffuse + specular;

    FragColor = vec4(res, 1.0);
}