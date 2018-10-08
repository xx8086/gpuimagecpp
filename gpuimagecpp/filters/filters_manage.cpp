//
//  filters_manage.cpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/11.
//  Copyright © 2018年 hanliu. All rights reserved.
//
#include <assert.h>
#include "filters_manage.hpp"
#include "../common/lock.h"

namespace gpuimagecpp {
    FiltersManage::FiltersManage(){
        ;
    }
    
    FiltersManage::~FiltersManage(){
        destory_all();
        release();
    }
    
    gic_void FiltersManage::release(){
        _order_filters.clear();
        _filters.clear();
    }
    
    gic_bool FiltersManage::resize(const int w, const int h){
        return true;
    }
    
    gic_void FiltersManage::save_bmp(const char* path, gic_byte* datas){
        auto iter = _order_filters.rbegin();
        (*iter)->save_bmp(path, datas);
    }
    
    gic_byte* FiltersManage::image_datas(gic_uint textureid){
        auto iter = _order_filters.rbegin();
        return (*iter)->get_bytes(textureid);
    }
    
    gic_byte* FiltersManage::frame_texture_datas(gic_uint frameid){
        auto_lock();
        gic_byte* datas = nullptr;
        for(auto iter = _order_filters.begin();
            iter != _order_filters.end();
            iter++){
            if((*iter)->get_frameid() == frameid){
                datas = (*iter)->get_bytes((*iter)->get_texturid());
                break;
            }
        }
        return datas;
    }

    gic_uint FiltersManage::render(gic_uint textureid){
        //auto_lock();
        for(auto iter = _order_filters.begin();
            iter != _order_filters.end();
            iter++){
            if ((*iter)->enable()){
                textureid = (*iter)->render(textureid);
            }
        }
        return textureid;
    }
    
    gic_uint FiltersManage::frame_counts(){
        return _order_filters.size();
    }
    
    gic_uint FiltersManage::frame_id(gic_uint index){
        assert(index < _order_filters.size());
        auto iter = _order_filters.begin();
        iter+=index;
        return (*iter)->get_frameid();
    }
    
    gic_bool FiltersManage::append_filter(const gic_uint filterid){
        auto search = _filters.find(filterid);//查找、插入不用加锁；删除和render加旋转锁就行了。
        if (_filters.end() != search){
            _order_filters.emplace_back(search->second);//同一个id可以多次插入_order_filters，使其多次render
            return true;
        }
        return false;
    }
    
    gic_bool FiltersManage::insert_filter(const gic_uint filterid, Filter* filter){
        auto ret = _filters.emplace(filterid, filter);//已有的id插入会失败，只存一份
        return ret.second;
    }
    
    Filter* FiltersManage::find_filter(const gic_uint filterid) const{
        auto search = _filters.find(filterid);//查找、插入不用加锁；删除和render加旋转锁就行了。
        if (_filters.end() != search){
            return search->second;
        }
        return nullptr;
    }
    
    gic_bool FiltersManage::enable_filter(const gic_uint filterid){
        Filter* filter = find_filter(filterid);
        if (nullptr != filter){
            filter->visible();
            return true;
        }
        return false;
    }
    gic_bool FiltersManage::disable_filter(const gic_uint filterid){
        Filter* filter = find_filter(filterid);
        if (nullptr != filter){
            filter->invisible();
            return true;
        }
        return false;
    }
    gic_void FiltersManage::clear_order_list(){
        auto_lock();
        _order_filters.clear();
    }
    
    gic_void FiltersManage::destory_all(){
        auto_lock();
        _order_filters.clear();
        for(auto iter = _filters.begin();
            iter != _filters.end();
            iter++){
            if (nullptr != iter->second){
                delete iter->second;
                iter->second = nullptr;
            }
        }
        _filters.clear();
    }
    gic_void FiltersManage::destory_fiter(const gic_uint filterid){
        auto_lock();
        auto search = _filters.find(filterid);
        if (_filters.end() != search){
            for (auto iter = _order_filters.begin();
                 iter != _order_filters.end();
                 iter++){
                if (*iter == search->second){
                    _order_filters.erase(iter);
                    break;
                }
            }
            _filters.erase(search);
        }
    }
}
