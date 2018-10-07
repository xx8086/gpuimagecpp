//
//  out_soul_filter.cpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/12.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "out_soul_filter.hpp"
namespace gpuimagecpp {
    OutSoulFilter::OutSoulFilter(){
        _interval_ms = 500;
        reset_configure();
    }
    
    OutSoulFilter::~OutSoulFilter(){
        ;
    }
    
    gic_void OutSoulFilter::init(const char* filtername, const char* dir){
        std::string strvs(dir);
        std::string strfs(dir);
        strvs.append("default.vsh");
        strfs.append("outsoul.fsh");
        Filter::loadshader(strvs, strfs);
        Filter::init(filtername);
    }
    
    gic_uint OutSoulFilter::render(gic_uint textureid){
        if (0 == _frame_count){
            set_count_time(_interval_ms);
        }
        
        if (count_time()){
            set_count_time(_interval_ms);
            _frame_count = 0;
        }
        
        use();
        set_uniformname_float("ratio", ratio());
        set_uniformname_float("alpha", _alpha);
        textureid = Filter::draw(textureid);
        unuse();
        
        _frame_count++;
        return textureid;
    }
    
    gic_float OutSoulFilter::ratio(){
        gic_int a = _frame_count % _out_soul_frame;
        gic_float b = (gic_float)a / (gic_float)_out_soul_frame;
        return 1 - b; //shader 内部是做图像移动 此值越大 移动越少距离，灵魂就越小
    }
    
    gic_void OutSoulFilter::reset_configure(){
        _alpha = 0.2;
        _out_soul_frame = 30;
    }
    
}
