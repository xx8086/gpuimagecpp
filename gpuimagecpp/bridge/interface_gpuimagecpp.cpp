//
//  interface_gpuimagecpp.cpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/14.
//  Copyright © 2018年 hanliu. All rights reserved.
//
#include "../../PipeLineCPP/interface_gpuimagecpp.hpp"
#include "../filters/filters_manage.hpp"
#include "../common/singleton.h"

#include "../effects/mult_window_filter.hpp"
#include "../effects/out_soul_filter.hpp"
#include "../effects/shake_filter.hpp"
#include "../effects/font_filter.hpp"

namespace gpuimagecpp {
    CInterfaceGpuImageCPP::CInterfaceGpuImageCPP(){
        ;
    }
    CInterfaceGpuImageCPP::~CInterfaceGpuImageCPP(){
        ;
    }
    
    bool CInterfaceGpuImageCPP::init(const char* dir){
        ShakeFilter* shake = new ShakeFilter();
        OutSoulFilter* outsoul = new OutSoulFilter();
        MultWindowFilter* mulwindwo = new MultWindowFilter();
        FontFilter* font = new FontFilter();
        
        std::string strdir(dir);
        size_t dirlen = strdir.size();
        if(dirlen > 0 && '/' != strdir.at(dirlen - 1)){
            strdir.append("/");
       }
        
        shake->init("ShakeFilter", strdir.data());
        outsoul->init("OutSoulFilter", strdir.data());
        mulwindwo->init("MultWindowFilter", strdir.data());
        font->init("FontFilter", strdir.data());
                   
        append_filter(shake->get_id());
        append_filter(outsoul->get_id());
        append_filter(mulwindwo->get_id());
        append_filter(font->get_id());
        
        //shake->invisible();
        //outsoul->invisible();
        mulwindwo->invisible();
        return true;
    }
    
    bool CInterfaceGpuImageCPP::resize(const int w, const int h){
        return Singleton<FiltersManage>::get_instance()->resize(w, h);
    }
    unsigned int CInterfaceGpuImageCPP::frame_id(unsigned int index){
        return Singleton<FiltersManage>::get_instance()->frame_id(index);
    }
    unsigned int CInterfaceGpuImageCPP::frame_counts(){
        return Singleton<FiltersManage>::get_instance()->frame_counts();
    }
    unsigned int CInterfaceGpuImageCPP::render(unsigned int textureid,
                                               unsigned int frame_index){
        return Singleton<FiltersManage>::get_instance()->render(textureid);
    }
    
    unsigned char* CInterfaceGpuImageCPP::image_datas(unsigned int textureid){
        return Singleton<FiltersManage>::get_instance()->image_datas(textureid);
    }
    
    unsigned char* CInterfaceGpuImageCPP::frame_texture_datas(unsigned int frameid){
        return Singleton<FiltersManage>::get_instance()->frame_texture_datas(frameid);
    }
    
    void CInterfaceGpuImageCPP::save_bmp(const char* path, unsigned char* datas){
        Singleton<FiltersManage>::get_instance()->save_bmp(path, datas);
    }
    
    bool CInterfaceGpuImageCPP::enable_filter(const unsigned int filterid){
        return Singleton<FiltersManage>::get_instance()->enable_filter(filterid);
    }
    bool CInterfaceGpuImageCPP::disable_filter(const unsigned int filterid){
        return Singleton<FiltersManage>::get_instance()->disable_filter(filterid);
    }
    /*
    Filter* CInterfaceGpuImageCPP::find_filter(const unsigned int filterid) const{
        return Singleton<FiltersManage>::get_instance()->find_filter(filterid);
    }
     */
    void CInterfaceGpuImageCPP::append_filter(const unsigned int filterid){
        Singleton<FiltersManage>::get_instance()->append_filter(filterid);
    }
}
