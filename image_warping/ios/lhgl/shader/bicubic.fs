#version 300 es
precision highp float;

layout(location = 0) out vec4 o_FragColor;
in vec2 texture_coord;
uniform sampler2D imput_image_texture;

/*
uniform float uUnit;//传入原图的宽
uniform float vUnit;//传入原图的高

float BiCubicPoly1(float x, float a){
    x = abs(x);
    float res = (a+float(2))*x*x*x - (a+float(3))*x*x + float(1);
    return res;
}

float BiCubicPoly2(float x, float a){
    x = abs(x);
    float res = a*x*x*x - float(5)*a*x*x + float(8)*a*x - float(4)*a;
    return res;
}
void main(){
    vec2 basic;
    vec2 det;
    basic = texture_coord*vec2(uUnit, vUnit) - vec2(0.25,25);
    det = fract(basic);
    o_FragColor = vec4(0.0,0.0,0.0,0.0)
    +BiCubicPoly2(det.x-float(-1), float(-0.5))*BiCubicPoly2(det.y-float(-1), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(-1), float(-1)))/vec2(uUnit, vUnit))
    +BiCubicPoly2(det.x-float(-1), float(-0.5))*BiCubicPoly1(det.y-float(0), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(-1), float(0)))/vec2(uUnit, vUnit))
    +BiCubicPoly2(det.x-float(-1), float(-0.5))*BiCubicPoly1(det.y-float(1), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(-1), float(1)))/vec2(uUnit, vUnit))
    +BiCubicPoly2(det.x-float(-1), float(-0.5))*BiCubicPoly2(det.y-float(2), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(-1), float(2)))/vec2(uUnit, vUnit))
    +BiCubicPoly1(det.x-float(0), float(-0.5))*BiCubicPoly2(det.y-float(-1), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(0), float(-1)))/vec2(uUnit, vUnit))
    +BiCubicPoly1(det.x-float(0), float(-0.5))*BiCubicPoly1(det.y-float(0), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(0), float(0)))/vec2(uUnit, vUnit))
    +BiCubicPoly1(det.x-float(0), float(-0.5))*BiCubicPoly1(det.y-float(1), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(0), float(1)))/vec2(uUnit, vUnit))
    +BiCubicPoly1(det.x-float(0), float(-0.5))*BiCubicPoly2(det.y-float(2), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(0), float(2)))/vec2(uUnit, vUnit))
    +BiCubicPoly1(det.x-float(1), float(-0.5))*BiCubicPoly2(det.y-float(-1), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(1), float(-1)))/vec2(uUnit, vUnit))
    +BiCubicPoly1(det.x-float(1), float(-0.5))*BiCubicPoly1(det.y-float(0), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(1), float(0)))/vec2(uUnit, vUnit))
    +BiCubicPoly1(det.x-float(1), float(-0.5))*BiCubicPoly1(det.y-float(1), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(1), float(1)))/vec2(uUnit, vUnit))
    +BiCubicPoly1(det.x-float(1), float(-0.5))*BiCubicPoly2(det.y-float(2), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(1), float(2)))/vec2(uUnit, vUnit))
    +BiCubicPoly2(det.x-float(2), float(-0.5))*BiCubicPoly2(det.y-float(-1), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(2), float(-1)))/vec2(uUnit, vUnit))
    +BiCubicPoly2(det.x-float(2), float(-0.5))*BiCubicPoly1(det.y-float(0), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(2), float(0)))/vec2(uUnit, vUnit))
    +BiCubicPoly2(det.x-float(2), float(-0.5))*BiCubicPoly1(det.y-float(1), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(2), float(1)))/vec2(uUnit, vUnit))
    +BiCubicPoly2(det.x-float(2), float(-0.5))*BiCubicPoly2(det.y-float(2), float(-0.5))*texture(imput_image_texture, texture_coord + ( - det + vec2(float(2), float(2)))/vec2(uUnit, vUnit))
    ;
}
 */

uniform float ratio;
//uniform float faceStrong;
//uniform float eyeStrong;
uniform vec2 imgSize;
uniform vec2 leftEye;
uniform vec2 rightEye;
uniform vec2 mouthTop;
uniform vec2 mouthBottom;
uniform vec2 leftEdge2;
uniform vec2 rightEdge2;
uniform vec2 leftEdge3;
uniform vec2 rightEdge3;
uniform vec2 leftEdge4;
uniform vec2 rightEdge4;
uniform vec2 chin;

void main (){
    float faceStrong = ratio;
    float eyeStrong = ratio;
    vec2 textureCoord_new_1;
    float radius_2;
    vec2 targetRight_3;
    vec2 targetLeft_4;
    vec2 tmpvar_5;
    tmpvar_5 = (texture_coord * imgSize);
    vec2 tmpvar_6;
    float tmpvar_7;
    tmpvar_7 = (leftEye.x * imgSize.x);
    tmpvar_6.x = tmpvar_7;
    float tmpvar_8;
    tmpvar_8 = (leftEye.y * imgSize.y);
    tmpvar_6.y = tmpvar_8;
    vec2 tmpvar_9;
    float tmpvar_10;
    tmpvar_10 = (rightEye.x * imgSize.x);
    tmpvar_9.x = tmpvar_10;
    float tmpvar_11;
    tmpvar_11 = (rightEye.y * imgSize.y);
    tmpvar_9.y = tmpvar_11;
    float tmpvar_12;
    vec2 tmpvar_13;
    tmpvar_13 = (tmpvar_6 - tmpvar_9);
    tmpvar_12 = sqrt(dot (tmpvar_13, tmpvar_13));
    vec2 tmpvar_14;
    tmpvar_14 = (mouthBottom * imgSize);
    vec2 tmpvar_15;
    tmpvar_15 = (mouthTop * imgSize);
    radius_2 = (tmpvar_12 * 1.5);
    vec2 tmpvar_16;
    tmpvar_16 = (leftEdge3 * imgSize);
    targetLeft_4 = (tmpvar_14 + ((tmpvar_16 - tmpvar_14) * 0.8));
    vec2 tmpvar_17;
    vec2 tmpvar_18;
    tmpvar_18 = (targetLeft_4 - tmpvar_16);
    float tmpvar_19;
    tmpvar_19 = sqrt(dot (tmpvar_18, tmpvar_18));
    vec2 tmpvar_20;
    tmpvar_20 = (tmpvar_5 - tmpvar_16);
    float tmpvar_21;
    tmpvar_21 = clamp ((1.0 - (
                               sqrt(dot (tmpvar_20, tmpvar_20))
                               / radius_2)), 0.0, 1.0);
    tmpvar_17 = ((tmpvar_18 * (
                               (faceStrong * min (tmpvar_19, radius_2))
                               / tmpvar_19)) * (tmpvar_21 * tmpvar_21));
    vec2 tmpvar_22;
    tmpvar_22 = (rightEdge3 * imgSize);
    targetRight_3 = (tmpvar_14 + ((tmpvar_22 - tmpvar_14) * 0.8));
    vec2 tmpvar_23;
    vec2 tmpvar_24;
    tmpvar_24 = (targetRight_3 - tmpvar_22);
    float tmpvar_25;
    tmpvar_25 = sqrt(dot (tmpvar_24, tmpvar_24));
    vec2 tmpvar_26;
    tmpvar_26 = (tmpvar_5 - tmpvar_22);
    float tmpvar_27;
    tmpvar_27 = clamp ((1.0 - (
                               sqrt(dot (tmpvar_26, tmpvar_26))
                               / radius_2)), 0.0, 1.0);
    tmpvar_23 = ((tmpvar_24 * (
                               (faceStrong * min (tmpvar_25, radius_2))
                               / tmpvar_25)) * (tmpvar_27 * tmpvar_27));
    vec2 tmpvar_28;
    tmpvar_28 = (leftEdge2 * imgSize);
    targetLeft_4 = (tmpvar_14 + ((tmpvar_28 - tmpvar_14) * 0.93));
    vec2 tmpvar_29;
    vec2 tmpvar_30;
    tmpvar_30 = (targetLeft_4 - tmpvar_28);
    float tmpvar_31;
    tmpvar_31 = sqrt(dot (tmpvar_30, tmpvar_30));
    vec2 tmpvar_32;
    tmpvar_32 = (tmpvar_5 - tmpvar_28);
    float tmpvar_33;
    tmpvar_33 = clamp ((1.0 - (
                               sqrt(dot (tmpvar_32, tmpvar_32))
                               / radius_2)), 0.0, 1.0);
    tmpvar_29 = ((tmpvar_30 * (
                               (faceStrong * min (tmpvar_31, radius_2))
                               / tmpvar_31)) * (tmpvar_33 * tmpvar_33));
    vec2 tmpvar_34;
    tmpvar_34 = (rightEdge2 * imgSize);
    targetRight_3 = (tmpvar_14 + ((tmpvar_34 - tmpvar_14) * 0.93));
    vec2 tmpvar_35;
    vec2 tmpvar_36;
    tmpvar_36 = (targetRight_3 - tmpvar_34);
    float tmpvar_37;
    tmpvar_37 = sqrt(dot (tmpvar_36, tmpvar_36));
    vec2 tmpvar_38;
    tmpvar_38 = (tmpvar_5 - tmpvar_34);
    float tmpvar_39;
    tmpvar_39 = clamp ((1.0 - (
                               sqrt(dot (tmpvar_38, tmpvar_38))
                               / radius_2)), 0.0, 1.0);
    tmpvar_35 = ((tmpvar_36 * (
                               (faceStrong * min (tmpvar_37, radius_2))
                               / tmpvar_37)) * (tmpvar_39 * tmpvar_39));
    vec2 tmpvar_40;
    tmpvar_40 = (chin * imgSize);
    vec2 tmpvar_41;
    tmpvar_41 = ((tmpvar_14 + (
                               (tmpvar_40 - tmpvar_14)
                               * 1.1)) - tmpvar_40);
    float tmpvar_42;
    tmpvar_42 = sqrt(dot (tmpvar_41, tmpvar_41));
    vec2 tmpvar_43;
    tmpvar_43 = (tmpvar_5 - tmpvar_40);
    float tmpvar_44;
    tmpvar_44 = clamp ((1.0 - (
                               sqrt(dot (tmpvar_43, tmpvar_43))
                               / tmpvar_12)), 0.0, 1.0);
    radius_2 = (tmpvar_12 * 1.3);
    vec2 tmpvar_45;
    tmpvar_45 = (leftEdge4 * imgSize);
    targetLeft_4 = (tmpvar_14 + ((tmpvar_45 - tmpvar_14) * 0.9));
    vec2 tmpvar_46;
    vec2 tmpvar_47;
    tmpvar_47 = (targetLeft_4 - tmpvar_45);
    float tmpvar_48;
    tmpvar_48 = sqrt(dot (tmpvar_47, tmpvar_47));
    vec2 tmpvar_49;
    tmpvar_49 = (tmpvar_5 - tmpvar_45);
    float tmpvar_50;
    tmpvar_50 = clamp ((1.0 - (
                               sqrt(dot (tmpvar_49, tmpvar_49))
                               / radius_2)), 0.0, 1.0);
    tmpvar_46 = ((tmpvar_47 * (
                               (faceStrong * min (tmpvar_48, radius_2))
                               / tmpvar_48)) * (tmpvar_50 * tmpvar_50));
    vec2 tmpvar_51;
    tmpvar_51 = (rightEdge4 * imgSize);
    targetRight_3 = (tmpvar_14 + ((tmpvar_51 - tmpvar_14) * 0.9));
    vec2 tmpvar_52;
    vec2 tmpvar_53;
    tmpvar_53 = (targetRight_3 - tmpvar_51);
    float tmpvar_54;
    tmpvar_54 = sqrt(dot (tmpvar_53, tmpvar_53));
    vec2 tmpvar_55;
    tmpvar_55 = (tmpvar_5 - tmpvar_51);
    float tmpvar_56;
    tmpvar_56 = clamp ((1.0 - (
                               sqrt(dot (tmpvar_55, tmpvar_55))
                               / radius_2)), 0.0, 1.0);
    tmpvar_52 = ((tmpvar_53 * (
                               (faceStrong * min (tmpvar_54, radius_2))
                               / tmpvar_54)) * (tmpvar_56 * tmpvar_56));
    vec2 tmpvar_57;
    tmpvar_57.x = tmpvar_10;
    tmpvar_57.y = tmpvar_11;
    targetLeft_4 = (tmpvar_15 + ((tmpvar_57 - tmpvar_15) * 2.4));
    vec2 tmpvar_58;
    tmpvar_58.x = tmpvar_7;
    tmpvar_58.y = tmpvar_8;
    targetRight_3 = (tmpvar_15 + ((tmpvar_58 - tmpvar_15) * 2.4));
    radius_2 = (tmpvar_12 * 0.23);
    vec2 tmpvar_59;
    tmpvar_59.x = tmpvar_7;
    tmpvar_59.y = tmpvar_8;
    vec2 tmpvar_60;
    tmpvar_60 = (tmpvar_5 - tmpvar_59);
    float tmpvar_61;
    tmpvar_61 = clamp ((sqrt(
                             dot (tmpvar_60, tmpvar_60)
                             ) / radius_2), 0.0, 1.0);
    vec2 tmpvar_62;
    tmpvar_62.x = tmpvar_10;
    tmpvar_62.y = tmpvar_11;
    vec2 tmpvar_63;
    tmpvar_63 = (tmpvar_5 - tmpvar_62);
    float tmpvar_64;
    tmpvar_64 = clamp ((sqrt(
                             dot (tmpvar_63, tmpvar_63)
                             ) / radius_2), 0.0, 1.0);
    textureCoord_new_1 = ((tmpvar_5 - tmpvar_17) - tmpvar_23);
    textureCoord_new_1 = (textureCoord_new_1 - ((tmpvar_41 *
                                                 ((faceStrong * min (tmpvar_42, tmpvar_12)) / tmpvar_42)
                                                 ) * (tmpvar_44 * tmpvar_44)));
    textureCoord_new_1 = (textureCoord_new_1 - tmpvar_29);
    textureCoord_new_1 = (textureCoord_new_1 - tmpvar_35);
    textureCoord_new_1 = (textureCoord_new_1 - tmpvar_46);
    textureCoord_new_1 = (textureCoord_new_1 - tmpvar_52);
    textureCoord_new_1 = (tmpvar_59 + ((textureCoord_new_1 - tmpvar_59) * (
                                                                           ((eyeStrong * tmpvar_61) * (tmpvar_61 - 1.0))
                                                                           + 1.0)));
    textureCoord_new_1 = (tmpvar_62 + ((textureCoord_new_1 - tmpvar_62) * (
                                                                           ((eyeStrong * tmpvar_64) * (tmpvar_64 - 1.0))
                                                                           + 1.0)));
    vec4 tmpvar_65 = texture(imput_image_texture, (textureCoord_new_1 / imgSize));
    o_FragColor = tmpvar_65;
    
}
