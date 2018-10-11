//
//  font.hpp
//  render
//
//  Created by liu on 2018/10/11.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef font_hpp
#define font_hpp

#include "context.hpp"
#include "shader.hpp"
#include "rander.hpp"
#include "quad.hpp"
#include "usefont.hpp"

class CFont: public CRender{
public:
    CFont();
    ~CFont();
    int esMain(ESContext *esContext);
private:
    virtual void release();
    virtual void init();
    virtual void draw();
    virtual void update();
    virtual void shutdown();
    virtual void keyboard(bool bchar, unsigned int uchar, unsigned int utype);
    virtual void touch_event();
protected:
    virtual void set_point_light() {};
    virtual void set_spot_light() {};
    virtual void set_directional_light() {};
    
public:
    void set_color(float r, float g, float b);
    void draw_worlds(int begin_x, int beign_y, const wchar_t* worlds);
    void resize(unsigned int w, unsigned int h);
    //void reset_configure();
    
private:
    TextureFont* _font;
    unsigned int _font_texture_id = 0;
    int _sign = 0;
    CQuad _quad;
    CShader _shader;
    Vec2f _world_pos;
    Vec3f _world_color;
    std::wstring _str_worlds;
    std::string _dir;
};

#endif /* font_hpp */
