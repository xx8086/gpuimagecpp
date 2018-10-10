//
//  recognition.hpp
//  render
//
//  Created by liu on 2018/7/25.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef recognition_hpp
#define recognition_hpp

#include <stdio.h>
#include "context.hpp"
#include "shader.hpp"
#include "rander.hpp"
#include "texture.hpp"
#include "timer.hpp"
#include "face_plusplus.hpp"
#include "camera.hpp"
#include "pipeline.hpp"

class CRecognition: public CRender{
public:
    CRecognition();
    ~CRecognition();
    int esMain(ESContext *esContext);
private:
    virtual void release();
    virtual void init();
    virtual void draw();
    virtual void update();
    virtual void shutdown();
    virtual void keyboard(bool bchar, unsigned int uchar, unsigned int utype);
    virtual void touch_event();
    void resize(unsigned int w, unsigned int h);
    void bind();
private:
    void draw_face();
    void draw_head();
    void draw_warp();
    void warp_uniform();
    void face_uniform();
    void head_uniform();
    void face_uniform_mouth();
    void face_uniform_left_eye();
    void face_uniform_right_eye();
    void face_uniform_left_eyebrow();
    void face_uniform_right_eyebrow();
    void face_uniform_eyebrow();
    void face_uniform_nod();
    void face_uniform_warp();
    void bind_face();
    void detec_face();
    void make_point(std::vector<float>&, float x, float y, float z);
    inline float to_uv(float);
    float accuracy(float a, int len);
    void save_face_points();
public:
private:
    void bind_frame();
    void un_bind_frame();

private:
    FacePP _face;
    CShader _face_shader;
    CShader _face_shader_points;
    CShader _face_shader_move_head;
    CShader _face_shader_warp;
    Camera* _camera = nullptr;
    Pipeline _pipeline;
    TexureGl _texture;
    TexureGl _texture_tongue;
    Timer _timer;
    std::string _str_text;
    std::string _write_dir;
    float _step = 0.05f;
    float _ratio = 1.0f;
    unsigned int _vao;
    unsigned int _vbo;
    unsigned int _ebo;
    unsigned int _framebuffer;
    unsigned int _render_buffer;
    unsigned int _texture_colorbuffer;
    unsigned int _vao_face;
    unsigned int _vbo_face;
    unsigned int _ebo_face;
    unsigned int _nums_face;
    
    unsigned int _quad_vao;
    unsigned int _quad_vbo;
    GLint       _defaultframebuffer;
    bool _point = false;
    Face106 _face106;
};

#endif /* recognition_hpp */
