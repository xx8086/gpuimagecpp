#version 300 es
precision mediump float;
in vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
uniform sampler2D love_texture;
uniform vec2 love_postion;
const float love_width = 0.2;
const float love_height = 0.2;
layout(location = 0) out vec4 FragColor;

float transf(float x, float b){
    return x * 5.0;
}

void main(void){
    vec4 color = texture(inputImageTexture, vec2(textureCoordinate.x, 1.0 - textureCoordinate.y));
    FragColor = vec4(color.z, color.y, color.x, color.w);
    if (love_postion.y < textureCoordinate.y && love_postion.x < textureCoordinate.x &&
        textureCoordinate.y < (love_postion.y + love_height) && textureCoordinate.x < (love_postion.x + love_width)){
        vec4 colorlove = texture(love_texture, vec2((textureCoordinate.x - love_postion.x)*5.0, 1.0 - (textureCoordinate.y - love_postion.y)*5.0));
        if (colorlove.w > 0.5){
            FragColor = vec4(colorlove.z, colorlove.y, colorlove.x, colorlove.w);
        }
    }

}
