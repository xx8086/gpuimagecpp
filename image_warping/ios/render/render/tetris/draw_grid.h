#pragma once
#include "glgrid.h"
#include "shader.hpp"

namespace lh_gl {
    typedef enum DrawGridFace {
        DRAW_GRID_FACE_NULL = 0,
        DRAW_GRID_FACE_X = 0x1,
        DRAW_GRID_FACE_Y = 0x2,
        DRAW_GRID_FACE_Z = 0x4,
    }DRAW_GRID_FACE;
 
    class draw_grid
    {
    public:
        draw_grid();
        ~draw_grid();
    public:
        void init(const char* dir);
        void draw(const Matrix4f &proj, const Matrix4f &view, const Matrix4f &model);
        void set_draw_face(unsigned int drawface);
    private:
        bool isdraw(GRID_FACE);
        void release();
        void init_sharde(const char*);
        void vao();
        void vao_xyz();
        void vao_x();
        void draw_xyz(const Matrix4f & proj, const Matrix4f &view, const Matrix4f &model);
        void draw_x(const Matrix4f & proj, const Matrix4f &view, const Matrix4f &model);
    private:
        unsigned int _draw_face = 0;
        glgrid _grid;
        CShader* _gl_shardes_grid[GRID_FACE_NUMS] = { nullptr };
        GLuint _vao_hor[GRID_FACE_NUMS];
        GLuint _vao_ver[GRID_FACE_NUMS];
        GLuint _vbo_hor[GRID_FACE_NUMS];
        GLuint _vbo_ver[GRID_FACE_NUMS];
        vec3 _grid_colors_horizontal[GRID_FACE_NUMS];
        vec3 _grid_colors_vertical[GRID_FACE_NUMS];
        int _grid_point_nums_hor[GRID_FACE_NUMS] = {0};
        int _grid_point_nums_ver[GRID_FACE_NUMS] = {0};

        float _colors[GRID_FACE_NUMS][3] = {
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0}
        };
    };
}
