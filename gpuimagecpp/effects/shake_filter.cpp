//
//  shake_filter.cpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/13.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "shake_filter.hpp"
namespace gpuimagecpp {
    ShakeFilter::ShakeFilter(){
        _interval_ms = 500;
        reset_configure();
    }
    
    ShakeFilter::~ShakeFilter(){
        ;
    }
    
    gic_uint ShakeFilter::render(gic_uint textureid){
        if (count_time()){
            if (!_is_shake_out) {
                _ratio = 0.0f;
            }
            _is_shake_out = !_is_shake_out;
            set_count_time(_interval_ms);
        }
        
        if (_is_shake_out) {
            _ratio += 0.02;
            _ratio = _ratio > 0.3 ? 0.3 : _ratio;
        } else {
            _ratio -= 0.02;
            _ratio = _ratio < 0 ? 0 : _ratio;
        }
        
        use();
        set_uniformname_float("ratio", 1.0 - _ratio);
        textureid = Filter::draw(textureid);
        unuse();
        return textureid;
    }
    gic_void ShakeFilter::init(const char* filtername, const char* dir){
        std::string strvs(dir);
        std::string strfs(dir);
        strvs.append("default.vsh");
        strfs.append("shake.fsh");
        Filter::loadshader(strvs, strfs);
        use();
        set_uniformname_int("inputImageTexture", 0);
        unuse();
        Filter::init(filtername);
    }
    gic_void ShakeFilter::reset_configure(){
        
        _is_shake_out = true;
        _ratio = 0.0f;
        //_shake_frame = 40;
        //_frame_count = 0;
    }
}
