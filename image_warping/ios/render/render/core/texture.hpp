//
//  texture.hpp
//  render
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef texture_hpp
#define texture_hpp

#include "type_render.h"
#include <string>

struct Vertex {
    Vec3f Position;
    Vec3f Normal;
    Vec2f TexCoords;
    Vec3f Tangent;
    Vec3f Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class TexureGl: protected Texture{
public:
    void bind(unsigned int texture_unit);
    void free_datas(unsigned char*);
    unsigned char* load_texture(const std::string &filename, int&, int&, int&);
    unsigned int load_texture(const std::string &filename, bool gamma = false);
    int get_width() const;
    int get_height() const;
    unsigned int get_texture_id() const;
private:
    int _width;
    int _height;
    unsigned int _texture_id;
    unsigned int _format;
};

#endif /* texture_hpp */
