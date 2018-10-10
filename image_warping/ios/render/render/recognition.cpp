//
//  recognition.cpp
//  render
//
//  Created by liu on 2018/7/25.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "recognition.hpp"
#include "pipeline.hpp"
#include "math.hpp"
#include <assert.h>
#include <fstream>

CRecognition::CRecognition(){
}

CRecognition::~CRecognition(){
    release();
}

void CRecognition::init(){
    glViewport (0, 0, _width, _height);
    glEnable(GL_DEPTH_TEST);
}

void CRecognition::update(){
    if (_timer.count_time()){
        if (_ratio <= 0.0 || _ratio > 1.0){//0.45
            _step = -_step;
        }
        _ratio += _step;
        _timer.set_count_time(10);
        //_ratio = 0.0f;
    }
    
    _pipeline.set_camera(Vec3f(0.0f, 0.0f, -10.0f), Vec3f(0.0f, 0.0f, 1.0f), Vec3f(0.0f, 1.0f, 0.0f));
    _pipeline.set_perspective_proj(_camera->get_proj_info());
    _pipeline.rotate(0.0f, 0.0f, 0.0f);
    _pipeline.scale(4.0);
}
void CRecognition::keyboard(bool bchar, unsigned int uchar, unsigned int utype){
    ;
}
void CRecognition::touch_event(){
    ;
}
void CRecognition::release(){
    un_bind_frame();
}

void CRecognition::resize(unsigned int w, unsigned int h){
    _width = w;
    _height = h;
}

void CRecognition::draw_head(){
    _face_shader_move_head.use();
    _face_shader_move_head.setmat4(_face_shader_move_head.getuniformlocation("pvw"), _pipeline.get_pvw_trans(), GL_TRUE);
    _face_shader_move_head.setfloat(_face_shader_move_head.getuniformlocation("ratio"), _ratio);
    glBindVertexArray(_quad_vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture_colorbuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    _face_shader_move_head.unuse();
    glBindVertexArray(0);
}

void CRecognition::draw_warp(){
    _face_shader_warp.use();
    _face_shader_warp.setmat4(_face_shader_warp.getuniformlocation("pvw"), _pipeline.get_pvw_trans(), GL_TRUE);
    _face_shader_warp.setfloat(_face_shader_warp.getuniformlocation("ratio"), _ratio);
    glBindVertexArray(_quad_vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture_colorbuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    _face_shader_warp.unuse();
    glBindVertexArray(0);
}

void CRecognition::draw_face(){
    _pipeline.world_pos(0.0f, 0.0f, 0.0f);
    _face_shader.use();
    _face_shader.setmat4(_face_shader.getuniformlocation("pvw"), _pipeline.get_pvw_trans(), GL_TRUE);
    _face_shader.setfloat(_face_shader.getuniformlocation("ratio"), _ratio);
    _texture.bind(GL_TEXTURE0);
    _texture_tongue.bind(GL_TEXTURE1);
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    _face_shader.unuse();
    glBindVertexArray(0);
    
}

void CRecognition::draw(){
    glViewport (0, 0, _width, _height);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_defaultframebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    
    draw_face();
    detec_face();

    glBindFramebuffer(GL_FRAMEBUFFER, _defaultframebuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //draw_head();
    draw_warp();
    
}

void CRecognition::shutdown(){
    glDeleteProgram (_face_shader.programid());
}

int CRecognition::esMain (ESContext *esContext){
    esContext->render = (CRender*)this;
    esCreateWindow(esContext, "face", esContext->width, esContext->height, ES_WINDOW_RGB);
    _write_dir = esContext->writedir;
    if (GL_FALSE == _face_shader.loadshader(esContext->appdir,
                                            "triangle.vs",
                                            "triangle.fs")){
        return GL_FALSE;
    }
    
    if (GL_FALSE == _face_shader_points.loadshader(esContext->appdir,
                                            "points.vs",
                                            "points.fs")){
        return GL_FALSE;
    }
    
    if(GL_FALSE == _face_shader_move_head.loadshader(esContext->appdir,
                                                     "move_head.vs",
                                                     "move_head.fs")){
        return GL_FALSE;
    }
    
    if(GL_FALSE == _face_shader_warp.loadshader(esContext->appdir,
                                                     "move_head.vs",
                                                     "bicubic.fs")){
        return GL_FALSE;
    }
    
    _width = esContext->width;
    _height = esContext->height;
    _camera = new Camera(Vec3f(0.0f, 0.0f, -10.0f));
    PersProjInfo sp;
    sp.FOV = 45;
    sp.Width = 600;//esContext->width;
    sp.Height = 600;//esContext->height;
    sp.zNear = 0.1;
    sp.zFar = 100;
    _camera->set_proj_info(sp);
    _dir = esContext->appdir;
    std::string strimge_niuyan(esContext->appdir);
    strimge_niuyan.append("/niuyan.jpg");//niuyan.jpg  //mnls.jpg //fanbingbing.jpg //IMG_0117.JPG
    _str_text = strimge_niuyan;
    if (!_texture.load_texture(strimge_niuyan)){
        printf("Error loading texture '%s'\n", strimge_niuyan.c_str());
        assert(false);
        return GL_FALSE;
    }
    
    _face.init_handle((MG_BYTE*)esContext->model_bytes, esContext->_model_datas_length);
    bind();
    bind_frame();
    _face_shader.use();
    _face_shader.setint(_face_shader.getuniformlocation("imput_image_texture"), 0);
    //_face_shader.setint(_face_shader.getuniformlocation("tongue_image_texture"), 1);
    _face_shader.unuse();
    
    _face_shader_move_head.use();
    _face_shader_move_head.setint(_face_shader_move_head.getuniformlocation("imput_image_texture"), 0);
    _face_shader_move_head.unuse();
    
    _face_shader_warp.use();
    _face_shader_warp.setint(_face_shader_warp.getuniformlocation("imput_image_texture"), 0);
    _face_shader_warp.setvec2(_face_shader_warp.getuniformlocation("imgSize"), _texture.get_width(), _texture.get_height());
    _face_shader_warp.unuse();
    return GL_TRUE;
}

void CRecognition::bind(){
    float vertices[] = {
        // positions          // colors           // texture coords
        1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top right
        1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);
    
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}

void CRecognition::make_point(std::vector<float>& vec_vertices_face, float x, float y, float z){
    vec_vertices_face.emplace_back(x);
    vec_vertices_face.emplace_back(y);
    vec_vertices_face.emplace_back(z);
    vec_vertices_face.emplace_back(to_uv(x));
    vec_vertices_face.emplace_back(to_uv(y));
}

void CRecognition::bind_face(){
    glGenVertexArrays(1, &_vao_face);
    glGenBuffers(1, &_vbo_face);
    glGenBuffers(1, &_ebo_face);
    glBindVertexArray(_vao_face);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo_face);
    _nums_face = 108;
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * _nums_face, &_face106, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

float CRecognition::to_uv(float v){
    return (v + 1.0)/2.0;
}

void CRecognition::detec_face(){
    if (_point){
        if (1){
            _face_shader_points.use();
            _face_shader_points.setmat4(_face_shader_points.getuniformlocation("pvw"), _pipeline.get_pvw_trans(), GL_TRUE);
            glBindVertexArray(_vao_face);
            glDrawArrays(GL_POINTS, 0, _nums_face);
            _face_shader_points.unuse();
            glBindVertexArray(0);
        }
        return;
    }
    
    std::vector<MG_FACE> faces;
    int width, height, nrComponents;
    unsigned char *data = _texture.load_texture(_str_text.c_str(), width, height, nrComponents);
    _face.set_image_data(width, height, data, MG_IMAGEMODE_RGB);
    _face.detect_face(faces);
    free(data);
    data = nullptr;
    
    MG_SINGLE fw = (MG_SINGLE)width/2.0f;
    MG_SINGLE fh = (MG_SINGLE)height/2.0f;
    //for (auto iter = faces.begin(); iter != faces.end(); iter++){
    if (faces.size() > 0){
        _point = true;
        _face.set_face_points(fw, fh, faces[0].points, _face106);
    }
    
    if (_point){
        bind_face();
        face_uniform();
        head_uniform();
        warp_uniform();
    }
}


void CRecognition::face_uniform_mouth(){
    float mouth_left_x = to_uv(_face106.mouth_inside[0].x);
    float mouth_left_y = to_uv(_face106.mouth_inside[0].y);
    float mouth_right_x = to_uv(_face106.mouth_inside[4].x);
    float mouth_right_y = to_uv(_face106.mouth_inside[4].y);
    float mouth_top_x = to_uv(_face106.mouth_outside[2].x);
    float mouth_top_y = to_uv((_face106.mouth_outside[2].y + _face106.nose[4].y)/2.0);
    float mouth_bottom_x = to_uv(_face106.mouth_outside[9].x);
    float mouth_bottom_y = to_uv((_face106.mouth_outside[9].y + _face106.cheek[16].y)/2.0);
    _face_shader.setvec2(_face_shader.getuniformlocation("mouth_left"), mouth_left_x, mouth_left_y);
    _face_shader.setvec2(_face_shader.getuniformlocation("mouth_right"), mouth_right_x, mouth_right_y);
    _face_shader.setvec2(_face_shader.getuniformlocation("mouth_top"), mouth_top_x, mouth_top_y);
    _face_shader.setvec2(_face_shader.getuniformlocation("mouth_bottom"), mouth_bottom_x, mouth_bottom_y);
    
    float mouth_distance = distance_2d(Vector2f(mouth_left_x, mouth_left_y), Vector2f(mouth_right_x, mouth_right_y));
    float mouth_cos = (mouth_right_x - mouth_left_x)/mouth_distance;
    float mouth_sin = (mouth_right_y - mouth_left_y)/mouth_distance;
    _face_shader.setfloat(_face_shader.getuniformlocation("mouth_cos"), mouth_cos);
    _face_shader.setfloat(_face_shader.getuniformlocation("mouth_sin"), mouth_sin);
    _face_shader.setfloat(_face_shader.getuniformlocation("mouth_tan"), mouth_sin/mouth_cos);
    _face_shader.setfloat(_face_shader.getuniformlocation("mouth_k"), (mouth_left_y - mouth_right_y)/(mouth_left_x - mouth_right_x));
}

float CRecognition::accuracy(float a, int len){
    return 0.0;
}

void CRecognition::face_uniform_right_eye(){
    float right_eye_left_x = to_uv(_face106.right_eye[1].x);
    float right_eye_left_y = to_uv(_face106.right_eye[1].y);
    float right_eye_right_x = to_uv(_face106.right_eye[5].x);
    float right_eye_right_y = to_uv(_face106.right_eye[5].y);
    float right_eye_top_x = to_uv(_face106.right_eye[3].x);
    float right_eye_top_y = to_uv(_face106.right_eye[3].y);
    float right_eye_bottom_x = to_uv(_face106.right_eye[7].x);
    float right_eye_bottom_y = to_uv(_face106.right_eye[7].y);
    
    _face_shader.setvec2(_face_shader.getuniformlocation("right_eye_left"), right_eye_left_x, right_eye_bottom_y);
    _face_shader.setvec2(_face_shader.getuniformlocation("right_eye_right"), right_eye_right_x, right_eye_bottom_y);
    _face_shader.setvec2(_face_shader.getuniformlocation("right_eye_top"), right_eye_top_x, right_eye_top_y);
    _face_shader.setvec2(_face_shader.getuniformlocation("right_eye_bottom"),
                         right_eye_bottom_x, right_eye_bottom_y);
    float ellispe_a = (right_eye_right_x - right_eye_left_x)/2.0f;
    float ellispe_b = right_eye_bottom_y - right_eye_top_y;
    _face_shader.setfloat(_face_shader.getuniformlocation("right_eye_ellipse_a"), ellispe_a);
    _face_shader.setfloat(_face_shader.getuniformlocation("right_eye_ellipse_b"), ellispe_b);
}

void CRecognition::face_uniform_left_eye(){
    float left_eye_left_x = to_uv(_face106.left_eye[1].x);
    float left_eye_left_y = to_uv(_face106.left_eye[1].y);
    float left_eye_right_x = to_uv(_face106.left_eye[5].x);
    float left_eye_right_y = to_uv(_face106.left_eye[5].y);
    float left_eye_top_x = to_uv(_face106.left_eye[3].x);
    float left_eye_top_y = to_uv(_face106.left_eye[3].y);
    float left_eye_bottom_x = to_uv(_face106.left_eye[7].x);
    float left_eye_bottom_y = to_uv(_face106.left_eye[7].y);
    
    _face_shader.setvec2(_face_shader.getuniformlocation("left_eye_left"), left_eye_left_x, left_eye_bottom_y);
    _face_shader.setvec2(_face_shader.getuniformlocation("left_eye_right"), left_eye_right_x, left_eye_bottom_y);
    _face_shader.setvec2(_face_shader.getuniformlocation("left_eye_top"), left_eye_top_x, left_eye_top_y);
    _face_shader.setvec2(_face_shader.getuniformlocation("left_eye_bottom"),
                         left_eye_bottom_x, left_eye_bottom_y);

    float ellispe_a = (left_eye_right_x - left_eye_left_x)/2.0f;
    float ellispe_b = left_eye_bottom_y - left_eye_top_y;
    _face_shader.setfloat(_face_shader.getuniformlocation("left_eye_ellipse_a"), ellispe_a);
    _face_shader.setfloat(_face_shader.getuniformlocation("left_eye_ellipse_b"), ellispe_b);
    //
}

void CRecognition::face_uniform_right_eyebrow(){
    float right_eyebrow_left_x = to_uv((_face106.right_eyebrow[8].x + _face106.left_eyebrow[5].x)/2.0 );
    float right_eyebrow_left_y = to_uv(_face106.right_eyebrow[8].y);
    float right_eyebrow_right_x = to_uv(_face106.right_eyebrow[4].x);
    float right_eyebrow_right_y = to_uv(_face106.right_eyebrow[4].y);
    float right_eyebrow_right_top = to_uv(_face106.right_eyebrow[0].y);
    float right_eyebrow_right_bottom = right_eyebrow_left_y;
    
    for(int i = 1; i <= 4; i++){
        float temp_top = to_uv(_face106.right_eyebrow[i].y);
        if (temp_top < right_eyebrow_right_top){right_eyebrow_right_top = temp_top;}
    }
    
    for(int i = 4; i <= 8; i++){
        float temp_bottom = to_uv(_face106.right_eyebrow[i].y);
        if (temp_bottom > right_eyebrow_right_bottom){right_eyebrow_right_bottom = temp_bottom;}
    }
    
    float right_eye_top = to_uv(_face106.right_eye[0].y);
    for (int i = 1; i <= 5; i++){
        float temp_eye_top = to_uv(_face106.right_eye[i].y);
        if (temp_eye_top < right_eye_top)right_eye_top = temp_eye_top;
    }
    float right_eyebrow_height = right_eyebrow_right_bottom - right_eyebrow_right_top;
    
    _face_shader.setvec2(_face_shader.getuniformlocation("right_eyebrow_left"), right_eyebrow_left_x, right_eyebrow_left_y);
    _face_shader.setvec2(_face_shader.getuniformlocation("right_eyebrow_right"), right_eyebrow_right_x, right_eyebrow_right_y);
    _face_shader.setfloat(_face_shader.getuniformlocation("right_eyebrow_top"), right_eyebrow_right_top - right_eyebrow_height);
    _face_shader.setfloat(_face_shader.getuniformlocation("right_eyebrow_middle"), right_eyebrow_right_top);
    _face_shader.setfloat(_face_shader.getuniformlocation("right_eyebrow_bottom"), right_eyebrow_right_bottom);
    _face_shader.setfloat(_face_shader.getuniformlocation("right_eyebrow_height"), right_eyebrow_height);
}

void CRecognition::face_uniform_left_eyebrow(){
    float left_eyebrow_right_x = to_uv((_face106.left_eyebrow[5].x + _face106.right_eyebrow[8].x)/2.0 );
    float left_eyebrow_right_y = to_uv(_face106.left_eyebrow[5].y);
    float left_eyebrow_left_x = to_uv(_face106.left_eyebrow[0].x);
    float left_eyebrow_left_y = to_uv(_face106.left_eyebrow[0].y);
    float left_eyebrow_top = left_eyebrow_left_y;
    float left_eyebrow_bottom = left_eyebrow_left_y;
    
    for(int i = 1; i <= 4; i++){
        float temp_top = to_uv(_face106.left_eyebrow[i].y);
        if (temp_top < left_eyebrow_top){left_eyebrow_top = temp_top;}
    }
    
    for(int i = 5; i <= 8; i++){
        float temp_bottom = to_uv(_face106.left_eyebrow[i].y);
        if (temp_bottom > left_eyebrow_bottom){left_eyebrow_bottom = temp_bottom;}
    }

    float left_eye_top = to_uv(_face106.left_eye[0].y);
    for (int i = 1; i <= 5; i++){
        float temp_eye_top = to_uv(_face106.right_eye[i].y);
        if (temp_eye_top < left_eye_top)left_eye_top = temp_eye_top;
    }
    
    float left_eyebrow_height = left_eyebrow_bottom - left_eyebrow_top;
    //left_eyebrow_bottom += left_eyebrow_height * 0.06f;
    //left_eyebrow_height = left_eyebrow_bottom - left_eyebrow_top;
    _face_shader.setvec2(_face_shader.getuniformlocation("left_eyebrow_left"), left_eyebrow_left_x, left_eyebrow_left_y);
    _face_shader.setvec2(_face_shader.getuniformlocation("left_eyebrow_right"), left_eyebrow_right_x, left_eyebrow_right_y);
    _face_shader.setfloat(_face_shader.getuniformlocation("left_eyebrow_top"), left_eyebrow_top - left_eyebrow_height);
    _face_shader.setfloat(_face_shader.getuniformlocation("left_eyebrow_middle"), left_eyebrow_top);
    _face_shader.setfloat(_face_shader.getuniformlocation("left_eyebrow_bottom"), left_eyebrow_bottom);
    _face_shader.setfloat(_face_shader.getuniformlocation("left_eyebrow_height"), left_eyebrow_height);
}

void CRecognition::face_uniform_eyebrow(){
    float right_eyebrow_left_x = to_uv((_face106.right_eyebrow[8].x + _face106.left_eyebrow[5].x)/2.0 );
    float right_eyebrow_left_y = to_uv(_face106.right_eyebrow[8].y);
    float right_eyebrow_right_x = to_uv(_face106.right_eyebrow[4].x);
    float right_eyebrow_right_y = to_uv(_face106.right_eyebrow[4].y);
    float right_eyebrow_right_top = to_uv(_face106.right_eyebrow[0].y);
    float right_eyebrow_right_bottom = right_eyebrow_left_y;
    
    for(int i = 1; i <= 4; i++){
        float temp_top = to_uv(_face106.right_eyebrow[i].y);
        if (temp_top < right_eyebrow_right_top){right_eyebrow_right_top = temp_top;}
    }
    
    for(int i = 4; i <= 8; i++){
        float temp_bottom = to_uv(_face106.right_eyebrow[i].y);
        if (temp_bottom > right_eyebrow_right_bottom){right_eyebrow_right_bottom = temp_bottom;}
    }
    
    float right_eyebrow_height = right_eyebrow_right_bottom - right_eyebrow_right_top;
    
    float left_eyebrow_right_x = to_uv((_face106.left_eyebrow[5].x + _face106.right_eyebrow[8].x)/2.0 );
    float left_eyebrow_right_y = to_uv(_face106.left_eyebrow[5].y);
    float left_eyebrow_left_x = to_uv(_face106.left_eyebrow[0].x);
    float left_eyebrow_left_y = to_uv(_face106.left_eyebrow[0].y);
    float left_eyebrow_top = left_eyebrow_left_y;
    float left_eyebrow_bottom = left_eyebrow_left_y;
    
    for(int i = 1; i <= 4; i++){
        float temp_top = to_uv(_face106.left_eyebrow[i].y);
        if (temp_top < left_eyebrow_top){left_eyebrow_top = temp_top;}
    }
    
    for(int i = 5; i <= 8; i++){
        float temp_bottom = to_uv(_face106.left_eyebrow[i].y);
        if (temp_bottom > left_eyebrow_bottom){left_eyebrow_bottom = temp_bottom;}
    }
    
    float left_eyebrow_height = left_eyebrow_bottom - left_eyebrow_top;
    
    float eyebrow_height = left_eyebrow_height > right_eyebrow_height ? left_eyebrow_height : right_eyebrow_height;
    left_eyebrow_top = left_eyebrow_bottom - 2 * eyebrow_height;
    right_eyebrow_right_top = right_eyebrow_right_bottom - 2* eyebrow_height;
    
    _face_shader.setvec2(_face_shader.getuniformlocation("left_eyebrow_left"), left_eyebrow_left_x, left_eyebrow_left_y);
    _face_shader.setvec2(_face_shader.getuniformlocation("left_eyebrow_right"), left_eyebrow_right_x, left_eyebrow_right_y);
    _face_shader.setfloat(_face_shader.getuniformlocation("left_eyebrow_top"), left_eyebrow_top);
    _face_shader.setfloat(_face_shader.getuniformlocation("left_eyebrow_middle"), left_eyebrow_top + eyebrow_height);
    _face_shader.setfloat(_face_shader.getuniformlocation("left_eyebrow_bottom"), left_eyebrow_bottom);
    _face_shader.setfloat(_face_shader.getuniformlocation("left_eyebrow_height"), eyebrow_height);
    
    _face_shader.setvec2(_face_shader.getuniformlocation("right_eyebrow_left"), right_eyebrow_left_x, right_eyebrow_left_y);
    _face_shader.setvec2(_face_shader.getuniformlocation("right_eyebrow_right"), right_eyebrow_right_x, right_eyebrow_right_y);
    _face_shader.setfloat(_face_shader.getuniformlocation("right_eyebrow_top"), right_eyebrow_right_top);
    _face_shader.setfloat(_face_shader.getuniformlocation("right_eyebrow_middle"), right_eyebrow_right_top + eyebrow_height);
    _face_shader.setfloat(_face_shader.getuniformlocation("right_eyebrow_bottom"), right_eyebrow_right_bottom);
    _face_shader.setfloat(_face_shader.getuniformlocation("right_eyebrow_height"), eyebrow_height);
}

void CRecognition::face_uniform_nod(){
    float face_bottom_x = to_uv(_face106.cheek[13].x);
    float face_bottom_y = to_uv(_face106.cheek[13].y);
    for (int i = 14; i <= 18; i++){
        float temp_bottom = to_uv(_face106.cheek[i].y);
        if (temp_bottom > face_bottom_y){
            face_bottom_y = temp_bottom;
            face_bottom_x = to_uv(_face106.cheek[i].x);
        }
    }
    
    float face_left_x = to_uv(_face106.cheek[0].x);
    float face_left_y = to_uv(_face106.cheek[0].y);
    for (int i = 1; i <= 10; i++){
        float temp_left = to_uv(_face106.cheek[i].x);
        if (temp_left < face_left_x){
            face_left_x = temp_left;
            face_left_y = to_uv(_face106.cheek[i].y);
        }
    }
    
    float face_right_x = to_uv(_face106.cheek[32].x);
    float face_right_y = to_uv(_face106.cheek[32].y);
    for (int i = 23; i < 32; i++){
        float temp_right = to_uv(_face106.cheek[i].x);
        if (temp_right > face_left_x){
            face_right_x = temp_right;
            face_right_y = to_uv(_face106.cheek[i].y);
        }
    }
    
    float face_top_x = to_uv(_face106.bridge_nose[1].x);
    float face_top_y = 2.0f * to_uv(_face106.bridge_nose[1].y) - face_bottom_y;
    if (face_top_y < 0.0f){
        face_top_y = 0.0f;
    }
    
    face_top_y = 1.0f - face_bottom_y;
    face_bottom_y = face_top_y +  2.0 * (face_bottom_y - to_uv(_face106.bridge_nose[1].y));

    _face_shader_move_head.setvec2(_face_shader_move_head.getuniformlocation("face_head_bottom"), face_bottom_x, face_bottom_y + 0.05);
    _face_shader_move_head.setvec2(_face_shader_move_head.getuniformlocation("face_head_left"), face_left_x, face_left_y);
    _face_shader_move_head.setvec2(_face_shader_move_head.getuniformlocation("face_head_right"), face_right_x, face_right_y);
    _face_shader_move_head.setvec2(_face_shader_move_head.getuniformlocation("face_head_top"), face_top_x, face_top_y - 0.02);
    
    float face_middle_x = face_left_x + (face_right_x - face_left_x)/2.0f;
    float face_middle_y = face_top_y + (face_bottom_y - face_top_y) /2.0f;
    _face_shader_move_head.setvec2(_face_shader_move_head.getuniformlocation("face_head_middle"), face_middle_x, face_middle_y);
    _face_shader_move_head.setfloat(_face_shader_move_head.getuniformlocation("face_head_height"), face_bottom_y - face_top_y);
    _face_shader_move_head.setfloat(_face_shader_move_head.getuniformlocation("face_head_width"), face_right_x - face_left_x);
}

void CRecognition::face_uniform(){
    _face_shader.use();
    face_uniform_mouth();
    face_uniform_left_eye();
    face_uniform_right_eye();
    //face_uniform_eyebrow();
    face_uniform_right_eyebrow();
    face_uniform_left_eyebrow();
    _face_shader.unuse();
}

void CRecognition::head_uniform(){
    _face_shader_move_head.use();
    face_uniform_nod();
    _face_shader_move_head.unuse();
    save_face_points();
}

void CRecognition::warp_uniform(){
    _face_shader_warp.use();
    face_uniform_warp();
    _face_shader_warp.unuse();
    
}

void CRecognition::face_uniform_warp(){
    float right_eye_left_x = to_uv(_face106.left_eye[0].x);
    float right_eye_left_y = to_uv(_face106.left_eye[0].y);
    float right_eye_right_x = to_uv(_face106.right_eye[0].x);
    float right_eye_right_y = to_uv(_face106.right_eye[0].y);
    float right_mouth_top_x = to_uv(_face106.mouth_outside[3].x);
    float right_mouth_top_y = to_uv(_face106.mouth_outside[3].y);
    float right_mouth_bottom_x = to_uv(_face106.mouth_outside[9].x);
    float right_mouth_bottom_y = to_uv(_face106.mouth_outside[9].y);
    
    float left_edge_2_x = to_uv(_face106.cheek[7].x);
    float left_edge_2_y = to_uv(_face106.cheek[7].y);
    float left_edge_3_x = to_uv(_face106.cheek[10].x);
    float left_edge_3_y = to_uv(_face106.cheek[10].y);
    float left_edge_4_x = to_uv(_face106.cheek[13].x);
    float left_edge_4_y = to_uv(_face106.cheek[13].y);
    
    
    float right_edge_2_x = to_uv(_face106.cheek[25].x);
    float right_edge_2_y = to_uv(_face106.cheek[25].y);
    float right_edge_3_x = to_uv(_face106.cheek[22].x);
    float right_edge_3_y = to_uv(_face106.cheek[22].y);
    float right_edge_4_x = to_uv(_face106.cheek[19].x);
    float right_edge_4_y = to_uv(_face106.cheek[19].y);
    
    float chin_x = to_uv(_face106.cheek[16].y);
    float chin_y = to_uv(_face106.cheek[16].y);
    _face_shader_warp.setvec2(_face_shader_warp.getuniformlocation("leftEye"), right_eye_left_x, 1.0 - right_eye_left_y);
    _face_shader_warp.setvec2(_face_shader_warp.getuniformlocation("rightEye"), right_eye_right_x, 1.0 - right_eye_right_y);
    _face_shader_warp.setvec2(_face_shader_warp.getuniformlocation("mouthTop"), right_mouth_top_x, 1.0 - right_mouth_top_y);
    _face_shader_warp.setvec2(_face_shader_warp.getuniformlocation("mouthBottom"), right_mouth_bottom_x, 1.0 - right_mouth_bottom_y);
    _face_shader_warp.setvec2(_face_shader_warp.getuniformlocation("leftEdge2"), left_edge_2_x, 1.0 - left_edge_2_y);
    _face_shader_warp.setvec2(_face_shader_warp.getuniformlocation("leftEdge3"), left_edge_3_x, 1.0 - left_edge_3_y);
    _face_shader_warp.setvec2(_face_shader_warp.getuniformlocation("leftEdge4"), left_edge_4_x, 1.0 - left_edge_4_y);
    
    _face_shader_warp.setvec2(_face_shader_warp.getuniformlocation("rightEdge2"), right_edge_2_x, 1.0 - right_edge_2_y);
    _face_shader_warp.setvec2(_face_shader_warp.getuniformlocation("rightEdge3"), right_edge_3_x, 1.0 - right_edge_3_y);
    _face_shader_warp.setvec2(_face_shader_warp.getuniformlocation("rightEdge4"), right_edge_4_x, 1.0 - right_edge_4_y);
    
    _face_shader_warp.setvec2(_face_shader_warp.getuniformlocation("chin"), chin_x, 1.0 - chin_y);
}

void CRecognition::bind_frame(){
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_defaultframebuffer);
    
    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    
    glGenTextures(1, &_texture_colorbuffer);
    glBindTexture(GL_TEXTURE_2D, _texture_colorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture_colorbuffer, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, _defaultframebuffer);
    
    float vertices[] = {
        // positions          // texture coords
        1.0f,  1.0f, 0.0f,    1.0f, 0.0f, // top right
        1.0f, -1.0f, 0.0f,    1.0f, 1.0f, // bottom right
        -1.0f,  1.0f, 0.0f,   0.0f, 0.0f,  // top left
        
        1.0f, -1.0f, 0.0f,    1.0f, 1.0f, // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 1.0f, // bottom left
        -1.0f,  1.0f, 0.0f,   0.0f, 0.0f  // top left
    };
    

    glGenVertexArrays(1, &_quad_vao);
    glGenBuffers(1, &_quad_vbo);
    glBindVertexArray(_quad_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
}

void CRecognition::un_bind_frame(){
    glDeleteRenderbuffers(1, &_render_buffer);
    glDeleteFramebuffers(1, &_framebuffer);
}


void CRecognition::save_face_points(){
    std::ofstream outfacepoints_x;
    std::ofstream outfacepoints_y;
    std::string strfile_x(_write_dir + "/facepoints_x.txt");
    std::string strfile_y(_write_dir + "/facepoints_y.txt");
    outfacepoints_x.open(strfile_x.c_str());
    outfacepoints_y.open(strfile_y.c_str());
    /*
    for(int i =0; i < 33; i++){
        outfacepoints_x << _face106.cheek[i].x << std::endl;
        outfacepoints_y << _face106.cheek[i].y << std::endl;
    }
    
    for(int i =0; i < 9; i++){
        outfacepoints_x << _face106.left_eye[i].x << std::endl;
        outfacepoints_y << _face106.left_eye[i].y << std::endl;
    }
    
    for(int i =0; i < 9; i++){
        outfacepoints_x << _face106.right_eye[i].x << std::endl;
        outfacepoints_y << _face106.right_eye[i].y << std::endl;
    }
    
    for(int i =0; i < 9; i++){
        outfacepoints_x << _face106.left_eyebrow[i].x << std::endl;
        outfacepoints_y << _face106.left_eyebrow[i].y << std::endl;
    }
    
    for(int i =0; i < 9; i++){
        outfacepoints_x << _face106.right_eyebrow[i].x << std::endl;
        outfacepoints_y << _face106.right_eyebrow[i].y << std::endl;
    }
    
    for(int i =0; i < 9; i++){
        outfacepoints_x << _face106.nose[i].x << std::endl;
        outfacepoints_y << _face106.nose[i].y << std::endl;
    }
    
    for(int i =0; i < 6; i++){
        outfacepoints_x << _face106.bridge_nose[i].x << std::endl;
        outfacepoints_y << _face106.bridge_nose[i].y << std::endl;
    }
    */
    
    
    for(int i =0; i < 8; i++){
        outfacepoints_x << _face106.mouth_inside[i].x << std::endl;
        outfacepoints_y << _face106.mouth_inside[i].y << std::endl;
    }
    /*
    for(int i =0; i < 12; i++){
        outfacepoints_x << _face106.mouth_outside[i].x << std::endl;
        outfacepoints_y << _face106.mouth_outside[i].y << std::endl;
    }
    
    for(int i =0; i < 2; i++){
        outfacepoints_x << _face106.benevolence[i].x << std::endl;
        outfacepoints_y << _face106.benevolence[i].y << std::endl;
    }
    */
    outfacepoints_x.close();
    outfacepoints_y.close();
    
}



