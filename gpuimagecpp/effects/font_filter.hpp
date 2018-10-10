//
//  font_filter.hpp
//  PipeLineCPP
//
//  Created by liu on 2018/9/28.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef font_filter_hpp
#define font_filter_hpp
#include "../bridge/filter.hpp"
#include "usefont.hpp"

namespace gpuimagecpp {
    class FontFilter: public Filter{
    public:
        FontFilter();
        virtual ~FontFilter();
    public:
        gic_uint render(gic_uint textureid);
        gic_void init(const char* filtername, const char* dir);
        gic_void reset_configure();
    private:
        TextureFont*    _font;
        gic_int _sign = 0;

        Vec2f _world_pos;
        Vec3f _world_color;
        std::wstring _str_worlds;
    };
}

#endif /* font_filter_hpp */
