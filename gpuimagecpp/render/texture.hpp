//
//  texture.hpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/10.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef texture_hpp
#define texture_hpp
#include "texture_options.h"
#include "../bridge/gic_type.hpp"
#include "gic_gl.h"

namespace gpuimagecpp {    
    class Texture{
    public:
        Texture(){};
        virtual ~Texture(){};
        virtual gic_uint get_texture(gic_int index = 0) const;
        gic_int get_width() const;
        gic_int get_height() const;
        gic_void save_bmp(const gic_char* path, gic_byte* images);
    protected:
        TextureOptions _options;
        GicSize _size;
    };
    
    class TextureEmpty : public Texture{
    public:
        TextureEmpty();
        virtual ~TextureEmpty();
        virtual gic_uint get_texture(gic_int index = 0) const;
    public:
        gic_void release();
        gic_void set_counts(gic_int counts);
        gic_int get_tex_counts() const;
        gic_void set_options(const TextureOptions& options);
        gic_uint* resize(gic_int w, gic_int h);
    private:
        gic_uint* make_empty_texture();
    private:
        gic_uint* _ids = nullptr;
        gic_int _tetx_count = 0;
    };
    
    class TextureGL: public Texture{
    public:
        TextureGL();
        virtual ~TextureGL();
        virtual gic_uint get_texture(gic_int index = 0) const;
    public:
        gic_void release();
        gic_void bind(gic_uint texture_unit);
        gic_uint load_texture(const gic_char* path, gic_bool gammar = false);
        
    private:
        gic_uint make_texture(gic_uchar *data);
        gic_void texture_format(gic_int format, gic_bool gammar);
    private:
        gic_uint _texture_id = 0;
    };
}
#endif /* texture_hpp */
