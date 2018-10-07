//
//  object.hpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/11.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef object_hpp
#define object_hpp
#include "gic_type.hpp"

namespace gpuimagecpp {

    class Object{
    public:
        Object(){};
        virtual ~Object(){};
    public:
        virtual gic_void visible();
        virtual gic_void invisible();
        virtual gic_bool enable();

    protected:
        gic_bool _enble;
    };
    
    class ObjectTime: public Object{
    public:
        ObjectTime(){};
        virtual ~ObjectTime(){};
        virtual gic_float interval_ms() = 0;
        virtual gic_void set_count_time(gic_int ms) = 0;
        virtual gic_bool count_time() = 0;
        virtual gic_bool count_time_loop() = 0;
    };
    
    class ObjectFrameBuffer: public Object{
    public:
        ObjectFrameBuffer(){};
        virtual ~ObjectFrameBuffer(){};
        virtual gic_uint get_texture_buffer_id(gic_int texture_index = 0) = 0;
        virtual gic_bool bind_texture_buffer_id(gic_uint texture_unit) = 0;
        virtual gic_void bind_quad() = 0;
        virtual gic_void bind_frame_buffer_id() = 0;
        virtual gic_void bind_default_frame_buffer_id() = 0;
        virtual gic_int  get_default_frame_buffer_id() = 0;
    };
    
    class ObjectShader: public Object{
    public:
        ObjectShader(){}
        virtual ~ObjectShader(){};
        virtual gic_void use() = 0;
        virtual gic_void unuse() = 0;
        virtual gic_void setbool(const gic_char *name, gic_bool value) const = 0;
        virtual gic_void setint(const gic_char *name, gic_int value) const = 0;
        virtual gic_void setfloat(const gic_char *name, gic_float value) const = 0;
        virtual gic_void setvec2(const gic_char *name, gic_float x, gic_float y) const = 0;
        virtual gic_void setvec3(const gic_char *name, gic_float x, gic_float y, gic_float z) const = 0;
        virtual gic_void setmat4(const gic_char *name, const Mat4f &mat, gic_bool transpose = true) const = 0;
    };
    
}

#endif /* object_hpp */
