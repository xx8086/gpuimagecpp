#version 300 es
precision mediump float;
in vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
layout(location = 0) out vec4 FragColor;
void main(void){
    vec4 color = texture(inputImageTexture, vec2(textureCoordinate.x, 1.0 - textureCoordinate.y));
    FragColor = vec4(color.z, color.y, color.x, color.w);
}
