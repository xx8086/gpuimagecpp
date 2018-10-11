#version 300 es
precision mediump float;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 view_pos;

in vec3 normal;
in vec3 frag_pos;
in vec3 light_color;

out vec4 FragColor;
void main()
{
    // ambient
    vec3 ambient = light_color * light.ambient * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - frag_pos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light_color * light.diffuse * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(view_pos - frag_pos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
