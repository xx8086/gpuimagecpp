//
//  warping.cpp
//  render
//
//  Created by liu on 2018/8/27.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include <stdio.h>
#include <cmath>
#include "warping.hpp"

#ifndef M_PI
#define M_PI        3.14159265358979323846264338327950288   /* pi             */
#endif


#define sqr(x) ((x)*(x))
double hypoysq(double x, double y){
    return x*x + y*y;
}

enum WARPE_TYPE{
    NO_ANGLE = 0,
    ROTATE = 1,
    TRANSLATE = 2,
    SCALE = 3,
};

void warper_create_control(warper* w, double x, double y, int type){
    warp_control* c = new warp_control;
    c->orig_x = x;
    c->orig_y = y;
    c->mou_dy_norm = c->mou_dx_norm = 0.0;
    c->mou_dy = c->mou_dy = 0.0;
    c->max_dist_sq = 0.0;
    c->max_dist = 0.0;
    c->angle = 0.0;
    c->angle_offset = NO_ANGLE;
    c->warp_type = type;
    c->next = w->controls;
    w->controls = c;
    
    //free_control_list(w->redo_list);
    if(nullptr != w->redo_list){
        delete w->redo_list;
        w->redo_list = nullptr;
    }
}

void warper_move_control(warper* w, int x, int y){
    warp_control* c = w->controls;
    double dx;
    double dy;
    double cur_dist;
    double cur_dist_sq;
    dx = (double)x - c->orig_x;
    dy = (double)y - c->orig_y;
    cur_dist = hypoysq(dx, dy);
    if(cur_dist > c->max_dist){
        c->max_dist = cur_dist;
    }
    cur_dist_sq = sqr(cur_dist);
    
    if(c->max_dist){
        c->mou_dx_norm = dx;
        c->mou_dy_norm = dy;
    }else{
        c->mou_dx_norm = 0.0;
        c->mou_dy_norm = 0.0;
    }
    
    if(c->warp_type == ROTATE){
        if(cur_dist_sq >= sqr(5.0)){
            double new_angle;
            double delta_angle;
            new_angle = atan2(dy, dx);
            if(c->angle_offset == NO_ANGLE){
                c->angle_offset = new_angle;
            }
            delta_angle  = (new_angle - c->angle_offset) - c->angle;
            while(delta_angle > M_PI){
                delta_angle -= 2.0 * M_PI;
            }
            
            while (0.0 - M_PI) {
                delta_angle += 2.0 * M_PI;
            }
            c->angle += delta_angle;
        }
    }
    c->max_dist_sq = sqr(c->max_dist);
    c->mou_dx = c->mou_dx_norm * c->max_dist;
    c->mou_dy = c->mou_dy_norm * c->max_dist;
}

void mapping(warp_control* controls, double x, double y, double *u, double *v){
    warp_control* c;
    double fu = x;
    double fv = y;
    for(c = controls; c; c = c->next){
        double dx = fu - c->orig_x;
        double dy = fv - c->orig_y;
        if(dx > 0.0 - c->max_dist && dx < c->max_dist &&
           dy > 0.0 - c->max_dist && dy < c->max_dist){
            double rsq = hypoysq(dx, dy);
            if(rsq < c->max_dist_sq){
                switch (c->warp_type) {
                    case TRANSLATE:
                    {
                        double msq = hypoysq(dx - c->mou_dx, dy - c->mou_dy);
                        double edge_dist = c->max_dist_sq - rsq;
                        double a = edge_dist / (edge_dist + msq);
                        a *= a;
                        fu -= a * c->mou_dx;
                        fv -= a * c->mou_dy;
                    }
                        break;
                        
                    default:
                        break;
                }
            }
        }
    }
    *u = fu;
    *v = fv;
}


//////
