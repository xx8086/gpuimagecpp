//
//  face_plusplus.hpp
//  render
//
//  Created by liu on 2018/7/24.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef face_plusplus_hpp
#define face_plusplus_hpp

//#include "MG_Common.h"
#include "MG_Facepp.h"
#include "type_render.h"
#include <vector>

struct Face106{
    Vec3f cheek[33];//脸颊
    Vec3f left_eye[9];//[0]正中心
    Vec3f right_eye[9];//[0]正中心
    Vec3f left_eyebrow[9];//眉毛
    Vec3f right_eyebrow[9];//
    Vec3f nose[9];//鼻头
    Vec3f bridge_nose[6];//鼻梁
    Vec3f mouth_inside[8];//内嘴唇
    Vec3f mouth_outside[12];//外嘴唇
    Vec3f benevolence[2];//眼仁
};

class FacePP{
public:
    FacePP();
    ~FacePP();
    
public:
    void set_face_points(MG_SINGLE width, MG_SINGLE height, MG_FACELANDMARKS&, Face106&);
    void set_face_deep(float deep);
    
    MG_RETCODE init_handle(MG_BYTE* model_data, int32_t model_length);
    MG_RETCODE set_image_data(int width, int height, const MG_BYTE *image_data, MG_IMAGEMODE image_mode);
    MG_RETCODE detect_face(std::vector<MG_FACE>&);
    MG_RETCODE set_config(const MG_FPP_APICONFIG config);
    MG_RETCODE get_config(MG_FPP_APICONFIG *config);
    MG_RETCODE get_land_mark(MG_INT32 faceid, MG_BOOL smooth, MG_POINT* points, MG_INT32 nr = MG_FPP_GET_LANDMARK106);
    MG_RETCODE get_faceinfo(MG_INT32 faceid, MG_FACE* face);
    const char* get_version();
    MG_UINT64 get_expiration();
private:
    void release();
    inline Vec3f to_point(MG_POINT& point, MG_SINGLE& fw, MG_SINGLE& fh);
private:
    MG_FPP_APIHANDLE _api_handle = nullptr;
    MG_FPP_IMAGEHANDLE _imge_handle = nullptr;
    MG_FPP_APICONFIG _config;
    int _width = 0;
    int _height = 0;
    float _face_deep = 0.0f;
};

#endif /* face_plusplus_hpp */
