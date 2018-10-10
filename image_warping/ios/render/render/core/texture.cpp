//
//  texture.cpp
//  render
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <OpenGLES/ES3/gl.h>

void TexureGl::bind(unsigned int texture_unit){
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_2D, _texture_id);
}

void free_datas(unsigned char* data){
    if (nullptr != data){
        stbi_image_free(data);
    }
}

unsigned char* TexureGl::load_texture(const std::string &filename, int& width, int& height, int& components){
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &components, 0);
    if (nullptr != data){
        if (components == 1)
            _format = GL_RED;
        else if (components == 3)
            _format = GL_RGB;
        else if (components == 4)
            _format = GL_RGBA;
    }
    
    return data;
}

int TexureGl::get_width() const{
    return _width;
}
int TexureGl::get_height() const{
    return _height;
}
unsigned int TexureGl::get_texture_id() const{
    return _texture_id;
}

unsigned int TexureGl::load_texture(const std::string &filename, bool gamma){
    //std::string filename = std::string(path);
    //filename = directory + '/' + filename;
    
    unsigned int texture_id;
    glGenTextures(1, &texture_id);
    
    int components;
    unsigned char *data = stbi_load(filename.c_str(), &_width, &_height, &components, 0);
    if (nullptr != data){
        if (components == 1)
            _format = GL_RED;
        else if (components == 3)
            _format = GL_RGB;
        else if (components == 4)
            _format = GL_RGBA;
        
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, _format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    }
    else{
        printf("Texture failed to load at path: %s\n", path.c_str());
    }
    
    _texture_id = texture_id;
    return texture_id;
}
