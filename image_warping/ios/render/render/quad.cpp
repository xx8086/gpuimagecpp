//
//  quad.cpp
//  render
//
//  Created by liu on 2018/10/10.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "quad.hpp"
#include <assert.h>

CQuad::CQuad(){
    ;
}
CQuad::~CQuad(){
    ;
}

void CQuad::gen_quad(){
    float qua_vertices[] = {
        -1.0f,  1.0f, -0.1f, 0.0f, 1.0f,
        -1.0f, -1.0f, -0.1f, 0.0f, 0.0f,
        1.0f,  1.0f, -0.1f, 1.0f, 1.0f,
        1.0f, -1.0f, -0.1f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(qua_vertices), &qua_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
    assert(GL_NO_ERROR == glGetError());
}

void CQuad::bind_texture(unsigned int active_texture, unsigned int texture_unit){
    glActiveTexture(active_texture);
    glBindTexture(GL_TEXTURE_2D, texture_unit);
}

void CQuad::draw_texture(){
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

