#version 300 es

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 anormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec3 frag_pos;

void main()
{
    frag_pos = vec3(model * vec4(position, 1.0));
    normal = mat3(transpose(inverse(model))) * anormal;
	gl_Position = projection * view * model * vec4(position, 1.0f);
}

