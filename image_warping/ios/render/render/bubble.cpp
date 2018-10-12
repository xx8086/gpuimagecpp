//
//  bubble.cpp
//  render
//
//  Created by liu on 2018/10/12.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "bubble.hpp"
#include "texture.hpp"
#include <assert.h>

CBubble::CBubble(){
}

CBubble::~CBubble(){
    release();
}


void CBubble::update(){
    ;
}
void CBubble::keyboard(bool bchar, unsigned int uchar, unsigned int utype){
    ;
}

void CBubble::touch_event(){
    ;
}

void CBubble::release(){
}

void CBubble::shutdown(){
    ;
}

void CBubble::init(){
    glViewport (0, 0, _width, _height);
    glEnable(GL_DEPTH_TEST);
    
}

void CBubble::draw(){
    _pos.y += 0.01;
    if(_pos.y >= 1.2){
        _pos.y = 0.0;
    }
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _shader.use();
    _shader.setvec2("love_postion", _pos.x, _pos.y);
    _quad.bind_texture(GL_TEXTURE0, _video_frame_texture_id);
    _quad.bind_texture(GL_TEXTURE1, _love_texture);
    _quad.draw_texture();
    _shader.unuse();
}

void CBubble::resize(unsigned int w, unsigned int h){
    _width = w;
    _height = h;
}

void CBubble::bindtexture(){
    std::string strlove(_dir + "/love.png");
    TexureGl love;
    _love_texture = love.load_texture(strlove.c_str());
}

int CBubble::esMain (ESContext *esContext){
    init();
    _pos.x = 0.5;
    _pos.y = 0.0;
    
    esContext->render = (CRender*)this;
    _dir = esContext->appdir;
    esCreateWindow(esContext, "CBubble", esContext->width, esContext->height, ES_WINDOW_RGB);
    assert(GL_TRUE == _shader.loadshader(_dir.c_str(),
                                         "default.vs",
                                         "bubble.fsh"));
    
    resize(esContext->width, esContext->height);
    bindtexture();
    _shader.use();
    _shader.setint("inputImageTexture", 0);
    _shader.setint("love_texture", 1);
    _shader.unuse();
    _quad.gen_quad();
    return GL_TRUE;
}
