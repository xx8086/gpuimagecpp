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

namespace gpuimagecpp {
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
    
    void TextureFont::set_texture_id(unsigned int texid){
        _textureId = texid;
    }
    
    TextureFont::~TextureFont(){
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
        FT_Set_Char_Size( _face, fontSize << 6, fontSize << 6, 72, 72);
        assert(_face != 0 );
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
            
            FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
            FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
            FT_Bitmap& bitmap = bitmap_glyph->bitmap;
            if (bitmap.width != 0 || bitmap.rows != 0){
                //bitmap_glyph->top;
                //bitmap_glyph->left;
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
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexSubImage2D(GL_TEXTURE_2D,
                            0,
                            _xStart,
                            _yStart,
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
    
    void TextureFont::drawText(float x, float y, std::wstring text) {
        _xStart = x;
        _yStart = y;
        int len = text.size();
        for (int i = 0; i < len; i++){
            getCharacter(text[i]);
        }
    }
    
    unsigned int TextureFont::get_texture_id(){
        return _textureId;
    }
}
