//
//  out_soul_filter.hpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/12.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef out_soul_filter_hpp
#define out_soul_filter_hpp
#include "../bridge/filter.hpp"

namespace gpuimagecpp {
    class OutSoulFilter: public Filter{
    public:
        OutSoulFilter();
        virtual ~OutSoulFilter();
        
    public:
        gic_uint render(gic_uint textureid);
        gic_void init(const char* filtername, const char* dir);
        gic_void reset_configure();

    private:
        gic_float ratio();
        
    private:
        gic_int _frame_count;
        gic_int _out_soul_frame;
        gic_float _ratio;
        gic_float _alpha;//灵魂透明度 0 - 1
    };
}
#endif /* out_soul_filter_hpp */
