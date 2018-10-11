#version 300 es
precision highp float;
in vec2 TexCoord0;
//in vec3 Normal0;
//in vec3 WorldPos0;
uniform sampler2D color_map;
layout(location = 0) out vec4 FragColor;

void main()
{
    FragColor = texture(color_map, TexCoord0.xy) ;
}
