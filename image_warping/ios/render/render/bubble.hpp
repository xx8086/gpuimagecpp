//
//  bubble.hpp
//  render
//
//  Created by liu on 2018/10/12.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef bubble_hpp
#define bubble_hpp

#include "context.hpp"
#include "shader.hpp"
#include "rander.hpp"
#include "quad.hpp"
class CBubble: public CRender{
public:
    CBubble();
    ~CBubble();
    int esMain(ESContext *esContext);
    
public:
    virtual void release();
    virtual void init();
    virtual void draw();
    virtual void update();
    virtual void shutdown();
    virtual void keyboard(bool bchar, unsigned int uchar, unsigned int utype);
    virtual void touch_event();
    
public:
    void resize(unsigned int w, unsigned int h);
private:
    void bindtexture();
private:
    unsigned int _love_texture;
    CShader _shader;
    CQuad _quad;
    vec2 _pos;
};
#endif /* bubble_hpp */
