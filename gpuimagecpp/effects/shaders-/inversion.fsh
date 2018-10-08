
varying highp vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
void main(){
    lowp vec4 textureColor = texture2D(inputImageTexture, vec2(textureCoordinate.x, 1.0 - textureCoordinate.y));
    gl_FragColor = textureColor;
}
