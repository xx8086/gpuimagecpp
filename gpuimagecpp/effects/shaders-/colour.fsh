precision mediump float;
varying highp vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
uniform int colour;
uniform float transparency;
void main(){
    vec3 colors[10];
    colors[9] = vec3(255, 255, 255);
    colors[0] = vec3(212, 83, 101);
    colors[1] = vec3(165, 83, 212);
    colors[2] = vec3(55,  177, 195);
    colors[3] = vec3(227, 169, 86);
    colors[4] = vec3(196, 127, 28);
    colors[5] = vec3(103, 227, 232);
    colors[6] = vec3(255, 145, 228);
    colors[7] = vec3(173, 144, 254);
    colors[8] = vec3(115, 225,109);
    

    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
    vec3 color = mix(textureColor.rgb, colors[colour]/255.0, transparency);
    gl_FragColor = vec4(color, textureColor.w);
}
