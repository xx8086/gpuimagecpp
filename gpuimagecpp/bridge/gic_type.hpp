//
//  gic_type.h
//  GPUImageCPP
//
//  Created by liu on 2018/9/10.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef gic_type_h
#define gic_type_h

namespace gpuimagecpp {
    typedef unsigned int gic_uint;
    typedef unsigned short gic_ushort;
    typedef unsigned long gic_ulong;
    typedef unsigned long long gic_ulonglong;
    typedef unsigned char gic_byte;
    typedef unsigned char gic_uchar;
    typedef unsigned gic_unsigned;
    
    typedef int gic_int;
    typedef short gic_short;
    typedef long gic_long;
    typedef char gic_char;
    typedef float gic_float;
    typedef double gic_double;
    typedef long long gic_longlong;
    typedef bool gic_bool;
    typedef void gic_void;
    
    struct GicSize{
        gic_int width = 0;
        gic_int height = 0;
        GicSize(gic_int w, gic_int h):width(w),height(h){};
        GicSize():width(0),height(0){}
    };
    
    struct Vec2f{
        gic_float x;
        gic_float y;
    };
    
    struct Vec3f{
        gic_float x;
        gic_float y;
        gic_float z;
    };
    
    struct Mat4f{
        gic_float m[4][4];
    };
    
#define GIC_DELETE_PTR(ptr) {\
    if (nullptr != ptr){\
        delete ptr;\
        ptr = nullptr;\
    }}
  
    
#define GIC_DELETE_ARRY_PTR(ptr) {\
    if (nullptr != ptr){\
        delete [] ptr;\
        ptr = nullptr;\
    }}
    
}
#endif /* gic_type_h */
