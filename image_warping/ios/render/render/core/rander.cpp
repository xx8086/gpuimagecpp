//
//  rander.cpp
//  lh_render
//
//  Created by liu on 2018/6/21.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "rander.hpp"
#include "context.hpp"
#include <assert.h>

CRender::CRender(){
}

CRender::~CRender(){
    ;
}

unsigned int CRender::get_width()const{
    return _width;
}

unsigned int CRender::get_height()const{
    return _height;
}

std::string CRender::get_dir()const{
    return _dir;
}

unsigned int CRender::get_video_frame_texture_id()const{
    return _video_frame_texture_id;
}

void CRender::video_frame(const unsigned char* datas, int w, int h){
    if (0 == _video_frame_texture_id){
        int er1 = glGetError();
        glGenTextures(1, &_video_frame_texture_id);
        int er = glGetError();
        if (0 == _video_frame_texture_id){
            return;
        }
        glBindTexture(GL_TEXTURE_2D, _video_frame_texture_id);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     w,
                     h,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     datas);
        assert(GL_NO_ERROR == glGetError());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }else{
        glBindTexture(GL_TEXTURE_2D, _video_frame_texture_id);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, datas);
    }
}

