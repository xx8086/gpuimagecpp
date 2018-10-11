//
//  usefont.hpp
//  PipeLineCPP
//
//  Created by liu on 2018/9/28.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef usefont_hpp
#define usefont_hpp
#include "freetype2/ft2build.h"
#include "freetype2/freetype/ftglyph.h"
#include <string>
#include <map>
    
    class   Character
    {
    public:
        Character()
        {
            x0          =   0;
            y0          =   0;
            x1          =   0;
            y1          =   0;
            offsetX     =   0;
            offsetY     =   0;
        }
        /**
         *   存储当前字符在纹理上的坐标位置
         */
        
        unsigned int   x0:10;
        unsigned int   y0:10;
        unsigned int   x1:10;
        unsigned int   y1:10;
        unsigned int   offsetX:10;
        unsigned int   offsetY:10;
    };
    struct Worlds{
        Worlds();
        ~Worlds();
        void operator=(const Worlds& other);
        void release();
        void memcpbuffer(const unsigned char* src);
        //wchar_t world;
        int width = 0;
        int rows = 0;
        int pitch = 0;
        unsigned char* buffer = nullptr;
    };
    class float5
    {
    public:
        float   x,y,z;
        float   u,v;
    };
    
    
    class TextureFont{
    public:
        ~TextureFont();
        TextureFont(const char* fontFile,int fontSize);
        void draw_worlds(float x, float y, std::wstring worlds);
        unsigned int get_texture_id();
        void clear_texture();
    private:
        void release();
        Worlds find_world(wchar_t ch);
        void  getCharacter(wchar_t ch);
    protected:
        FT_Library  _library;
        FT_Face     _face;
        unsigned int _textureId;
        int         _yStart;
        int         _xStart;
        int         _fontSize;
        std::map<wchar_t, Worlds> _worlds;
        unsigned char* _buffer = nullptr;
    };

#endif /* usefont_hpp */
