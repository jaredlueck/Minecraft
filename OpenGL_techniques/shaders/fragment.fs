#version 330 core

out vec4 FragColor;

in vec2 f_texCoord;
in vec3 f_normal;
in vec3 f_pos;

#define MAX_LIGHTS 8

struct PointLight
{
    vec3 position;
	vec3 light_color;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

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

    float shininess;
    float ior;
    float dissolve;

};

layout(std140) uniform Light
{
    PointLight lights[1];
};

uniform Material material;

uniform sampler2D texture_ambient;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform sampler2D normal_map;

uniform bool useNormalMap;

uniform vec3 cameraPos;

flat in vec3 cam_world;

vec3 calculatePointLight(PointLight light);

void main()
{	
	FragColor = vec4(calculatePointLight(lights[0]), 1.0);
};

vec3 calculatePointLight(PointLight light)
{
	vec3 k_a = material.ambient;
	vec3 k_d = material.diffuse;
	vec3 k_s = material.specular; 

	vec3 c_ambient = texture(texture_ambient, f_texCoord).xyz;
    vec3 c_diffuse = texture(texture_diffuse, f_texCoord).xyz;
	vec3 c_specular =  texture(texture_specular, f_texCoord).xyz;

	float shininess = material.shininess;

	vec3 lightDir = normalize(light.position - f_pos);

	vec3 normal;

	if(useNormalMap)
	{
		normal = texture(normal_map, f_texCoord).rgb;
		normal = normalize(normal * 2.0 - 1.0); 
	}
	else
	{
		normal = normalize(f_normal);
	}

	vec3 viewDir = normalize(cam_world - f_pos);

	vec3 reflectDir = reflect(-lightDir, normal);

	float diff = max(dot(normal, lightDir), 0.0);

	float spec = pow(max(dot(reflectDir, viewDir), 0.0), shininess);

	vec3 ambient = k_a * light.light_color * c_ambient;

	vec3 diffuse = k_d  * diff * light.light_color * c_diffuse;

	vec3 specular = k_s * light.specular * spec * c_specular; 

	return ambient + diffuse + specular;
	
}



