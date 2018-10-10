//
//  tetris.cpp
//  render
//
//  Created by liu on 2018/8/28.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "tetris.hpp"
#include "rander.hpp"
#include "msg.h"

#include <assert.h>

float acube[] = {
    // positions          // texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

float aplane[] = {
    // positions          // texture Coords
    5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
    
    5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
    5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};

float aquad[] = {
    // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    
    -1.0f,  1.0f,  0.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f,  1.0f, 1.0f
};

CTetris::CTetris():_origin(0.0f, 0.0f, 35.0f)
{
}


CTetris::~CTetris(){
    release();
}

void CTetris::update(){
    ;
}

void CTetris::touch_event(){
    ;
}
void CTetris::release(){
    glDeleteVertexArrays(1, &_cube_vao);
    glDeleteVertexArrays(1, &_plane_vao);
    glDeleteVertexArrays(1, &_quad_vao);
    glDeleteBuffers(1, &_cube_vbo);
    glDeleteBuffers(1, &_plane_vbo);
    glDeleteBuffers(1, &_quad_vbo);
    
    if(nullptr != _camera){
        delete _camera;
        _camera = nullptr;
    }
    
    if (nullptr != _gl_shardes){
        delete _gl_shardes;
        _gl_shardes = nullptr;
    }
    
    if (nullptr != _gl_shardes_screen){
        delete _gl_shardes_screen;
        _gl_shardes_screen = nullptr;
    }
}

bool CTetris::init_shader(){
    if (nullptr == _gl_shardes){
        _gl_shardes = new CShader;
    }
    
    if (nullptr == _gl_shardes_screen){
        _gl_shardes_screen = new CShader;
    }
    
    if(GL_FALSE == _gl_shardes->loadshader(_dir.c_str(),
                                 "framebuffers.vs",
                               "framebuffers.fs") ||
    GL_FALSE == _gl_shardes_screen->loadshader(_dir.c_str(),
                                 "framebuffers_screen.vs",
                                 "framebuffers_screen.fs")){
        assert(0);
        return false;
    }
    
    _gl_shardes->use();
    _gl_shardes->setint("texture1", 0);
    _gl_shardes->unuse();
    _gl_shardes_screen->use();
    _gl_shardes_screen->setint("screenTexture", 0);
    _gl_shardes_screen->unuse();
    
    return true;
}

void CTetris::bindvao(){
    // cube VAO
    glGenVertexArrays(1, &_cube_vao);
    glGenBuffers(1, &_cube_vbo);
    glBindVertexArray(_cube_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _cube_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(acube), &acube, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    
    // plane VAO
    glGenVertexArrays(1, &_plane_vao);
    glGenBuffers(1, &_plane_vbo);
    glBindVertexArray(_plane_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _plane_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aplane), &aplane, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    
    // screen quad VAO
    glGenVertexArrays(1, &_quad_vao);
    glGenBuffers(1, &_quad_vbo);
    glBindVertexArray(_quad_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aquad), &aquad, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void CTetris::bindtexture(){
    std::string strcube(_dir + "/marble.jpg");
    std::string strfloor(_dir + "/metal.png");
    TexureGl cube;
    TexureGl floor;
    _cube_texture = cube.load_texture(strcube.c_str());
    _floor_texture = floor.load_texture(strfloor.c_str());
}

void CTetris::bindframe()
{
    // framebuffer configuration
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_defaultframebuffer);
    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    
    // create a color attachment texture
    glGenTextures(1, &_texture_colorbuffer);
    glBindTexture(GL_TEXTURE_2D, _texture_colorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture_colorbuffer, 0);
    
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &_render_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _render_buffer);
    // use a single renderbuffer object for both a depth AND stencil buffer.
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
    // now actually attach it
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _render_buffer);
    
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, _defaultframebuffer);
}

void CTetris::draw() {

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_defaultframebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);// make sure we clear the framebuffer's content
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _pipeline.set_camera(Vec3f(0.0f, 0.0f, -10.0f), Vec3f(0.0f, 0.0f, 1.0f), Vec3f(0.0f, 1.0f, 0.0f));
    _pipeline.set_perspective_proj(_camera->get_proj_info());
    //_pipeline.rotate(0.0f, 0.0f, 0.0f);
    //_pipeline.scale(4.0);
    ;
    _gl_shardes->use();
    _gl_shardes->setmat4("view", _pipeline.get_view_trans());
    _gl_shardes->setmat4("projection", _pipeline.get_proj_trans());
    
    // floor
    glBindVertexArray(_plane_vao);
    glBindTexture(GL_TEXTURE_2D, _floor_texture);
    _pipeline.world_pos(0.0f, 0.0f, 0.0f);
    _gl_shardes->setmat4("model", _pipeline.get_world_trans());
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    
    

    glBindFramebuffer(GL_FRAMEBUFFER, _defaultframebuffer);
    glDisable(GL_DEPTH_TEST);
    // disable depth test so screen-space quad isn't discarded due to depth test.
    // clear all relevant buffers
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    _gl_shardes_screen->use();
    glBindVertexArray(_quad_vao);
    glBindTexture(GL_TEXTURE_2D, _texture_colorbuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    render_tetri();
  
}

void CTetris::unbindframe(){
    glDeleteTextures(1, &_texture_colorbuffer);
    glDeleteRenderbuffers(1, &_render_buffer);
    glDeleteFramebuffers(1, &_framebuffer);
    _texture_colorbuffer = 0;
    _render_buffer = 0;
    _framebuffer = 0;
}

void CTetris::shutdown(){
    glDeleteProgram (_gl_shardes->programid());
    glDeleteProgram (_gl_shardes_screen->programid());
}

void CTetris::resize(int w, int h){
    _width = w;
    _height = h;
    _camera->resize(w, h);
    unbindframe();
    bindframe();
}

void CTetris::init() {
    glViewport (0, 0, _width, _height);
    glEnable(GL_DEPTH_TEST);
    
    init_shader();
    bindtexture();
    bindvao();
    bindframe();
    
    _grid.set_draw_face(DRAW_GRID_FACE_X | DRAW_GRID_FACE_Y | DRAW_GRID_FACE_Z);
    _grid.init(_dir.c_str());
    
    _manage_tetris.init(_dir.c_str() ,vec3(0, 0, 150));
}

void CTetris::render_tetri() {
    if (_manage_tetris.can_draw()) {
        _manage_tetris.down();
    }
    
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    _pipeline.world_pos(_origin);
    _grid.draw(_pipeline.get_proj_trans(),
               _pipeline.get_view_trans(),
               _pipeline.get_world_trans());
    
    _manage_tetris.draw(_pipeline.get_proj_trans(),
                        _pipeline.get_view_trans(),
                        _pipeline.get_world_trans(), _camera->get_postion());
    glDisable(GL_DEPTH_TEST);
}
/*
  = 0,//暂停
 KEY_BOARD_A = 1,//左
 KEY_BOARD_S = 2,//下
 KEY_BOARD_D = 3,//右
 KEY_BOARD_W = 4,//变形
 KEY_BOARD_X = 5,//暂不用
 KEY_BOARD_C = 6;//暂不用
 */

void CTetris::keyboard(bool bchar, unsigned int uchar, unsigned int utype){
    switch (utype) {
        case KEY_BOARD_SPACE:
            _manage_tetris.suspend();
            break;
        case KEY_BOARD_W:
            _manage_tetris.up();
            break;
        case KEY_BOARD_A:
            //_cube.left();
            _manage_tetris.left();
            break;
        case KEY_BOARD_S:
            _manage_tetris.down();
            break;
        case KEY_BOARD_D:
            //_cube.right();
            _manage_tetris.right();
            break;
        case KEY_BOARD_X:
            //_cube.depth();
            break;
        case KEY_BOARD_C:
            //_cube.depth_front();
            break;
        default:
            break;
    }
}


int CTetris::esMain (ESContext *esContext){
    esContext->render = (CRender*)this;
    esCreateWindow(esContext, "face", esContext->width, esContext->height, ES_WINDOW_RGB);
    _width = esContext->width;
    _height = esContext->height;
    _camera = new Camera(Vec3f(0.0f, 0.0f, -10.0f));
    PersProjInfo sp;
    sp.FOV = 45;
    sp.Width = 600;//esContext->width;
    sp.Height = 600;//esContext->height;
    sp.zNear = 0.1;
    sp.zFar = 100;
    _camera->set_proj_info(sp);
    _dir = esContext->appdir;
    init();
    return GL_TRUE;
}

