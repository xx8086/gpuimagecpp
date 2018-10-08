
precision mediump float;
precision mediump int;
varying highp vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
uniform int window_counts;

vec2 mapuv(vec2 uv,float range){
    float rate = (1.0 - 2.0 * range);
    vec2 center = vec2(0.5, 0.5);
    vec2 distance = center - textureCoordinate;
    float x = uv.x + center.x*(-distance.x/center.x) * rate;
    float y = uv.y + center.y*(-distance.y/center.y) * rate;
    return vec2(x, y);
}
/*
 
 0---------->u
 |
 |
 |
 V v
 */
vec4 four(){
    vec2 tex = vec2(textureCoordinate.x * 2.0, textureCoordinate.y * 2.0);
    if(tex.x > 1.0){
        tex.x = tex.x - 1.0;
    }
    if(tex.y > 1.0){
        tex.y = tex.y - 1.0;
    }
    return texture2D(inputImageTexture, tex);
}

vec4 nine(){
    vec2 tex = vec2(textureCoordinate.x * 3.0, textureCoordinate.y * 3.0);
    if(tex.x > 1.0 && 2.0 >= tex.x){
        tex.x = tex.x - 1.0;
    }
    else if(tex.x > 2.0){
        tex.x = tex.x - 2.0;
    }
    
    if(tex.y > 1.0 && 2.0 >= tex.y){
        tex.y = tex.y - 1.0;
    }
    else if(tex.y > 2.0){
        tex.y = tex.y - 2.0;
    }
    return texture2D(inputImageTexture, tex);
}

void main(void){
    //vec4 sample_tex;
    if(4 == window_counts){
        gl_FragColor = four();
    }
    else if(9 == window_counts){
        gl_FragColor = nine();
    }
    else{
        gl_FragColor = texture2D(inputImageTexture, textureCoordinate);
    }
    //gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
