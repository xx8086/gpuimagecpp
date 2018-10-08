//
//  font_filter.cpp
//  PipeLineCPP
//
//  Created by liu on 2018/9/28.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "font_filter.hpp"

namespace gpuimagecpp {
    FontFilter::FontFilter(){
        _interval_ms = 1000;
    }
    
    FontFilter::~FontFilter(){
        if(nullptr != _font){
            delete _font;
            _font = nullptr;
        }
    }
    
    gic_void FontFilter::reset_configure(){
        ;
    }
    
    gic_uint FontFilter::render(gic_uint textureid){
        _font->set_texture_id(textureid);
        if (count_time()){
            switch(_sign){
                case 0:
                    _sign =  1;
                    break;
                case 1:
                    _sign =  2;
                    break;
                case 2:
                    _sign =  3;
                    break;
                case 3:
                    _sign =  0;
                    break;
                default:
                    break;
            }
            set_count_time(_interval_ms);
        }
        switch(_sign){
            case 0:
                _font->drawText(150, 1100, L"科大讯飞@！#123ABCEfg");
                break;
            case 1:
                _font->drawText(150, 1100, L"发财致富奔小康");
                break;
            case 2:
                _font->drawText(150, 1100, L"你好啊哈哈哈哈");
                break;
            case 3:
                _font->drawText(150, 1100, L"牛奶盒子");
                break;
                default:
                break;
        }
        
        return _font->get_texture_id();
    }
    gic_void FontFilter::init(const char* filtername, const char* dir){
        std::string strttf(dir);
        strttf.append("hz.ttc");
        GLenum err1 = glGetError();
        _font = new TextureFont(strttf.c_str(), 56);
        
        Filter::init(filtername);
    }
}
