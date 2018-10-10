#include "glgrid.h"


namespace lh_gl {
    glgrid::glgrid()
    {
    }

    glgrid::~glgrid()
    {
    }

    void glgrid::set_grid_len(int nums, float begin, float advance) {
        _grid_nums = nums;
        _grid_begin = begin;
        _grid_advance = advance;
        _grid_len = _grid_nums*advance + begin;
    }

    void glgrid::get_grid_horizontal(std::vector<float>& vecs, float depth) {
        float height = TETRI_HIGHT + 0.5;
        for (float begin = 0.0f; begin <= height; begin++) {
            vecs.push_back(0);//x
            vecs.push_back(begin*TETRI_UNIT_LENGTH);//y
            vecs.push_back(depth);//z

            vecs.push_back(TETRI_WIDTH);//x
            vecs.push_back(begin*TETRI_UNIT_LENGTH);//y
            vecs.push_back(depth);//z
        }
    }
    void glgrid::get_grid_vertical(std::vector<float>& vecs, float depth) {
        float height = TETRI_WIDTH + 0.5;
        for (float begin = 0.0f; begin <= height; begin++) {
            vecs.push_back(begin*TETRI_UNIT_LENGTH);//x
            vecs.push_back(0);//y
            vecs.push_back(depth);//z

            vecs.push_back(begin*TETRI_UNIT_LENGTH);//x
            vecs.push_back(TETRI_HIGHT);//y
            vecs.push_back(depth);//z
        }
    }

    void glgrid::get_grid_horizontal(std::vector<float>& vecs, GRID_FACE face) {
        if (GRID_FACE_X == face) {//x
            for (int i = 0; i <= _grid_nums; i++) {
                vecs.push_back(_grid_begin);//x
                vecs.push_back(_grid_begin + i*_grid_advance);//y
                vecs.push_back(-_grid_begin);//z

                vecs.push_back(_grid_len);//x
                vecs.push_back(_grid_begin + i*_grid_advance);//y
                vecs.push_back(-_grid_begin);//z
            }
        }
        else if (GRID_FACE_Y == face) {//y
            for (int i = 0; i <= _grid_nums; i++) {
                vecs.push_back(_grid_begin);//x
                vecs.push_back(_grid_begin + i*_grid_advance);//y
                vecs.push_back(_grid_begin);//z

                vecs.push_back(_grid_begin);//x
                vecs.push_back(_grid_begin + i*_grid_advance);//y
                vecs.push_back(_grid_len);//z
            }
        }
        else if (GRID_FACE_Z == face) {
            for (int i = 0; i <= _grid_nums; i++) {
                vecs.push_back(_grid_begin);//x
                vecs.push_back(_grid_begin);//y
                vecs.push_back(_grid_begin + i*_grid_advance);//z

                vecs.push_back(_grid_len);//x
                vecs.push_back(_grid_begin);//y
                vecs.push_back(_grid_begin + i*_grid_advance);//z
            }

        }
    }
    void glgrid::get_grid_vertical(std::vector<float>& vecs, GRID_FACE face) {
        if (GRID_FACE_X == face) {//x
            for (int i = 0; i <= _grid_nums; i++) {
                vecs.push_back(_grid_begin + i*_grid_advance);//x
                vecs.push_back(_grid_begin);//y
                vecs.push_back(-_grid_begin);//z

                vecs.push_back(_grid_begin + i*_grid_advance);//x
                vecs.push_back(_grid_len);//y
                vecs.push_back(-_grid_begin);//z
            }
        }
        else if (GRID_FACE_Y == face) {//y
            for (int i = 0; i <= _grid_nums; i++) {
                vecs.push_back(_grid_begin);//x
                vecs.push_back(_grid_begin);//y
                vecs.push_back(_grid_begin + i*_grid_advance);//z

                vecs.push_back(_grid_begin);//x
                vecs.push_back(_grid_len);//y
                vecs.push_back(_grid_begin + i*_grid_advance);//z
            }
        }
        else if (GRID_FACE_Z == face) {
            for (int i = 0; i <= _grid_nums; i++) {
                vecs.push_back(_grid_begin + i*_grid_advance);//x
                vecs.push_back(_grid_begin);//y
                vecs.push_back(_grid_begin);//z

                vecs.push_back(_grid_begin + i*_grid_advance);//x
                vecs.push_back(_grid_begin);//y
                vecs.push_back(_grid_len);//z
            }
        }
    }

}