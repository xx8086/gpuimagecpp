//
//  timer.hpp
//  GPUImageCPP
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef timer_hpp
#define timer_hpp

#include <chrono>
#include "../bridge/object.hpp"

namespace gpuimagecpp {
    class Timer: public ObjectTime
    {
    public:
        Timer();
        ~Timer();
    public:
        gic_float interval_ms();
        gic_void set_count_time(gic_int ms);
        gic_bool count_time();//每隔ms毫秒返回true,在ms时间内返回都是false
        gic_bool count_time_loop();
    private:
        gic_int _ms_count = 0;
        std::chrono::system_clock::time_point _aysnc_ms_count;
    };
}

#endif /* timer_hpp */
