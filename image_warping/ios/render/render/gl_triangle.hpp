//
//  gl_triangle.hpp
//  lh_render
//
//  Created by liu on 2018/6/19.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef gl_triangle_hpp
#define gl_triangle_hpp

#include <stdio.h>
#include "context.hpp"
#include "shader.hpp"
#include "rander.hpp"
#include "texture.hpp"
#include "timer.hpp"

class CTriangle: public CRender{
public:
    CTriangle();
    ~CTriangle();
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
    CShader _face_shader;
    TexureGl _texture;
    Timer _timer;
    float _step = 0.05f;
    float _ratio = 1.0f;
    unsigned int _vao;
    unsigned int _vbo;
    unsigned int _ebo;
};

#endif /* gl_triangle_hpp */
