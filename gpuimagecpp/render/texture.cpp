//
//  texture.cpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/10.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "texture.hpp"
#include "stb_image.h"
#include "stb_image_write.h"
#include <assert.h>

namespace gpuimagecpp {
    
    TextureOptions::TextureOptions():
    min_filter(GL_LINEAR),
    mag_filter(GL_LINEAR),
    wrap_s(GL_CLAMP_TO_EDGE),
    wrap_t(GL_CLAMP_TO_EDGE),
    internal_format(GL_RGBA),
    format(GL_RGBA),
    type(GL_UNSIGNED_BYTE){

    }
    
    TextureGL::TextureGL(){
        ;
    }
    
    TextureEmpty::TextureEmpty(){
        ;
    }
    
    TextureGL::~TextureGL(){
        release();
    }
    
    
    TextureEmpty::~TextureEmpty(){
        release();
    }
    
    gic_uint Texture::get_texture(gic_int index) const{
        return 0;
    }
    
    gic_int Texture::get_width() const{
        return _size.width;
    }
    gic_int Texture::get_height() const{
        return _size.height;
    }
    
    gic_void Texture::save_bmp(const gic_char* path, gic_byte* images){
        stbi_write_bmp(path, _size.width, _size.height, 4, images);
    }
    
    gic_uint TextureEmpty::get_texture(gic_int index) const{
        if (nullptr != _ids && index >=0 && index < _tetx_count){
            return _ids[index];
        }
        return 0;
    }
    
    gic_int TextureEmpty::get_tex_counts() const{
        return _tetx_count;
    }
    
    gic_uint TextureGL::get_texture(gic_int index) const{
        return _texture_id;
    }
    
    gic_void TextureGL::release(){
        if (0 != _texture_id){
            glDeleteTextures(1, &_texture_id);
            _texture_id = 0;
        }
    }

    gic_void TextureEmpty::release(){
        if (0 < _tetx_count){
            glDeleteTextures(_tetx_count, _ids);
            GIC_DELETE_ARRY_PTR(_ids)
            _tetx_count = 0;
        }
    }
    
    gic_uint* TextureEmpty::resize(gic_int w, gic_int h){
        _size.width = w;
        _size.height = h;
        return make_empty_texture();
    }
    
    gic_void TextureEmpty::set_options(const TextureOptions& options){
        _options = options;
    }
    
    gic_void TextureEmpty::set_counts(gic_int counts){
        _tetx_count = counts;
    }
    
    gic_void TextureGL::bind(gic_uint texture_unit){
        glActiveTexture(texture_unit);
        glBindTexture(GL_TEXTURE_2D, _texture_id);
    }
    
    gic_uint TextureGL::load_texture(const gic_char* path, gic_bool gammar){
        assert(nullptr != path);
        gic_int components;
        gic_uchar *data = stbi_load(path, &_size.width, &_size.height, &components, 0);
        assert(nullptr != data);
        texture_format(components, gammar);
        make_texture(data);
        stbi_image_free(data);
        
        return _texture_id;
    }
    
    gic_uint* TextureEmpty::make_empty_texture(){
        assert(_tetx_count > 0);
        if (nullptr != _ids){
            glDeleteTextures(_tetx_count, _ids);
            GIC_DELETE_ARRY_PTR(_ids)
        }
        _ids = new gic_uint[_tetx_count];
        glGenTextures(_tetx_count, _ids);
        for (unsigned int i = 0; i < _tetx_count; i++) {
            glBindTexture(GL_TEXTURE_2D, _ids[i]);
            glTexImage2D(GL_TEXTURE_2D,
                         0,
                         _options.internal_format,
                         _size.width,
                         _size.height,
                         0,
                         _options.format,
                         _options.type,
                         nullptr);
            assert(GL_NO_ERROR == glGetError());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _options.wrap_s);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _options.wrap_t);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _options.min_filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _options.mag_filter);
        }
        assert(GL_NO_ERROR == glGetError());
        return _ids;
    }

    gic_uint TextureGL::make_texture(gic_uchar *data){
        glGenTextures(1, &_texture_id);
        glBindTexture(GL_TEXTURE_2D, _texture_id);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     _options.internal_format,
                     _size.width,
                     _size.height,
                     0,
                     _options.format,
                     _options.type,
                     nullptr);
        assert(GL_NO_ERROR == glGetError());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _options.wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _options.wrap_t);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _options.min_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _options.mag_filter);
        return _texture_id;
    }
    
    gic_void TextureGL::texture_format(gic_int format, gic_bool gammar){
        switch (format) {
            case 1:
                _options.format = GL_LUMINANCE;
                _options.internal_format = GL_LUMINANCE;//GL_RED
                _options.type = GL_UNSIGNED_BYTE;
                break;
            case 3:
                _options.format = GL_RGB;
                _options.internal_format = gammar ? GL_RGB : GL_RGB;//GL_SRGB
                _options.type = GL_UNSIGNED_BYTE;
                break;
            case 4:
                _options.format = GL_RGBA;
                _options.internal_format = gammar ? GL_RGBA : GL_RGBA;//GL_SRGB
                _options.type = GL_UNSIGNED_BYTE;
                break;
            default:
                break;
        }
    }
}
