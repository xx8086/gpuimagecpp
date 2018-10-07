//
//  PipeLineCPP.m
//  PipeLineCPP
//
//  Created by liu on 2018/9/14.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#import "PipeLineCPP.h"
#import "interface_gpuimagecpp.hpp"


@implementation PipeLineCPP{
    gpuimagecpp::CInterfaceGpuImageCPP _piple;
}

-(void)initpipeline{
    //NSString *vertexShaderPathname = [[NSBundle mainBundle] pathForResource:@"default" ofType:@"vsh"];
    NSString *nsdir = [[NSBundle mainBundle] bundlePath];
    const char* strdir = [nsdir cStringUsingEncoding:NSASCIIStringEncoding];
    _piple.init(strdir);
}
-(void)resizew:(int)w resizeh:(int)h{
    _piple.resize(w, h);
}
-(unsigned int)render:(unsigned int)textureid{
    return _piple.render(textureid);
}

-(unsigned char*)image_datas:(unsigned int)textureid{
    return _piple.image_datas(textureid);
}

-(unsigned char*)frame_texture_datas:(unsigned int)frameid{
    return _piple.frame_texture_datas(frameid);
}

-(void) save_bmp:(const char*)path images:(unsigned char*)datas{
    return _piple.save_bmp(path, datas);
}

-(unsigned int)frame_counts{
    return _piple.frame_counts();
}

-(unsigned int)frame_id:(unsigned int)index{
    return _piple.frame_id(index);
}
@end
