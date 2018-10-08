//
//  shader.hpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/10.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp
#include "gic_gl.h"
#include "../bridge/object.hpp"
#include <string>

namespace gpuimagecpp {
    class Shader: public ObjectShader{
    public:
        Shader();
        ~Shader();
    public:
        std::string loadfile(const gic_char* file);
        GLboolean loadshader(std::string vs, std::string fs);
        GLboolean loadshader(const gic_char* dir, const gic_char* vs_file_name, const gic_char* fs_file_name);
        const GLuint& programid() const;
        gic_int getuniformlocation(const gic_char* name);
        gic_void use();
        gic_void unuse();
        
        gic_void setbool(const gic_char *name, gic_bool value) const;
        gic_void setfloat(const gic_char *name, gic_float value) const;
        gic_void setint(const gic_char *name, gic_int value) const;
        gic_void setvec2(const gic_char *name, gic_float x, gic_float y) const;
        gic_void setvec3(const gic_char *name, const Vec3f& v3) const;
        gic_void setvec3(const gic_char *name, gic_float x, gic_float y, gic_float z) const;
        gic_void setvec4(const gic_char *name, gic_float x, gic_float y, gic_float z, gic_float w) const;
        gic_void setmat4(const gic_char *name, const Mat4f &mat, gic_bool transpose = true) const;
        gic_void setmat4(const gic_uint localid, const Mat4f &mat, gic_bool transpose = true) const;
        gic_void set_attrib_location(const gic_char *name, gic_int i);
    private:
        GLboolean loadshader(const gic_char* vs, const gic_char* fs);
        GLuint loadshader(GLenum type, const gic_char *shader_src);
    private:
        GLuint _program = 0;
    };
}

#endif /* shader_hpp */
