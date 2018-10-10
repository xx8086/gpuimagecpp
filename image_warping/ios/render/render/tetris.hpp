//
//  tetris.hpp
//  render
//
//  Created by liu on 2018/8/28.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef tetris_hpp
#define tetris_hpp


#include <stdio.h>
#include "context.hpp"
#include "shader.hpp"
#include "rander.hpp"
#include "texture.hpp"
#include "timer.hpp"
#include "face_plusplus.hpp"
#include "camera.hpp"
#include "pipeline.hpp"
#include "draw_grid.h"
#include "manage_tetri.h"

using namespace lh_gl;

class CTetris: public CRender{
public:
    CTetris();
    ~CTetris();
    int esMain(ESContext *esContext);
private:
    virtual void release();
    virtual void init();
    virtual void draw();
    virtual void update();
    virtual void shutdown();
    virtual void keyboard(bool bchar, unsigned int uchar, unsigned int utype);
    virtual void touch_event();
    void resize(int w, int h);
private:
    void render_tetri();
protected:
    virtual void set_point_light() {};
    virtual void set_spot_light() {};
    virtual void set_directional_light() {};
    
protected:
    void unbindframe();
    void bindframe();
    void bindvao();
    void bindtexture();
    bool init_shader();

private:
    GLuint _framebuffer;
    GLuint _texture_colorbuffer;
    GLuint _render_buffer;
    GLuint _vbo;
    GLuint _ibo;
    GLuint _wvp_location;
    CShader* _gl_shardes = nullptr;
    CShader* _gl_shardes_screen = nullptr;
    draw_grid _grid;
    manage_tetri _manage_tetris;
    Pipeline _pipeline;
    unsigned int _cube_vao;
    unsigned int _cube_vbo;
    unsigned int _plane_vao;
    unsigned int _plane_vbo;
    unsigned int _quad_vao;
    unsigned int _quad_vbo;
    unsigned int _cube_texture;
    unsigned int _floor_texture;
    Vector3f _origin;
    Camera* _camera = nullptr;
    GLint       _defaultframebuffer;
    std::string _dir;
};

#endif /* tetris_hpp */
