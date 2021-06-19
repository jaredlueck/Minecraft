#version 330 core

out vec4 FragColor;
in vec2 f_texCoord;

uniform sampler2D texture_ambient;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;

#define MAX_LIGHTS 8

struct PointLight
{
    vec3 position;
    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight 
{
    vec3 position;
    vec3 direction;
    
    float constant;
    float linear;
    float quadratic;
};

struct Spotlight 
{
    vec3 position;
    vec3 direction;

    float cutoff;
    
    float constant;
    float linear;
    float quadratic;
};

struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 transmittance;
    vec3 specular;

    float shininess;
    float ior;
    float disolve;

    int illum;

    float shininess;
    float ior;
    float disolve;

    int illum;

    bool useDiffuseAsAmbient;

    bool transmittance;
    bool emission;
    bool normalMap;
};

layout(std140) uniform Light
{
    PointLight lights[1];
};

uniform sampler2D texture_ambient;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform sampler2D normal_map;

void main()
{
    FragColor = vec4(lights[0].position, 1.0);
};

