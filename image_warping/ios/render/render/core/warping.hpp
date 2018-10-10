//
//  warping.hpp
//  render
//
//  Created by liu on 2018/8/27.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef warping_hpp
#define warping_hpp


typedef struct warp_control{
    struct warp_control* next;
    int warp_type;
    double orig_x;
    double orig_y;//中心位置
    double mou_dx_norm;
    double mou_dy_norm;//normalized mouse delta
    double max_dist; //radius
    double max_dist_sq;//the square of max_dlist
    double mou_dx;
    double mou_dy;
    double angle;
    double angle_offset;
}warp_control;

typedef struct warper_struct{
    warp_control* controls;
    warp_control* redo_list;
}warper;

void mapping(warp_control* controls, double x, double y, double *u, double *v);

#endif /* warping_hpp */
