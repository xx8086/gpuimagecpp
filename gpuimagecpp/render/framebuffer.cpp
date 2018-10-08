//
//  framebuffer.hpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/10.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "framebuffer.hpp"
#include "../common/log.hpp"
#include <vector>
#include <assert.h>

namespace gpuimagecpp {
    FrameBuffer::FrameBuffer(){
        ;
    }
    
    FrameBuffer::~FrameBuffer(){
        release();
    }
    
    gic_void FrameBuffer::set_texture_options(const TextureOptions& options){
        _textures.set_options(options);
    }
    
    gic_void FrameBuffer::set_texture(const GicSize& fsize, gic_int counts){
        _textures.set_counts(counts);
        resize(fsize.width, fsize.height);
    }
    
    gic_void FrameBuffer::unbindframe(){
        if (nullptr != _images){
            delete [] _images;
            _images = nullptr;
        }
        _textures.release();
        if (0 != _renderbuffer_id)glDeleteRenderbuffers(1, &_renderbuffer_id);
        if (0 != _framebuffer_id)glDeleteFramebuffers(1, &_framebuffer_id);
    }
    gic_void FrameBuffer::bind_frame_buffer_id(){
        glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer_id);
    }
    gic_void FrameBuffer::bind_render_buffer_id(){
        glBindRenderbuffer(GL_RENDERBUFFER, _renderbuffer_id);
    }
    
    gic_bool FrameBuffer::bind_texture_buffer_id(gic_uint texture_unit){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_unit);
        return true;
    }
    gic_uint FrameBuffer::get_texture_buffer_id(gic_int texture_index){
        gic_uint texture_id = 0;
        if (0 <= texture_index && texture_index <  _textures.get_tex_counts()){
            texture_id = *(_ids + texture_index);
        }
        return texture_id;
    }
    
    gic_bool FrameBuffer::get_pixels_from_framebuffers(gic_uint gltex, gic_void* dataPtr, gic_int width, gic_int height){
        glBindTexture(GL_TEXTURE_2D, gltex);
        get_default_frame_buffer_id();
        bind_frame_buffer_id();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gltex, 0);
        if (GL_FRAMEBUFFER_COMPLETE != glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
            return false;
        }
        
        uint8_t* tempPtr = (uint8_t*)dataPtr;
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, dataPtr);
        
        glBindTexture(GL_TEXTURE_2D, 0);
        bind_default_frame_buffer_id();
        return true;
    }
    
    gic_byte* FrameBuffer::get_bytes(gic_int texture_index){
        get_pixels_from_framebuffers(texture_index, _images, _textures.get_width(), _textures.get_height());
        return _images;
    }
    
    gic_void FrameBuffer::save_bmp(const char* path, gic_byte* datas){
        _textures.save_bmp(path, datas);
    }
    
    gic_void FrameBuffer::resize(gic_int width, gic_int height){
        _ids = _textures.resize(width, height);
        if (nullptr != _images){
            delete [] _images;
            _images = nullptr;
        }
        _images = new unsigned char [width * height * 4];
        
    }
    gic_void FrameBuffer::bind_default_frame_buffer_id(){
        glBindFramebuffer(GL_FRAMEBUFFER, _default_framebuffer_id);
    }
    gic_int FrameBuffer::get_default_frame_buffer_id(){
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_default_framebuffer_id);
        return _default_framebuffer_id;
    }
    gic_uint FrameBuffer::get_current_frame_buffer_id() const{
        return _framebuffer_id;
    }
    gic_void FrameBuffer::bind_quad(){
        glBindVertexArray(_quad_vao);//
        //glDrawArrays(GL_TRIANGLE_STRIP, 0, _quad_nums);
        glDrawArrays(GL_TRIANGLES, 0, _quad_nums);
        glBindVertexArray(0);
    }
    
    gic_void FrameBuffer::gen(gic_bool open_render_buffer){
        if (0 == _framebuffer_id){
            glGenFramebuffers(1, &_framebuffer_id);
        }
        get_default_frame_buffer_id();
        glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer_id);
        _open_render_buffer = open_render_buffer;
        gen_texturebuffer();
        gen_renderbuffer();
        assert(GL_NO_ERROR == glGetError());
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            log_printf("ERROR::FrameBuffer:: glCheckFrameBufferStatus is not complete!");
            assert(0);
        }
        bind_default_frame_buffer_id();
    }
    
    gic_void FrameBuffer::gen_quad(){
        gic_float qua_vertices[] = {
            // positions        // texture Coords
/*
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
 */
             -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, // bottom-left
             1.0f, -1.0f,   0.0f,  1.0f, 0.0f, // bottom-right
             1.0f,  1.0f,   0.0f,  1.0f, 1.0f, // top-right
             1.0f,  1.0f,   0.0f,  1.0f, 1.0f, // top-right
             -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, // top-left
             -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, // bottom-left
 
        };
        // setup plane VAO
        _quad_nums = 6;
        glGenVertexArrays(1, &_quad_vao);
        glGenBuffers(1, &_quad_vbo);
        glBindVertexArray(_quad_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _quad_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(qua_vertices), &qua_vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        assert(GL_NO_ERROR == glGetError());
    }
    gic_void FrameBuffer::gen_quad(gic_float* qua_vertices, gic_int nums){
        // setup plane VAO
        if(0 == nums){
            gen_quad();
        }
        else{
            _quad_nums = nums / 5;
            glGenVertexArrays(1, &_quad_vao);
            glGenBuffers(1, &_quad_vbo);
            glBindVertexArray(_quad_vao);
            glBindBuffer(GL_ARRAY_BUFFER, _quad_vbo);
            glBufferData(GL_ARRAY_BUFFER, nums, &qua_vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            assert(GL_NO_ERROR == glGetError());
        }
    }
    
    gic_void FrameBuffer::gen_texturebuffer(){
        assert(nullptr != _ids);
        gic_int counts = _textures.get_tex_counts();
        std::vector<gic_uint> attachments;
        for (gic_int i = 0; i < counts; i++){
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, *(_ids + i), 0);
            attachments.emplace_back(GL_COLOR_ATTACHMENT0 + i);
        }
        if(counts > 1){
            glDrawBuffers(counts, attachments.data());
        }
        
        glBindTexture(GL_TEXTURE_2D, 0);
        assert(GL_NO_ERROR == glGetError());
    }
    gic_void FrameBuffer::gen_renderbuffer(){
        if (_open_render_buffer){
            if (0 == _renderbuffer_id)glGenRenderbuffers(1, &_renderbuffer_id);
            glBindRenderbuffer(GL_RENDERBUFFER, _renderbuffer_id);
            glRenderbufferStorage(GL_RENDERBUFFER,
                                  GL_DEPTH24_STENCIL8,
                                  _textures.get_width(),
                                  _textures.get_height());
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderbuffer_id);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
            assert(GL_NO_ERROR == glGetError());
        }
    }
    gic_void FrameBuffer::release(){
        unbindframe();
    }

}
