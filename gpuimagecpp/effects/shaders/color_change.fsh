
precision highp float;
precision highp sampler2D;
varying mediump vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
uniform float red; //0- 1
uniform float white;//0 - 1
uniform float pink; // 0 - 1
const vec3 lumCoeff = vec3(0.2125, 0.7154, 0.0721);
const vec3 rggCoeff = vec3(0.299, 0.587, 0.114);

#define BlendSoftLightf(base, blend) ((blend < 0.5) ? (2.0 * base * blend + base * base * (1.0 - 2.0 * blend)) : (sqrt(base) * (2.0 * blend - 1.0) + 2.0 * base * (1.0 - blend)))
#define BlendScreenf(base, blend) (1.0 - ((1.0 - base) * (1.0 - blend)))
#define Blend(base, blend, funcf) vec3(funcf(base.r, blend.r), funcf(base.g, blend.g), funcf(base.b, blend.b))
#define BlendSoftLight(base, blend) Blend(base, blend, BlendSoftLightf)
#define BlendScreen(base, blend) Blend(base, blend, BlendScreenf)

vec3 SkinWhitening(vec3 inputColor, float fWhite)
{
  vec3 outputColor = inputColor.rgb;
  vec3 minus = vec3(1.0) - outputColor;
  outputColor = vec3(1.0) - minus * minus;
  float fAlpha = dot(rggCoeff, inputColor.rgb);
  outputColor = mix(inputColor.rgb, outputColor, fWhite * fAlpha);
  return outputColor;
}

vec3 SkinPinking(vec3 inputColor, float fPink)
{
  vec3 pinkColor = vec3(0.705, 0.784, 0.882);
  vec3 outputColor = inputColor.rgb;
  outputColor = BlendSoftLight(outputColor, pinkColor);
  float fAlpha = dot(rggCoeff, inputColor.rgb);
  outputColor = mix(inputColor.rgb, outputColor, fPink * fAlpha);
  return outputColor;
}

vec3 SkinRedden(vec3 inputColor, float fRed)
{
  vec3 outputColor;
  outputColor = BlendScreen(inputColor, inputColor.rgb);
  outputColor = mix(inputColor, outputColor, 0.2 * fRed);
  float gray = dot(outputColor, rggCoeff);
  outputColor = mix(vec3(gray), outputColor, 1.0 + fRed);
  inputColor = outputColor;
  vec3 clearColor = mix(inputColor.rgg, inputColor, 0.5);
  float fAlpha = dot(clearColor, rggCoeff);
  outputColor = BlendSoftLight(clearColor, vec3(1.0));
  outputColor = mix(clearColor, outputColor, fAlpha);
  outputColor = mix(inputColor.rgb, outputColor, fRed * fAlpha);
  return outputColor;
}

void main(void)
{
  
  vec4 vImageColor = texture2D(inputImageTexture, textureCoordinate).rgba;
  vec4 vSoftColor = vImageColor;
  vSoftColor.a = 1.0;
  
  if(white != 0.0)
  {
    vSoftColor.rgb = SkinWhitening(vSoftColor.rgb, white);
    vSoftColor.rgb = clamp(vSoftColor.rgb, 0.0, 1.0);
  }
  
  if (red != 0.0)
  {
    vSoftColor.rgb = SkinRedden(vSoftColor.rgb, red);
    vSoftColor.rgb = clamp(vSoftColor.rgb, 0.0, 1.0);
  }
  
  if (pink != 0.0)
  {
    vSoftColor.rgb = SkinPinking(vSoftColor.rgb, pink);
    vSoftColor.rgb = clamp(vSoftColor.rgb, 0.0, 1.0);
  }
  
  gl_FragColor = vSoftColor;
}
