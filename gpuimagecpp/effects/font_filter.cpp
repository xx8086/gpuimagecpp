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
        
        std::wstring strcon;
        switch(_sign){
            case 0:
                strcon = L"科大讯飞@！#123ABCEfg";
                break;
            case 1:
                strcon = L"发财致富，奔小康";
                break;
            case 2:
                strcon = L"你好啊哈哈哈哈";
                break;
            case 3:
                strcon = L"牛奶盒子";
                break;
                default:
                break;
        }
        _font->clear_texture();
        _font->drawText(100, 1000, strcon);
        use();
        textureid = Filter::draw(textureid);
        unuse();
        
        return textureid;
    }
    
    gic_void FontFilter::init(const char* filtername, const char* dir){
        std::string strvs(dir);
        std::string strfs(dir);
        strvs.append("default.vsh");
        strfs.append("font.fsh");
        Filter::loadshader(strvs, strfs);
        Filter::init(filtername);
        
        std::string strttf(dir);
        strttf.append("hz.ttc");
        _font = new TextureFont(strttf.c_str(), 56);
        append_texture_x(_font->get_texture_id());
        use();
        set_uniformname_int("inputImageTexture", 0);
        set_uniformname_int("worlds_texture", 1);
        unuse();
    }
}
