//
//  filters_manage.hpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/11.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef filters_manage_hpp
#define filters_manage_hpp
#include <unordered_map>
#include <string>
#include <vector>
#include "../bridge/filter.hpp"

namespace gpuimagecpp {
    class FiltersManage{
    public:
        FiltersManage();
        ~FiltersManage();
    public:
        Filter* find_filter(const gic_uint filterid) const;
        gic_byte* image_datas(gic_uint textureid);
        gic_byte* frame_texture_datas(gic_uint frameid);
        gic_void save_bmp(const char* path, gic_byte* datas);
        gic_uint render(gic_uint textureid);
        gic_uint frame_counts();
        gic_uint frame_id(gic_uint index);
        gic_void clear_order_list();
        gic_bool resize(const int w, const int h);
        gic_bool enable_filter(const gic_uint filterid);
        gic_bool disable_filter(const gic_uint filterid);
        gic_bool append_filter(const gic_uint filterid);//插入_order_filters
        gic_bool insert_filter(const gic_uint filterid, Filter* filter);//插入_filters
    protected:
        gic_void destory_all();//暂不开放
        gic_void destory_fiter(const gic_uint filterid);
        
    private:
        gic_void release();
    private:
        std::vector<Filter*> _order_filters;//管线执行顺序
        std::unordered_map<gic_uint, Filter*> _filters;//专门用于快速find
    };
}

#endif /* filters_manage_hpp */
