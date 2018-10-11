#version 300 es

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 anormal;
layout (location = 2) in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec3 frag_pos;
out vec3 light_color;

void main()
{
    frag_pos = vec3(model * vec4(position, 1.0));
    normal = mat3(transpose(inverse(model))) * anormal;
    light_color = color;
	gl_Position = projection * view * model * vec4(position, 1.0f);
}
