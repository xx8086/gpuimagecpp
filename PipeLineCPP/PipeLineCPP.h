//
//  PipeLineCPP.h
//  PipeLineCPP
//
//  Created by liu on 2018/9/14.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
@interface PipeLineCPP : NSObject
-(void)initpipeline;
-(void)resizew:(int)w resizeh:(int)h;
-(unsigned int)frame_counts;
-(unsigned int)frame_id:(unsigned int)index;
-(unsigned int)render:(unsigned int)textureid;
-(unsigned char*)frame_texture_datas:(unsigned int)frameid;
-(unsigned char*)image_datas:(unsigned int)textureid;
-(void) save_bmp:(const char*)path images:(unsigned char*)datas;
@end
