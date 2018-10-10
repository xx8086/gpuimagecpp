#version 300 es
precision highp float;

layout(location = 0) out vec4 o_FragColor;
in vec2 texture_coord;
uniform float screen_width;
uniform float screen_hight;
uniform float ratio;
uniform float face_head_height;
uniform float face_head_width;
uniform vec2 face_head_bottom;
uniform vec2 face_head_left;
uniform vec2 face_head_right;
uniform vec2 face_head_top;
uniform vec2 face_head_middle;
uniform sampler2D imput_image_texture;

float getdistance(vec2 pos_src, vec2 pos_dist){
    float quadratic_sum = pow((pos_src.x - pos_dist.x), 2.) + pow((pos_src.y - pos_dist.y), 2.);
    return sqrt(quadratic_sum);
}

bool move_head(){
    if(texture_coord.y > face_head_top.y){
        float dis = getdistance(texture_coord, face_head_middle);
        if(dis < face_head_height){
            float roat = -0.1f * ratio * (1.0 - dis/face_head_height);
            mat2 matroat = mat2(cos(roat), -sin(roat), sin(roat), cos(roat));
            vec2 v2 = matroat * (texture_coord - face_head_top) + face_head_top;
            o_FragColor = texture(imput_image_texture, v2);
        }
    }
    
    return false;
}


///////////
/*
uniform highp float radius;
uniform highp float aspectRatio;
uniform float leftContourPoints[MAX_CONTOUR_POINT_COUNT*2];
uniform float rightContourPoints[MAX_CONTOUR_POINT_COUNT*2];
uniform float deltaArray[MAX_CONTOUR_POINT_COUNT];
uniform int arraySize;

highp vec2 warpPositionToUse(vec2 currentPoint, vec2 contourPointA,  vec2 contourPointB, float radius, float delta, float aspectRatio){
    vec2 positionToUse = currentPoint;
    vec2 currentPointToUse = vec2(currentPoint.x, currentPoint.y * aspectRatio + 0.5 - 0.5 * aspectRatio);
    vec2 contourPointAToUse = vec2(contourPointA.x, contourPointA.y * aspectRatio + 0.5 - 0.5 * aspectRatio);
    
    float r = distance(currentPointToUse, contourPointAToUse);
    if(r < radius)
    {
        vec2 dir = normalize(contourPointB - contourPointA);
        float dist = radius * radius - r * r;
        float alpha = dist / (dist + (r-delta) * (r-delta));
        alpha = alpha * alpha;
        
        positionToUse = positionToUse - alpha * delta * dir;
        
    }
    
    return positionToUse;
    
}


void move_eyes(){
    vec2 positionToUse = textureCoordinate;
    
    for(int i = 0; i < arraySize; i++){
        positionToUse = warpPositionToUse(positionToUse, vec2(leftContourPoints[i * 2], leftContourPoints[i * 2 + 1]), vec2(rightContourPoints[i * 2], rightContourPoints[i * 2 + 1]), radius, deltaArray[i], aspectRatio);
        positionToUse = warpPositionToUse(positionToUse, vec2(rightContourPoints[i * 2], rightContourPoints[i * 2 + 1]), vec2(leftContourPoints[i * 2], leftContourPoints[i * 2 + 1]), radius, deltaArray[i], aspectRatio);
    }
    
    gl_FragColor = texture2D(inputImageTexture, positionToUse);
}
*/

void main(){
    o_FragColor = texture(imput_image_texture, texture_coord);
    move_head();
}

