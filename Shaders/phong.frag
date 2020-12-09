#version 330 core
//precision mediump float;

#define MAX_DIRECTION_LIGHTS 8
#define MAX_POINT_LIGHTS 64
#define MAX_SPOT_LIGHTS 32

struct DirectionLight 
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; 
struct PointLight 
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
struct SpotLight 
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

struct Material 
{
	sampler2D diffuse;
	vec3 diffuseColor;
    sampler2D specular;
	sampler2D emission;
    float shininess;
}; 


in vec3 fPosition;
in vec3 fNormal;
in vec2 fTexCoord;

in vec3 fViewPos;

uniform Material uMaterial;

uniform int uDirectionLightAmount;
uniform int uPointLightAmount;
uniform int uSpotLightAmount;

uniform DirectionLight uDirectionLights[MAX_DIRECTION_LIGHTS];
uniform PointLight uPointLights[MAX_POINT_LIGHTS];
uniform SpotLight uSpotLights[MAX_SPOT_LIGHTS];

vec3 CalcDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main()
{
    // properties
    vec3 norm = normalize(fNormal);
    vec3 viewDir = normalize(fViewPos - fPosition);
    
    vec3 result = vec3(0.0f);
    
    // directional lights
    for(int i = 0; i < uDirectionLightAmount; i++)
    {
        result += CalcDirectionLight(uDirectionLights[i], norm, viewDir);
    }

    // point lights
    for(int i = 0; i < uPointLightAmount; i++)
    {
        result += CalcPointLight(uPointLights[i], norm, fPosition, viewDir);    
    }
    
    // spot lights
    for(int i = 0; i < uSpotLightAmount; i++)
    {
        result += CalcSpotLight(uSpotLights[i], norm, fPosition, viewDir);    
    }

    //vec3 emission = texture(uMaterial.emission, fTexCoord).rgb;

    //gl_FragColor = vec4(result + emission, 1.0);
    gl_FragColor = vec4(result, 1.0);

}

vec3 CalcDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(uMaterial.diffuse, fTexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(uMaterial.diffuse, fTexCoord)) * uMaterial.diffuseColor;
    vec3 specular = light.specular * spec * vec3(texture(uMaterial.specular, fTexCoord));
    
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(uMaterial.diffuse, fTexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(uMaterial.diffuse, fTexCoord)) * uMaterial.diffuseColor;
    vec3 specular = light.specular * spec * vec3(texture(uMaterial.specular, fTexCoord));
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(uMaterial.diffuse, fTexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(uMaterial.diffuse, fTexCoord)) * uMaterial.diffuseColor;
    vec3 specular = light.specular * spec * vec3(texture(uMaterial.specular, fTexCoord));
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}