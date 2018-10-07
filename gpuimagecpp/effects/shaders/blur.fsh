
precision mediump float;
varying highp vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
uniform float ratio;
uniform float range;//[0.0, 0.5]

vec4 gauss_blur(){
    float delta = ratio; //1.0/150.0;
    vec4 color = vec4(0.0);
    float factor[9];
    factor[0] = 0.0947416; factor[1] = 0.118318; factor[2] = 0.0947416;
    factor[3] = 0.118318; factor[4] = 0.147761; factor[5] = 0.118318;
    factor[6] = 0.0947416; factor[7] = 0.118318; factor[8] = 0.0947416;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            float x = max(0.0, textureCoordinate.x + float(i) * delta);
            float y = max(0.0, textureCoordinate.y + float(i) * delta);
            color += texture2D(inputImageTexture, vec2(x, y)) * factor[(i+1)*3+(j+1)];
        }
    }
    return vec4(vec3(color), 1.0);
}

vec4 blur(){
    vec4 sample0,sample1,sample2,sample3;
    sample0 = texture2D(inputImageTexture,vec2(textureCoordinate.x-ratio,textureCoordinate.y-ratio));
    sample1 = texture2D(inputImageTexture,vec2(textureCoordinate.x+ratio,textureCoordinate.y-ratio));
    sample2 = texture2D(inputImageTexture,vec2(textureCoordinate.x+ratio,textureCoordinate.y+ratio));
    sample3 = texture2D(inputImageTexture,vec2(textureCoordinate.x-ratio,textureCoordinate.y+ratio));

    vec4 color = (sample0 + sample1 + sample2 + sample3) / 4.0;
    return color ;//* texture2D(inputImageTexture, textureCoordinate);
}

void main(){
    if(textureCoordinate.x > range && textureCoordinate.x < 1.0 - range){
        gl_FragColor = texture2D(inputImageTexture, textureCoordinate);
    }
    else{
        gl_FragColor = blur();
    }
    
}

