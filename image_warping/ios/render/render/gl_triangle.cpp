//
//  gl_triangle.cpp
//  lh_render
//
//  Created by liu on 2018/6/19.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "gl_triangle.hpp"
#include "pipeline.hpp"
#include <assert.h>

CTriangle::CTriangle(){
}

CTriangle::~CTriangle(){
    release();
}

void CTriangle::init(){
    glViewport (0, 0, _width, _height);
    glEnable(GL_DEPTH_TEST);
}

void CTriangle::update(){
    if (_timer.count_time()){
        if (_ratio <= 0.0 || _ratio > 1.0){//0.45
            _step = -_step;
        }
        _ratio += _step;
        _timer.set_count_time(10);
    }
}

void CTriangle::keyboard(bool bchar, unsigned int uchar, unsigned int utype){
    ;
}
void CTriangle::touch_event(){
    ;
}
void CTriangle::release(){
}

void CTriangle::resize(unsigned int w, unsigned int h){
    _width = w;
    _height = h;
}

void CTriangle::draw(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _face_shader.use();
    _face_shader.setfloat(_face_shader.getuniformlocation("ratio"), _ratio);
    _texture.bind(GL_TEXTURE0);
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    _face_shader.unuse();
}

void CTriangle::shutdown(){
    glDeleteProgram (_face_shader.programid());
}

int CTriangle::esMain (ESContext *esContext){
    esContext->render = (CRender*)this;
    esCreateWindow(esContext, "face", esContext->width, esContext->height, ES_WINDOW_RGB);
    if (GL_FALSE == _face_shader.loadshader(esContext->appdir,
                                       "triangle.vs",
                                       "triangle.fs")){
        return GL_FALSE;
    }
    _dir = esContext->appdir;
    std::string strimge(esContext->appdir);
    strimge.append("/niuyan.jpg");
    if (!_texture.load_texture(strimge)){
        printf("Error loading texture '%s'\n", strimge.c_str());
        assert(false);
        return GL_FALSE;
    }
    bind();
    return GL_TRUE;
}

void CTriangle::bind(){
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
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}
