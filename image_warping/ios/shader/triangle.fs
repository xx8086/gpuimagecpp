#version 300 es
precision mediump float;

layout(location = 0) out vec4 o_FragColor;
in vec3 our_color;
in vec2 texture_coord;
uniform float screen_width;
uniform float screen_hight;
uniform float ratio;
uniform sampler2D imput_image_texture;
uniform sampler2D tongue_image_texture;

uniform vec2 mouth_left;
uniform vec2 mouth_right;
uniform vec2 mouth_top;
uniform vec2 mouth_bottom;
uniform float mouth_cos;
uniform float mouth_sin;
uniform float mouth_tan;
uniform float mouth_k;

uniform vec2 left_eye_left;
uniform vec2 left_eye_right;
uniform vec2 left_eye_top;
uniform vec2 left_eye_bottom;
uniform float left_eye_ellipse_a;
uniform float left_eye_ellipse_b;

uniform vec2 right_eye_left;
uniform vec2 right_eye_right;
uniform vec2 right_eye_top;
uniform vec2 right_eye_bottom;
uniform float right_eye_ellipse_a;
uniform float right_eye_ellipse_b;

uniform vec2 right_eyebrow_left;
uniform vec2 right_eyebrow_right;
uniform float right_eyebrow_top;
uniform float right_eyebrow_bottom;
uniform float right_eyebrow_height;
uniform float right_eyebrow_middle;

uniform vec2 left_eyebrow_left;
uniform vec2 left_eyebrow_right;
uniform float left_eyebrow_top;
uniform float left_eyebrow_bottom;
uniform float left_eyebrow_height;
uniform float left_eyebrow_middle;

float right_eyebrow_up(float right_eyebrow_x_pos){
    return (right_eyebrow_x_pos - right_eyebrow_left.x)/(right_eyebrow_right.x - right_eyebrow_left.x);
}

float getdistance(vec2 pos_src, vec2 pos_dist){
    float quadratic_sum = pow((pos_src.x - pos_dist.x), 2.) + pow((pos_src.y - pos_dist.y), 2.);
    return sqrt(quadratic_sum);
}

void zoom(){
    if (getdistance(vec2(0.40, 0.39), texture_coord) > 0.1){
        o_FragColor = texture(imput_image_texture, texture_coord);
    }
    else {
        o_FragColor = texture(imput_image_texture, texture_coord / 2.0 + 0.2);
    }
}
bool greater_than(float a, float b){
    return a - b > 0.001;
}

bool equal_float(float a, float b){
    if (a > b - 0.001 && a < b + 0.001){
        return true;
    }
    return false;
}

float pos_on_line(vec2 p1, vec2 p2){
    return p1.x * p2.y - p2.x * p1.y;
}

float line_y(float k, float x, float x0, float y0){
    return (y0 + k * (x - x0));
}

float range(float x, float left, float right, float u){
    if (x <= left || x >= right){
        return 0.0f;
    }
    float k = 3.1415926f / (right - left);
    float b = 1.5707963 - k * right;
    return 2.0*cos(b + k * x) * u;
}

bool mouth(){
    if(texture_coord.x > mouth_left.x && texture_coord.x < mouth_right.x &&
       texture_coord.y > mouth_top.y && texture_coord.y < mouth_bottom.y){
        float mouth_dis = range(texture_coord.x, mouth_left.x, mouth_right.x, 0.01) * ratio;
        float mouth_top_dis = mouth_dis * 0.5;
        float mouth_y = line_y(mouth_k, texture_coord.x, mouth_left.x, mouth_left.y);
        float post_point = pos_on_line(texture_coord - mouth_left, mouth_right - mouth_left);//
        if (post_point >= 0.0f){
            float dis_top = (mouth_y - texture_coord.y) * mouth_cos;
            if (mouth_top_dis >= dis_top){
                o_FragColor = vec4(0.341176, 0.168627, 0.180392, 1.0);
            }
            else{
                mouth_top_dis = mouth_top_dis * (1.0 - (mouth_y - texture_coord.y)/(mouth_y - mouth_top.y));
                o_FragColor = texture(imput_image_texture,
                                      vec2(texture_coord.x + mouth_top_dis * mouth_sin, texture_coord.y + mouth_top_dis * mouth_cos));
                                      //vec2(texture_coord.x , texture_coord.y + mouth_top_dis));
                //o_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
            }
            
        }else if (post_point < 0.0f){
            float dis_bottom = (texture_coord.y - mouth_y) * mouth_cos;
            if (dis_bottom > mouth_dis){
                mouth_dis = mouth_dis * (1.0 - (texture_coord.y - mouth_y)/(mouth_bottom.y - mouth_y));
                o_FragColor = texture(imput_image_texture,
                                      vec2(texture_coord.x - mouth_dis * mouth_sin, texture_coord.y - mouth_dis * mouth_cos));
                                      //vec2(texture_coord.x, texture_coord.y - mouth_dis));
                //o_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
            }else{
                o_FragColor = vec4(0.341176, 0.168627, 0.180392, 1.0);
            }
        }
        return true;
    }
    
    return false;
}

bool left_eye(){
    if (texture_coord.x > left_eye_left.x && left_eye_right.x > texture_coord.x &&
        texture_coord.y > left_eye_top.y && left_eye_bottom.y > texture_coord.y){
        float ellipse_x = texture_coord.x - left_eye_left.x - left_eye_ellipse_a;
        float ellipse_y = left_eye_ellipse_b * sqrt((1.0f - (ellipse_x * ellipse_x) / (left_eye_ellipse_a * left_eye_ellipse_a)));
        float left_eye_point_height = left_eye_bottom.y - texture_coord.y;
        if (ellipse_y > left_eye_point_height){//椭圆内
            /*
            float offset = 1.0 - left_eye_point_height/ellipse_y ;
            if(1.0 - left_eye_point_height/ellipse_y  < ratio){
                o_FragColor = texture(imput_image_texture,
                                   vec2(texture_coord.x, texture_coord.y - left_eye_point_height * left_eye_ellipse_q / left_eye_ellipse_b));
            }
             */
            float offset = ellipse_y - left_eye_point_height + ellipse_y*0.5;
            o_FragColor = texture(imput_image_texture,
                                  vec2(texture_coord.x, texture_coord.y - offset * ratio * 0.5));
            return true;
        }
    }
    return false;
}

bool right_eye(){
    if (texture_coord.x > right_eye_left.x && texture_coord.x < right_eye_right.x &&
        texture_coord.y > right_eye_top.y && texture_coord.y < right_eye_bottom.y){
        float ellipse_x = texture_coord.x - right_eye_left.x - right_eye_ellipse_a;
        float ellipse_y = right_eye_ellipse_b * sqrt((1.0f - (ellipse_x * ellipse_x) / (right_eye_ellipse_a * right_eye_ellipse_a)));
        float right_eye_point_height = right_eye_bottom.y - texture_coord.y;
        if (ellipse_y >= right_eye_point_height){//椭圆内
            float offset = ellipse_y - right_eye_point_height + ellipse_y*0.5;
            o_FragColor = texture(imput_image_texture,
                                  vec2(texture_coord.x, texture_coord.y - offset * ratio * 0.7));
            return true;
        }
    }
    return false;
}

bool right_eyebrow(){
    if(texture_coord.x > right_eyebrow_left.x && texture_coord.x <= right_eyebrow_right.x &&
       texture_coord.y > right_eyebrow_top && texture_coord.y < right_eyebrow_bottom ){
        float incrementingi = (texture_coord.x - right_eyebrow_right.x) / (right_eyebrow_left.x - right_eyebrow_right.x);
        incrementingi = texture_coord.y + right_eyebrow_height * ratio * incrementingi;
        if (incrementingi >= right_eyebrow_bottom){
            incrementingi = right_eyebrow_bottom;
        }
        o_FragColor = texture(imput_image_texture,
                              vec2(texture_coord.x, incrementingi));
        return true;
    }
    return false;
}

bool left_eyebrow(){
    if (texture_coord.x > left_eyebrow_left.x && texture_coord.x < left_eyebrow_right.x &&
        texture_coord.y > left_eyebrow_top && texture_coord.y < left_eyebrow_bottom){
            float incrementingi = (texture_coord.x - left_eyebrow_left.x) / (left_eyebrow_right.x - left_eyebrow_left.x);
            incrementingi = texture_coord.y + left_eyebrow_height * ratio * incrementingi;
            if (incrementingi >= left_eyebrow_bottom){
                incrementingi = left_eyebrow_bottom;
            }
            o_FragColor = texture(imput_image_texture,
                                  vec2(texture_coord.x, incrementingi));
        return true;
        }
        return false;
}

void main(){
    o_FragColor = texture(imput_image_texture, texture_coord);
    mouth() && /*left_eye() && right_eye() && */ left_eyebrow() && right_eyebrow() && left_eyebrow();
}

