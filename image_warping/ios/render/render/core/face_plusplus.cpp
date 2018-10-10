//
//  face_plusplus.cpp
//  render
//
//  Created by liu on 2018/7/24.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "face_plusplus.hpp"
#include <stdio.h>
#include <cstring>
#define KMGDETECTMAXFACE 5


FacePP::FacePP(){
    ;
}

FacePP::~FacePP(){
    release();
}

MG_RETCODE FacePP::set_image_data(int width, int height, const MG_BYTE *image_data, MG_IMAGEMODE image_mode){
    MG_RETCODE return_code = MG_RETCODE_OK;
    if (width == 0 || height == 0) {
        return_code = MG_RETCODE_INVALID_ARGUMENT;
        return return_code;
    }
    
    if (_imge_handle == nullptr) {
        mg_facepp.CreateImageHandle(width, height, &_imge_handle);
        _width = width;
        _height = height;
        
    }else{
        if (width != _width || height != _height) {
            mg_facepp.ReleaseImageHandle(_imge_handle);
            mg_facepp.CreateImageHandle(width, height, &_imge_handle);
        }
        
        _width = width;
        _height = height;
    }
    
    if (mg_facepp.SetImageData(_imge_handle, image_data, image_mode) != MG_RETCODE_OK) {
        return_code = MG_RETCODE_FAILED;
    }
    
    return return_code;
}

MG_RETCODE FacePP::init_handle(MG_BYTE * model_data, int32_t model_length){
    MG_RETCODE initcode = mg_facepp.CreateApiHandle((MG_BYTE *)model_data, model_length, &_api_handle);
    if (MG_RETCODE_OK != initcode){
        printf("[CreateApiHandle] 初始化失败，modelData 与 SDK 不匹配！，请检查后重试！errorCode:%d", initcode);
    }else{
        mg_facepp.GetDetectConfig(_api_handle, &_config);
        _config.min_face_size = 50;
        _config.interval = 5;
        _config.detection_mode = MG_FPP_DETECTIONMODE_TRACKING_FAST;
        _config.rotation = MG_ROTATION_0;
        _config.one_face_tracking = false;
        initcode = mg_facepp.SetDetectConfig(_api_handle, &_config);
    }
    
    return initcode;
}

MG_RETCODE FacePP::detect_face(std::vector<MG_FACE>& vecfaces){
    MG_RETCODE return_code = MG_RETCODE_OK;
    vecfaces.clear();
    int face_count = 0;
    return_code = mg_facepp.Detect(_api_handle, _imge_handle, &face_count);
    if (return_code == MG_RETCODE_OK) {
        face_count = face_count < KMGDETECTMAXFACE ? face_count : KMGDETECTMAXFACE;
        for(int i = 0 ; i < face_count; i++){
            MG_FACE face;
            mg_facepp.GetFaceInfo(_api_handle, i, &face);
            mg_facepp.GetLandmark(_api_handle, i, true, MG_LANDMARK_NR, face.points.point);
            vecfaces.emplace_back(face);
        }
    }
    return return_code;
}

MG_RETCODE FacePP::set_config(const MG_FPP_APICONFIG config){
    return mg_facepp.SetDetectConfig(_api_handle, &config);
}

MG_RETCODE FacePP::get_config(MG_FPP_APICONFIG *config){
    MG_RETCODE returnCode = mg_facepp.GetDetectConfig(_api_handle, config);
    return returnCode;
}

void FacePP::release(){
    if (_api_handle != nullptr) {
        mg_facepp.ReleaseApiHandle(_api_handle);
        _api_handle = nullptr;
        printf("release api_handle\n");
        mg_facepp.Shutdown();
    }
    
    if (_imge_handle != nullptr) {
        mg_facepp.ReleaseImageHandle(_imge_handle);
        _imge_handle = nullptr;
        printf("release imge_handle\n");
    }
}

MG_RETCODE FacePP::get_land_mark(MG_INT32 faceid, MG_BOOL smooth, MG_POINT* points, MG_INT32 nr){
    return mg_facepp.GetLandmark(_api_handle, faceid, smooth, nr, points);
}

MG_RETCODE FacePP::get_faceinfo(MG_INT32 faceid, MG_FACE* face){
    return mg_facepp.GetFaceInfo(_api_handle, faceid, face);
}

const char* FacePP::get_version(){
    return mg_facepp.GetApiVersion();
}

MG_UINT64 FacePP::get_expiration(){
    return mg_facepp.GetApiExpiration();
}

void FacePP::set_face_deep(float deep){
    _face_deep = deep;
}

Vec3f FacePP::to_point(MG_POINT& point, MG_SINGLE& fw, MG_SINGLE& fh){
    return  Vec3f((point.x - fw) / fw,
                  (point.y - fh) / fh,
                  _face_deep);
}


void FacePP::set_face_points(MG_SINGLE fw, MG_SINGLE fh, MG_FACELANDMARKS& points, Face106& facepoints){
    facepoints.benevolence[0] = to_point(points.point[104], fw, fh);
    facepoints.benevolence[1] = to_point(points.point[105], fw, fh);
    
    for(int i = 0; i < 33; i++){
        facepoints.cheek[i] = to_point(points.point[i], fw, fh);
    }
    
    int point_nums = 0;
    facepoints.left_eye[point_nums++] = to_point(points.point[74], fw, fh);
    facepoints.left_eye[point_nums++] = to_point(points.point[52], fw, fh);
    facepoints.left_eye[point_nums++] = to_point(points.point[53], fw, fh);
    facepoints.left_eye[point_nums++] = to_point(points.point[72], fw, fh);
    facepoints.left_eye[point_nums++] = to_point(points.point[54], fw, fh);
    facepoints.left_eye[point_nums++] = to_point(points.point[55], fw, fh);
    facepoints.left_eye[point_nums++] = to_point(points.point[56], fw, fh);
    facepoints.left_eye[point_nums++] = to_point(points.point[73], fw, fh);
    facepoints.left_eye[point_nums++] = to_point(points.point[57], fw, fh);
    
    point_nums = 0;
    facepoints.right_eye[point_nums++] = to_point(points.point[77], fw, fh);
    facepoints.right_eye[point_nums++] = to_point(points.point[58], fw, fh);
    facepoints.right_eye[point_nums++] = to_point(points.point[59], fw, fh);
    facepoints.right_eye[point_nums++] = to_point(points.point[75], fw, fh);
    facepoints.right_eye[point_nums++] = to_point(points.point[60], fw, fh);
    facepoints.right_eye[point_nums++] = to_point(points.point[61], fw, fh);
    facepoints.right_eye[point_nums++] = to_point(points.point[62], fw, fh);
    facepoints.right_eye[point_nums++] = to_point(points.point[76], fw, fh);
    facepoints.right_eye[point_nums++] = to_point(points.point[63], fw, fh);
    
    point_nums = 0;
    facepoints.left_eyebrow[point_nums++] = to_point(points.point[33], fw, fh);
    facepoints.left_eyebrow[point_nums++] = to_point(points.point[34], fw, fh);
    facepoints.left_eyebrow[point_nums++] = to_point(points.point[35], fw, fh);
    facepoints.left_eyebrow[point_nums++] = to_point(points.point[36], fw, fh);
    facepoints.left_eyebrow[point_nums++] = to_point(points.point[37], fw, fh);
    facepoints.left_eyebrow[point_nums++] = to_point(points.point[67], fw, fh);
    facepoints.left_eyebrow[point_nums++] = to_point(points.point[66], fw, fh);
    facepoints.left_eyebrow[point_nums++] = to_point(points.point[65], fw, fh);
    facepoints.left_eyebrow[point_nums++] = to_point(points.point[64], fw, fh);
    
    point_nums = 0;
    facepoints.right_eyebrow[point_nums++] = to_point(points.point[38], fw, fh);
    facepoints.right_eyebrow[point_nums++] = to_point(points.point[39], fw, fh);
    facepoints.right_eyebrow[point_nums++] = to_point(points.point[40], fw, fh);
    facepoints.right_eyebrow[point_nums++] = to_point(points.point[41], fw, fh);
    facepoints.right_eyebrow[point_nums++] = to_point(points.point[42], fw, fh);
    facepoints.right_eyebrow[point_nums++] = to_point(points.point[71], fw, fh);
    facepoints.right_eyebrow[point_nums++] = to_point(points.point[70], fw, fh);
    facepoints.right_eyebrow[point_nums++] = to_point(points.point[69], fw, fh);
    facepoints.right_eyebrow[point_nums++] = to_point(points.point[68], fw, fh);
    
    point_nums = 0;
    facepoints.nose[point_nums++] = to_point(points.point[81], fw, fh);
    facepoints.nose[point_nums++] = to_point(points.point[83], fw, fh);
    facepoints.nose[point_nums++] = to_point(points.point[51], fw, fh);
    facepoints.nose[point_nums++] = to_point(points.point[50], fw, fh);
    facepoints.nose[point_nums++] = to_point(points.point[49], fw, fh);
    facepoints.nose[point_nums++] = to_point(points.point[48], fw, fh);
    facepoints.nose[point_nums++] = to_point(points.point[47], fw, fh);
    facepoints.nose[point_nums++] = to_point(points.point[82], fw, fh);
    facepoints.nose[point_nums++] = to_point(points.point[80], fw, fh);
    
    point_nums = 0;
    facepoints.bridge_nose[point_nums++] = to_point(points.point[78], fw, fh);
    facepoints.bridge_nose[point_nums++] = to_point(points.point[43], fw, fh);
    facepoints.bridge_nose[point_nums++] = to_point(points.point[79], fw, fh);
    facepoints.bridge_nose[point_nums++] = to_point(points.point[44], fw, fh);
    facepoints.bridge_nose[point_nums++] = to_point(points.point[45], fw, fh);
    facepoints.bridge_nose[point_nums++] = to_point(points.point[46], fw, fh);
    
    point_nums = 0;
    facepoints.mouth_inside[point_nums++] = to_point(points.point[96], fw, fh);
    facepoints.mouth_inside[point_nums++] = to_point(points.point[97], fw, fh);
    facepoints.mouth_inside[point_nums++] = to_point(points.point[98], fw, fh);
    facepoints.mouth_inside[point_nums++] = to_point(points.point[99], fw, fh);
    facepoints.mouth_inside[point_nums++] = to_point(points.point[100], fw, fh);
    facepoints.mouth_inside[point_nums++] = to_point(points.point[101], fw, fh);
    facepoints.mouth_inside[point_nums++] = to_point(points.point[102], fw, fh);
    facepoints.mouth_inside[point_nums++] = to_point(points.point[103], fw, fh);
    
    point_nums = 0;
    facepoints.mouth_outside[point_nums++] = to_point(points.point[84], fw, fh);
    facepoints.mouth_outside[point_nums++] = to_point(points.point[85], fw, fh);
    facepoints.mouth_outside[point_nums++] = to_point(points.point[86], fw, fh);
    facepoints.mouth_outside[point_nums++] = to_point(points.point[87], fw, fh);
    facepoints.mouth_outside[point_nums++] = to_point(points.point[88], fw, fh);
    facepoints.mouth_outside[point_nums++] = to_point(points.point[89], fw, fh);
    facepoints.mouth_outside[point_nums++] = to_point(points.point[90], fw, fh);
    facepoints.mouth_outside[point_nums++] = to_point(points.point[91], fw, fh);
    facepoints.mouth_outside[point_nums++] = to_point(points.point[92], fw, fh);
    facepoints.mouth_outside[point_nums++] = to_point(points.point[93], fw, fh);
    facepoints.mouth_outside[point_nums++] = to_point(points.point[94], fw, fh);
    facepoints.mouth_outside[point_nums++] = to_point(points.point[95], fw, fh);
}
