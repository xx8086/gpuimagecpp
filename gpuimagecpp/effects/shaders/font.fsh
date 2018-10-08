#version 300 es
precision lowp float;
in vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
uniform sampler2D worlds_texture;
layout(location = 0) out vec4 FragColor;
void main(void){
    FragColor = texture(inputImageTexture, textureCoordinate);
    vec4 fontcolor = texture(worlds_texture, textureCoordinate);
    if(fontcolor.w > 0.0){
        FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    }
}
