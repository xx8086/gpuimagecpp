#version 300 es
precision mediump float;

out vec4 FragColor;
uniform vec3 grid_color;
void main()
{
    FragColor = vec4(grid_color, 1.0f);
}
