//
//  quad.hpp
//  render
//
//  Created by liu on 2018/10/10.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef quad_hpp
#define quad_hpp

#include "shader.hpp"
class CQuad{
public:
    CQuad();
    ~CQuad();
public:
    void init(const char* dir);
    void gen_quad();
    void draw_texture(unsigned int);
private:
    CShader _shader;
    unsigned int _vao;
    unsigned int _vbo;
};


#endif /* quad_hpp */
