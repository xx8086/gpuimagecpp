//
//  shake_filter.hpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/13.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef shake_filter_hpp
#define shake_filter_hpp
#include "../bridge/filter.hpp"

namespace gpuimagecpp {
    class ShakeFilter: public Filter{
    public:
        ShakeFilter();
        virtual ~ShakeFilter();
        
    public:
        gic_uint render(gic_uint textureid);
        gic_void init(const char* filtername, const char* dir);
        gic_void reset_configure();
        
    private:
        gic_float ratio();
        
    private:
        gic_float _ratio;
        gic_float _shake_stenght;
        //gic_int _frame_count;
        //gic_int _shake_frame;
        gic_bool _is_shake_out;
        
    };
}

#endif /* shake_filter_hpp */
