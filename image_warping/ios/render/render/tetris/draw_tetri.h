#pragma once

#include "tetri_type.h"
#include "material.h"
#include <functional>
#include <vector>
namespace lh_gl {
    class draw_tetri :
        protected color_cube
    {
    public:
        draw_tetri();
        ~draw_tetri();
    public:
        //void init();
        void draw(const Matrix4f &proj, const Matrix4f &view, const Matrix4f &model, 
            const vec3& viewpos,  bool uniformcolor = false);
        void release_gl_datas();
        bool init_sharde(const char* dir, const char* strvs, const char* strfs);
        void init_vao();
        void bind_datas(std::function<void (void)> bind_buffer_datas);
        void update_gl_current_datas();
        void set_curr_counts(unsigned int nums);
        void set_color(short);
        unsigned int get_curr_data_point_nums();
        std::vector<float>& get_datas();
        void set_light_postion(vec3 postion);
    private:
        CShader* _gl_tetri_shardes;
        material _light_material;
        GLuint _vao_tetri = 0;
        GLuint _vbo_tetri = 0;
        std::vector<float> _current_datas;
        short _current_color;
        unsigned int _curr_counts = 0;
    };
}
