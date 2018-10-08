//
//  filter.hpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/11.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef filter_hpp
#define filter_hpp
#include "object.hpp"
#include <string>

namespace gpuimagecpp {
    class Filter: public Object{
    public:
        //Filter(const char*);
        Filter();
        virtual ~Filter();
    public:
        virtual gic_void init(const char* filtername, const char* dir) = 0;
        virtual gic_uint render(gic_uint textureid) = 0;//子类都要自己实现render
        virtual gic_void begin_draw();
        virtual gic_void end_draw();
        virtual gic_uint draw(gic_uint textureid);
        virtual gic_void reset_configure(){};
        
    public:
        gic_void resize(gic_int w, gic_int h);
        gic_void init(const char*, gic_float* = nullptr, gic_int = 0);
        gic_void use();
        gic_void unuse();
        gic_uint get_frameid();
        gic_uint get_texturid(gic_int texture_index = 0);
        gic_byte* get_bytes(gic_int texture_index = 0);
        gic_void save_bmp(const gic_char* path, gic_byte* datas);
        gic_uint get_id()const;
    public:
        gic_void set_count_time(int ms);
        gic_bool count_time();
        gic_bool count_time_loop();
        gic_bool loadshader(std::string vs, std::string fs);
        gic_void set_uniformname_bool(const gic_char*, gic_bool);
        gic_void set_uniformname_int(const gic_char*, gic_int);
        gic_void set_uniformname_float(const gic_char*, gic_float);
        gic_void set_uniformname_float2(const gic_char*, gic_float, gic_float);
        gic_void set_uniformname_float3(const gic_char*, gic_float, gic_float, gic_float);
        gic_void set_uniformname_mat4f(const gic_char*, const Mat4f&);
    private:
        gic_void release();
    protected:
        gic_uint _interval_ms = 0;//间隔毫秒
    private:
        gic_uint _hash_id;
        ObjectShader* _shader = nullptr;
        ObjectTime* _timer = nullptr;
        ObjectFrameBuffer* _framebuffer = nullptr;
    };
}

#endif /* filter_hpp */
