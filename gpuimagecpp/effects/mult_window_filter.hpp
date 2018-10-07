//
//  mult_window_filter.hpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/12.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef mult_window_filter_hpp
#define mult_window_filter_hpp
#include "../bridge/filter.hpp"

namespace gpuimagecpp {
    class MultWindowFilter: public Filter{
    public:
        MultWindowFilter();
        virtual ~MultWindowFilter();
    public:
        gic_uint render(gic_uint textureid);
        gic_void init(const char* filtername, const char* dir);
        gic_void reset_configure();
        
    private:
        gic_void switch_window();
    private:
        gic_int _frame_count;
        gic_int _window_count;

    };
}

#endif /* mult_window_filter_hpp */
