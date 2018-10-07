//
//  shader.cpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/10.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "shader.hpp"
#include "log.hpp"
#include <fstream>
#include <sstream>

namespace gpuimagecpp {
    Shader::Shader(){
        ;
    }
    
    Shader::~Shader(){
        ;
    }
    
    const GLuint& Shader::programid() const{
        return _program;
    }
    
    GLuint Shader::loadshader(GLenum type, const char *loadshader)
    {
        GLuint shader = 0;
        GLint compiled = 0;
        shader = glCreateShader (type);
        if (0 == shader){
            return 0;
        }
        
        glShaderSource(shader, 1, &loadshader, NULL);
        glCompileShader(shader );
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled){
            GLint info_len = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
            if ( info_len > 1 ){
                char *info_log = (char*)malloc(sizeof(char) * info_len);
                glGetShaderInfoLog (shader, info_len, NULL, info_log);
                log_printf ("Error compiling shader:\n%s\n", info_log);
                free (info_log);
            }
            
            glDeleteShader (shader);
            return 0;
        }
        
        return shader;
    }
    
    GLboolean Shader::loadshader(const char* vs, const char* fs){
        if (nullptr == vs  || nullptr == fs){
            return GL_FALSE;
        }
        
        GLuint vertex_shader = 0;
        GLuint fragment_shader = 0;
        GLuint program_object = 0;
        GLint linked = 0;
        vertex_shader = loadshader(GL_VERTEX_SHADER, vs);
        fragment_shader = loadshader(GL_FRAGMENT_SHADER, fs);
        program_object = glCreateProgram();
        if (0 == program_object){
            return 0;
        }
        glAttachShader(program_object, vertex_shader);
        glAttachShader(program_object, fragment_shader);
        glLinkProgram(program_object);
        glGetProgramiv(program_object, GL_LINK_STATUS, &linked);
        if (!linked){
            GLint info_len = 0;
            glGetProgramiv(program_object, GL_INFO_LOG_LENGTH, &info_len);
            if (info_len > 1){
                char *info_log = (char*)malloc( sizeof(char) * info_len);
                glGetProgramInfoLog (program_object, info_len, NULL, info_log);
                log_printf ("Error linking program:\n%s\n", info_log);
                free (info_log);
            }
            glDeleteProgram (program_object);
            return GL_FALSE;
        }
        
        _program = program_object;
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        return GL_TRUE;
    }
    
    GLboolean Shader::loadshader(std::string vs, std::string fs) {
        std::string vs_content = loadfile(vs.c_str());
        std::string fs_content = loadfile(fs.c_str());
        return loadshader(vs_content.c_str(), fs_content.c_str());
    }
    
    GLboolean Shader::loadshader(const char*dir, const char* vs_file_name, const char* fs_file_name){
        if (nullptr == dir || nullptr == vs_file_name || nullptr == vs_file_name){
            return GL_FALSE;
        }
        std::string strvs(dir);
        std::string strfs(dir);
        strvs.append("/");
        strvs.append(vs_file_name);
        strfs.append("/");
        strfs.append(fs_file_name);
        std::string vs_content = loadfile(strvs.c_str());
        std::string fs_content = loadfile(strfs.c_str());
        return loadshader(vs_content.c_str(), fs_content.c_str());
    }
    
    std::string Shader::loadfile(const char* file){
        std::string strcontent;
        if(nullptr != file){
            std::ifstream t(file);
            if(t){
                std::stringstream buffer;
                buffer << t.rdbuf();
                strcontent = buffer.str();
                t.close();
            }
        }
        return strcontent;
    }
    // activate the shader
    // ------------------------------------------------------------------------
    void Shader::use(){
        glUseProgram(_program);
    }
    
    void Shader::unuse(){
        glUseProgram(0);
    }
    
    int Shader::getuniformlocation(const char* name){
        return glGetUniformLocation(_program, name);
    }
    
    gic_void Shader::set_attrib_location(const gic_char *name, gic_int i){
        glBindAttribLocation(_program, i, name);
    }
    
    gic_void Shader::setbool(const gic_char *name, gic_bool value) const{
        glUniform1i(glGetUniformLocation(_program, name), value);
    }
    gic_void Shader::setfloat(const gic_char *name, gic_float value) const{
        glUniform1f(glGetUniformLocation(_program, name), value);
    }
    gic_void Shader::setint(const gic_char *name, gic_int value) const{
        glUniform1i(glGetUniformLocation(_program, name), value);
    }
    gic_void Shader::setvec2(const gic_char *name, gic_float x, gic_float y) const{
        glUniform2f(glGetUniformLocation(_program, name), x, y);
    }
    gic_void Shader::setvec3(const gic_char *name, const Vec3f& v3) const{
        glUniform3f(glGetUniformLocation(_program, name), v3.x, v3.y, v3.z);
    }
    
    gic_void Shader::setvec3(const gic_char *name, gic_float x, gic_float y, gic_float z) const{
        glUniform3f(glGetUniformLocation(_program, name), x, y, z);
    }
    gic_void Shader::setvec4(const gic_char *name, gic_float x, gic_float y, gic_float z, gic_float w) const{
        glUniform4f(glGetUniformLocation(_program, name), x, y, z, w);
    }
    
    gic_void Shader::setmat4(const gic_char *name, const Mat4f &mat, gic_bool transpose) const{
        glUniformMatrix4fv(glGetUniformLocation(_program, name), 1, transpose, (const GLfloat*)mat.m);
    }
    
    gic_void Shader::setmat4(const gic_uint localid, const Mat4f &mat, gic_bool transpose) const{
        glUniformMatrix4fv(localid, 1, transpose, (const GLfloat*)mat.m);
    }
}
