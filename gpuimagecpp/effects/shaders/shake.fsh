precision mediump float;
varying highp vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
uniform float ratio;

void main(void){
    vec2 center = vec2(0.5, 0.5);
    vec2 distance = center - textureCoordinate;
    float x = center.x + center.x*(-distance.x/center.x) * ratio;
    float y = center.y + center.y*(-distance.y/center.y) * ratio;
    vec2 tex = vec2(x,y);
    vec4 sample_tex = texture2D(inputImageTexture, tex);
    gl_FragColor = sample_tex;
    /*
    if((textureCoordinate.x < -0.9 || textureCoordinate.x > 0.9) ||
        (textureCoordinate.y < 0.1 || textureCoordinate.y > 0.9)){
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }*/
}
