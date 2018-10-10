#pragma once

#include "tetri_type.h"
#include <vector>

namespace lh_gl {
    typedef enum GridFace {
        GRID_FACE_X = 0,
        GRID_FACE_Y = 1,
        GRID_FACE_Z = 2,
        GRID_FACE_NUMS = 3,
    }GRID_FACE;

    class glgrid
    {
    public:
        glgrid();
        ~glgrid();
    public:
        void get_grid_horizontal(std::vector<float>& vecs, float depth);
        void get_grid_vertical(std::vector<float>& vecs, float depth);
    public:
        void get_grid_horizontal(std::vector<float>& vecs, GRID_FACE face);
        void get_grid_vertical(std::vector<float>& vecs, GRID_FACE face);
    public:
        void set_grid_len(int nums, float begin, float advance);

    private:
        int _grid_nums = 10;
        float _grid_len = 1.0;
        float _grid_begin = -1.0;
        float _grid_advance = 0.05;
    };
}
