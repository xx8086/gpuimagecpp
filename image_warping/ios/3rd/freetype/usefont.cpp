//
//  usefont.cpp
//  PipeLineCPP
//
//  Created by liu on 2018/9/28.
//  Copyright © 2018年 hanliu. All rights reserved.
//
#include "usefont.hpp"
#include <math.h>
#include <assert.h>

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

#define FONT_WIDTH (720)
#define FONT_HIGHT (1280)
    Worlds::Worlds(){
        ;
    }
    Worlds::~Worlds(){
        width = 0;
        rows = 0;
        pitch = 0;
    }
    
    void Worlds::operator=(const Worlds& other){
        this->buffer = other.buffer;
        this->pitch = other.pitch;
        this->rows = other.rows;
        this->width = other.width;
    }
    void Worlds::release(){
        if (nullptr != buffer){
            delete [] buffer;
            buffer = nullptr;
        }
    }
    
    void Worlds::memcpbuffer(const unsigned  char* src){
        release();
        buffer = new unsigned char[width * rows * 4];
        memcpy(buffer, src, width * rows);
    }
    
    TextureFont::~TextureFont(){
        if (nullptr != _buffer){
            delete [] _buffer;
            _buffer = nullptr;
        }
        release();
    }
    void TextureFont::release(){
        for(auto iter = _worlds.begin();
            iter != _worlds.end();
            iter++){
            iter->second.release();
        }
        _worlds.clear();
    }
    
    TextureFont::TextureFont(const char* fontFile,int fontSize){
        release();
        
        _fontSize   =   fontSize;
        _xStart     =   0;
        _yStart     =   0;
        
        FT_Init_FreeType( &_library );
        assert(_library != 0 );
        
        FT_New_Face(_library,fontFile, 0, &_face);
        //FT_Set_Char_Size( _face, _fontSize << 6, _fontSize << 6, 72, 72);
        FT_Set_Pixel_Sizes(_face, _fontSize, 0);
        assert(_face != 0 );
        
        glGenTextures(1, &_textureId);
        glBindTexture(GL_TEXTURE_2D, _textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     FONT_WIDTH,
                     FONT_HIGHT,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     nullptr);
        assert(GL_NO_ERROR == glGetError());
        glBindTexture(GL_TEXTURE_2D, 0);
        _buffer = new unsigned char[FONT_WIDTH * FONT_HIGHT * 4];
        memset(_buffer, 0, sizeof(unsigned char) * FONT_WIDTH * FONT_HIGHT * 4);
    }
    
    void TextureFont::clear_texture(){
        glBindTexture(GL_TEXTURE_2D, _textureId);
        glTexSubImage2D(GL_TEXTURE_2D,
                        0,
                        0,
                        0,
                        FONT_WIDTH,
                        FONT_HIGHT,
                        GL_RGBA,
                        GL_UNSIGNED_BYTE,
                        _buffer);
    }
    
    Worlds TextureFont::find_world(wchar_t ch){
        Worlds world;
        auto iter = _worlds.find(ch);
        if(_worlds.end() != iter){
            world = iter->second;
        }
        else if (_worlds.end() == iter){//没有的字重新生成
            FT_Load_Glyph(_face, FT_Get_Char_Index(_face, ch), FT_RENDER_MODE_NORMAL);//
            FT_Glyph glyph;
            FT_Get_Glyph(_face->glyph, &glyph);
            //FT_Render_Glyph(_face->glyph, FT_RENDER_MODE_NORMAL);
            FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
            FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
            FT_Bitmap& bitmap = bitmap_glyph->bitmap;
            if (bitmap.width != 0 || bitmap.rows != 0){
                world.pitch = bitmap.pitch;
                world.rows = bitmap.rows;
                world.width = bitmap.width;
                world.memcpbuffer(bitmap.buffer);
                for (int j = 0; j < bitmap.width; j++) {
                    for (int i = 0; i < bitmap.rows; i++) {
                        unsigned char aph = bitmap.buffer[i*world.pitch + j/*(world - j - 1)*/];
                        world.buffer[world.width * i * 4 + j * 4 + 0] = aph;
                        world.buffer[world.width * i * 4 + j * 4 + 1] = aph;
                        world.buffer[world.width * i * 4 + j * 4 + 2] = 0;
                        world.buffer[world.width * i * 4 + j * 4 + 3] = aph;
                    }
                }
                
                auto insert_iter = _worlds.emplace(std::make_pair(ch, world));
                if (!insert_iter.second){
                    world.release();
                }
            }
        }
        
        return world;
    }
    
    void TextureFont::getCharacter(wchar_t ch){
        if (_xStart + _fontSize > FONT_WIDTH){
            _xStart = 0;
            _yStart += _fontSize;
        }
        
        Worlds world = find_world(ch);
        if(world.width != 0 || world.rows != 0){
            glBindTexture(GL_TEXTURE_2D, _textureId);
            //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexSubImage2D(GL_TEXTURE_2D,
                            0,
                            _xStart,
                            _yStart + (_fontSize - world.rows),
                            world.width,
                            world.rows,
                            GL_RGBA,
                            GL_UNSIGNED_BYTE,
                            world.buffer);
            _xStart += world.width + 1;
        }else{
            _xStart += _fontSize / 2;
        }
        
    }
    
    void TextureFont::draw_worlds(float x, float y, std::wstring worlds) {
        _xStart = x;
        _yStart = y;
        int len = worlds.size();
        for (int i = 0; i < len; i++){
            getCharacter(worlds[i]);
        }
    }
    
    unsigned int TextureFont::get_texture_id(){
        return _textureId;
    }
