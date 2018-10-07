//
//  texture_options.h
//  GPUImageCPP
//
//  Created by liu on 2018/9/10.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef texture_options_h
#define texture_options_h

namespace gpuimagecpp {
    typedef struct TextureOptions {
        unsigned int min_filter;
        unsigned int mag_filter;
        unsigned int wrap_s;
        unsigned int wrap_t;
        unsigned int internal_format;
        unsigned int format;
        unsigned int type;
        TextureOptions();
        
    } TextureOptions;
}

#endif /* texture_options_h */
