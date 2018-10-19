//
//  bones.hpp
//  render
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef bones_hpp
#define bones_hpp


#include <stdio.h>
#include "context.hpp"
#include "bones_shader.hpp"
#include "rander.hpp"
#include "bones_mesh.hpp"
#include "camera.hpp"
#include "quad.hpp"

class CBones: public CRender{
public:
    CBones();
    ~CBones();
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
private:
    BonesMesh* _bones_mesh = nullptr;
    Camera* _camera = nullptr;
    BonesShader _shader;
    CShader _shader_real;
    CQuad _quad;
};

#endif /* bones_hpp */
