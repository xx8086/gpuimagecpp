#version 300 es
precision mediump float;
in vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
uniform sampler2D worlds_texture;
uniform vec3 world_color;
layout(location = 0) out vec4 FragColor;
void main(void){
    FragColor = texture(inputImageTexture, textureCoordinate);
    vec4 fontcolor = texture(worlds_texture, textureCoordinate);
    if (fontcolor.w > 0.5){
        FragColor = vec4(world_color, 1.0);
    }
}
