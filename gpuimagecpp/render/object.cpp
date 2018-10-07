//
//  object.cpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/11.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "../bridge/object.hpp"
namespace gpuimagecpp {
    gic_void Object::visible(){
        _enble = true;
    }
    gic_void Object::invisible(){
        _enble = false;
    }
    
    gic_bool Object::enable(){
        return _enble;
    }
}
