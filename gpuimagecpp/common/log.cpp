//
//  log.cpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/10.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "log.hpp"
#include <stdio.h>
#include <stdarg.h>

namespace gpuimagecpp {
    void log_printf (const char *formatStr, ... ){
        va_list params;
        char buf[BUFSIZ];
        va_start ( params, formatStr );
#ifdef _WIN32
        vsprintf_s(buf, BUFSIZ, formatStr, params);
#else
        vsprintf ( buf, formatStr, params );
#endif
#ifdef ANDROID
        __android_log_print ( ANDROID_LOG_INFO, "esUtil" , "%s", buf );
#else
        printf ( "%s", buf );
#endif
        
        va_end ( params );
    }
}
