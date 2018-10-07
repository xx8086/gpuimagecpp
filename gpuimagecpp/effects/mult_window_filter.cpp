//
//  mult_window_filter.cpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/12.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "mult_window_filter.hpp"

namespace gpuimagecpp {
    MultWindowFilter::MultWindowFilter(){
        _interval_ms = 1000;
        reset_configure();
    }
    
    MultWindowFilter::~MultWindowFilter(){
        ;
    }
    
    gic_void MultWindowFilter::reset_configure(){
        _window_count = 1;
    }
    gic_void MultWindowFilter::init(const char* filtername, const char* dir){
        std::string strvs(dir);
        std::string strfs(dir);
        strvs.append("default.vsh");
        strfs.append("mult_window.fsh");
        Filter::loadshader(strvs, strfs);
        Filter::init(filtername);
    }
    
    gic_uint MultWindowFilter::render(gic_uint textureid){
        if (count_time()){
            switch_window();
            set_count_time(_interval_ms);
        }
        
        use();
        set_uniformname_int("window_counts", _window_count);
        textureid = Filter::draw(textureid);
        unuse();
        
        return textureid;
    }
    
    gic_void MultWindowFilter::switch_window(){
        switch(_window_count){
            case 1:
                _window_count = 4;
                break;
            case 4:
                _window_count = 9;
                break;
            case 9:
                _window_count = 1;
                break;
            default:
                _window_count = 1;
                break;
        }
    }
}
