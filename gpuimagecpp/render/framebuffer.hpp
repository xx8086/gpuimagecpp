//
//  framebuffer.hpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/10.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef FrameBuffer_hpp
#define FrameBuffer_hpp
#include "../bridge/object.hpp"
#include "texture.hpp"

namespace gpuimagecpp {
    
    class FrameBuffer: public ObjectFrameBuffer{
    public:
        FrameBuffer();
        virtual ~FrameBuffer();

    public:
        gic_void set_texture(const GicSize& fsize, gic_int counts = 1);
        gic_void set_texture_options(const TextureOptions& options);
        gic_void resize(gic_int width, gic_int height);
        gic_int get_default_frame_buffer_id();
        gic_uint get_current_frame_buffer_id() const;
        gic_byte* get_bytes(gic_int texture_index = 0);
        gic_void save_bmp(const char* path, gic_byte* datas);
    public:
        virtual gic_uint get_texture_buffer_id(gic_int texture_index = 0);
        virtual gic_bool bind_texture_buffer_id(gic_uint texture_unit);
        virtual gic_void bind_quad();
        virtual gic_void bind_frame_buffer_id();
        gic_void bind_render_buffer_id();
        gic_void bind_default_frame_buffer_id();
        gic_void gen(gic_bool open_render_buffer = false);
        gic_void gen_quad(gic_float* , gic_int nums);
    private:
        gic_bool get_pixels_from_framebuffers(gic_uint gltex, gic_void* dataPtr, gic_int width, gic_int height);
        gic_void gen_quad();
        gic_void gen_texturebuffer();
        gic_void gen_renderbuffer();
        gic_void unbindframe();
        gic_void release();
        
    private:
        TextureEmpty _textures;
        gic_bool _open_render_buffer = true;
        gic_uint* _ids = nullptr;
        gic_byte* _images = nullptr;
        gic_uint _framebuffer_id = 0;
        gic_uint _renderbuffer_id = 0;
        gic_int _default_framebuffer_id = 0;
        gic_int _quad_nums = 0;
        gic_uint _quad_vao;
        gic_uint _quad_vbo;
    };
}
#endif /* FrameBuffer_hpp */

