//
//  font.cpp
//  render
//
//  Created by liu on 2018/10/11.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "font.hpp"
#include <assert.h>

CFont::CFont(){
}

CFont::~CFont(){
    release();
}


void CFont::update(){
    ;
}
void CFont::keyboard(bool bchar, unsigned int uchar, unsigned int utype){
    ;
}

void CFont::touch_event(){
    ;
}

void CFont::release(){
}

void CFont::shutdown(){
    ;
}


void CFont::resize(unsigned int w, unsigned int h){
    _width = w;
    _height = h;
    //_camera->resize(w, h);
}

int CFont::esMain (ESContext *esContext){
    init();
    
    esContext->render = (CRender*)this;
    _dir = esContext->appdir;
    esCreateWindow(esContext, "CFont", esContext->width, esContext->height, ES_WINDOW_RGB);
    assert(GL_TRUE == _shader.loadshader(_dir.c_str(),
                                         "default.vs",
                                         "font.fsh"));
    
    std::string strfont(esContext->appdir);
    strfont.append("/hz.ttc");
    _font = new TextureFont(strfont.c_str(), 56);//字体大小暂时写成56，后面可以添加接口外面设置。
    _font_texture_id = _font->get_texture_id();
    resize(esContext->width, esContext->height);
    
    _shader.use();
    _shader.setint("inputImageTexture", 0);
    _shader.setint("worlds_texture", 1);
    set_color(0.0, 0.0, 0.0);
    _shader.unuse();
    _quad.gen_quad();
    return GL_TRUE;
}

void CFont::init(){
    glViewport (0, 0, _width, _height);
    glEnable(GL_DEPTH_TEST);
    
}

void CFont::set_color(float r, float g, float b){
    _shader.use();
    _shader.setvec3("world_color", r, g, b);
    _shader.unuse();
}

void CFont::draw_worlds(int begin_x, int beign_y, const wchar_t* worlds){
    _font->clear_texture();
    _font->draw_worlds(begin_x, beign_y, worlds);
}

void CFont::draw(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _shader.use();
    _quad.bind_texture(GL_TEXTURE0, _video_frame_texture_id);
    _quad.bind_texture(GL_TEXTURE1, _font_texture_id);
    _quad.draw_texture();
    _shader.unuse();
}
