//
//  filter.cpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/11.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "../bridge/filter.hpp"
#include "../common/singleton.h"
#include "../render/shader.hpp"
#include "../render/framebuffer.hpp"
#include "../common/timer.hpp"
#include "filters_manage.hpp"

namespace gpuimagecpp {
    Filter::Filter(){
        visible();
        release();
        _timer = new Timer();
        _shader = new Shader();
        _framebuffer = new FrameBuffer();
    }
    
    Filter::~Filter(){
        release();
    }
    
    gic_void Filter::release(){
        GIC_DELETE_PTR(_shader)
        GIC_DELETE_PTR(_framebuffer)
        GIC_DELETE_PTR(_timer)
    }
    
    gic_void Filter::init(const char* filtername){
        dynamic_cast<FrameBuffer*>(_framebuffer)->set_texture(GicSize(1280,720));//640, 1136
        dynamic_cast<FrameBuffer*>(_framebuffer)->gen();
        
        std::hash<std::string> strhash;
        _hash_id = static_cast<gic_uint>(strhash(filtername));//2018.0910.每个filtername对应一个id,便于更高速的find
        Singleton<FiltersManage>::get_instance()->insert_filter(_hash_id, this);
    }
    gic_void Filter::resize(gic_int w, gic_int h){
        if (nullptr != _framebuffer){
            dynamic_cast<FrameBuffer*>(_framebuffer)->resize(w, h);
        }
    }
    
    gic_void Filter::begin_draw(){
        
    }
    gic_void Filter::end_draw(){
        
        
    }
    gic_uint Filter::draw(gic_uint textureid){
        _framebuffer->get_default_frame_buffer_id();
        _framebuffer->bind_frame_buffer_id();
        _framebuffer->bind_texture_buffer_id(textureid);
        _framebuffer->bind_quad();
        _framebuffer->bind_default_frame_buffer_id();
        return _framebuffer->get_texture_buffer_id();
    }
    
    gic_void Filter::set_count_time(int ms){
        _timer->set_count_time(ms);
    }
    
    gic_bool Filter::count_time(){
        return _timer->count_time();
    }
    
    gic_bool Filter::count_time_loop(){
        return _timer->count_time_loop();
    }
    
    gic_bool Filter::loadshader(std::string vs, std::string fs){
        return dynamic_cast<Shader*>(_shader)->loadshader(vs, fs);
    }
    
    gic_void Filter::use(){
        _shader->use();
    }
    gic_void Filter::unuse(){
        _shader->unuse();
    }
    
    gic_void Filter::set_uniformname_bool(const gic_char* name, gic_bool value){
        _shader->setbool(name, value);
    }
    gic_void Filter::set_uniformname_int(const gic_char* name, gic_int value){
        _shader->setint(name, value);
    }
    gic_void Filter::set_uniformname_float(const gic_char* name, gic_float value){
        _shader->setfloat(name, value);
    }
    gic_void Filter::set_uniformname_float2(const gic_char* name, gic_float v1, gic_float v2){
        _shader->setvec2(name, v1, v2);
    }
    gic_void Filter::set_uniformname_float3(const gic_char* name, gic_float v1, gic_float v2, gic_float v3){
        _shader->setvec3(name, v1, v2, v3);
    }
    gic_void Filter::set_uniformname_mat4f(const gic_char* name, const Mat4f& mat){
        _shader->setmat4(name, mat);
    }
    
    gic_uint Filter::get_frameid(){
        return dynamic_cast<FrameBuffer*>(_framebuffer)->get_current_frame_buffer_id();
    }
    gic_byte* Filter::get_bytes(gic_int texture_index){
        return dynamic_cast<FrameBuffer*>(_framebuffer)->get_bytes(texture_index);
    }
    
    gic_void Filter::save_bmp(const gic_char* path, gic_byte* datas){
        dynamic_cast<FrameBuffer*>(_framebuffer)->save_bmp(path, datas);
    }
    
    gic_uint Filter::get_texturid(gic_int texture_index){
        return _framebuffer->get_texture_buffer_id(texture_index);
    }
    
    gic_uint Filter::get_id()const{
        return _hash_id;
    }
}
