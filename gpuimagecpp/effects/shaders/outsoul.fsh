
precision mediump float;
varying highp vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
uniform float ratio;
//uniform float width;
//uniform float height;
uniform float alpha;

void main(void)
{
    vec2 center = vec2(0.5, 0.5);
    vec2 distance = center - textureCoordinate;
    float x = center.x + center.x*(-distance.x/center.x) * ratio;
    float y = center.y + center.y*(-distance.y/center.y) * ratio;
    vec2 tex = vec2(x,y);
    
    lowp vec4 sample_tex = texture2D(inputImageTexture, textureCoordinate);
    lowp vec4 sample_offset = texture2D(inputImageTexture, tex);
    gl_FragColor = vec4(mix(sample_tex, sample_offset, alpha));
    //gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
}

