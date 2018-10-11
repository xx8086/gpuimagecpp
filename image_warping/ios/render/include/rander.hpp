//
//  rander.hpp
//  lh_render
//
//  Created by liu on 2018/6/21.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef rander_hpp
#define rander_hpp

#include <stdio.h>
#include <string>

class CRender{
public:
    CRender();
    virtual ~CRender();
public:
    virtual void release() = 0;
    virtual void init() = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void shutdown() = 0;
    virtual void keyboard(bool bchar, unsigned int uchar, unsigned int utype) = 0;
    virtual void touch_event() = 0;
    virtual void draw_worlds(int x, int y, const wchar_t* worlds){};
    virtual void set_color(float r, float g, float b){};
    
    unsigned int get_video_frame_texture_id()const;
    void video_frame(const unsigned char* datas, int w, int h);
    std::string get_dir()const;
    std::string loadfile(const char* file);
protected:
    unsigned int get_width()const;
    unsigned int get_height()const;
protected:
    unsigned int _width = 0;
    unsigned int _height = 0;
    unsigned int _video_frame_texture_id = 0;
    std::string _dir;
};


#endif /* rander_hpp */
