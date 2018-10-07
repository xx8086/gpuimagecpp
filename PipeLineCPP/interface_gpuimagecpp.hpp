//
//  interface_gpuimagecpp.hpp
//  GPUImageCPP
//
//  Created by liu on 2018/9/14.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef interface_gpuimagecpp_hpp
#define interface_gpuimagecpp_hpp

namespace gpuimagecpp {
    class CInterfaceGpuImageCPP{
    public:
        CInterfaceGpuImageCPP();
        ~CInterfaceGpuImageCPP();
    public:
        bool init(const char* dir);
        bool resize(const int w, const int h);
        unsigned int frame_counts();
        unsigned int frame_id(unsigned int index);
        unsigned int render(unsigned int textureid, unsigned int frame_index = 0);
        unsigned char* image_datas(unsigned int textureid);
        unsigned char* frame_texture_datas(unsigned int frameid);
        void save_bmp(const char* path, unsigned char* datas);
    private:
        //unsigned int render(unsigned char* texturedatas, unsigned int len, unsigned int index = 0);
        void append_filter(const unsigned int filterid);
        bool enable_filter(const unsigned int filterid);
        bool disable_filter(const unsigned int filterid);
        //Filter* find_filter(const gic_uint filterid) const;

    };
}
#endif /* gpuimagecpp_pipeline_hpp */
