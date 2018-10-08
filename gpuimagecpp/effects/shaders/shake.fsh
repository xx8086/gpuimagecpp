#version 300 es
precision mediump float;
in vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
uniform float ratio;
layout(location = 0) out vec4 FragColor;
void main(void){
    vec2 center = vec2(0.5, 0.5);
    vec2 distance = center - textureCoordinate;
    float x = center.x + center.x*(-distance.x/center.x) * ratio;
    float y = center.y + center.y*(-distance.y/center.y) * ratio;
    vec2 tex = vec2(x,y);
    vec4 sample_tex = texture(inputImageTexture, tex);
    FragColor = vec4(sample_tex.z, sample_tex.y, sample_tex.x, sample_tex.w);
    //FragColor = sample_tex;
}
