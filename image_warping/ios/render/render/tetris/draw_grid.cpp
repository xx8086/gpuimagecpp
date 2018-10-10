#include "draw_grid.h"

namespace lh_gl {
    draw_grid::draw_grid()
    {
    }

    draw_grid::~draw_grid()
    {
        release();
    }

    void draw_grid::set_draw_face(unsigned int drawface) {
        _draw_face = drawface;
    }

    bool draw_grid::isdraw(GRID_FACE face) {
        return _draw_face & (1 << face);
    }

    void draw_grid::release() {
        for (int face = GRID_FACE_X;
            face < GRID_FACE_NUMS;
            face++) {
            if (isdraw((GRID_FACE)face)) {
                glDeleteVertexArrays(1, &_vao_hor[face]);
                glDeleteBuffers(1, &_vbo_hor[face]);

                glDeleteVertexArrays(1, &_vao_ver[face]);
                glDeleteBuffers(1, &_vbo_ver[face]);

                if (nullptr != _gl_shardes_grid[face]) {
                    _gl_shardes_grid[face]->unuse();
                    delete _gl_shardes_grid[face];
                    _gl_shardes_grid[face] = nullptr;
                }
            }
        }
    }

    void draw_grid::draw_x(const Matrix4f & proj, const Matrix4f &view, const Matrix4f &model) {
        _gl_shardes_grid[GRID_FACE_X]->use();
        _gl_shardes_grid[GRID_FACE_X]->setmat4("view", view);
        _gl_shardes_grid[GRID_FACE_X]->setmat4("projection", proj);
        _gl_shardes_grid[GRID_FACE_X]->setmat4("model", model);
        _gl_shardes_grid[GRID_FACE_X]->setvec3("grid_color", _colors[0][0], _colors[0][1], _colors[0][2]);
        glBindVertexArray(_vao_ver[GRID_FACE_X]);
        glDrawArrays(GL_LINES, 0, _grid_point_nums_ver[GRID_FACE_X]);

        _gl_shardes_grid[GRID_FACE_X]->setvec3("grid_color", _colors[1][0], _colors[1][1], _colors[1][2]);
        glBindVertexArray(_vao_hor[GRID_FACE_X]);
        glDrawArrays(GL_LINES, 0, _grid_point_nums_hor[GRID_FACE_X]);
    }

    void draw_grid::draw_xyz(const Matrix4f & proj, const Matrix4f &view, const Matrix4f &model) {
        for (int face = GRID_FACE_X;
            face < GRID_FACE_NUMS;
            face++) {
            if (isdraw((GRID_FACE)face)) {
                _gl_shardes_grid[face]->use();
                _gl_shardes_grid[face]->setmat4("view", view);
                _gl_shardes_grid[face]->setmat4("projection", proj);
                _gl_shardes_grid[face]->setmat4("model", model);
                _gl_shardes_grid[face]->setvec3("grid_color", _colors[face][0], _colors[face][1], _colors[face][2]);
                glBindVertexArray(_vao_ver[face]);
                glDrawArrays(GL_LINES, 0, _grid_point_nums_ver[face]);

                glBindVertexArray(_vao_hor[GRID_FACE_X]);
                glDrawArrays(GL_LINES, 0, _grid_point_nums_hor[GRID_FACE_X]);
            }
        }
    }

    void draw_grid::vao_xyz() {
        _grid.set_grid_len(10, -1.0, 0.2);

        std::vector<float> vecs_hor[GRID_FACE_NUMS];
        std::vector<float> vecs_ver[GRID_FACE_NUMS];
        for (int face = GRID_FACE_X;
            face < GRID_FACE_NUMS;
            face++) {
            if (isdraw((GRID_FACE)face)) {
                _grid.get_grid_horizontal(vecs_hor[face], (GRID_FACE)face);
                _grid.get_grid_vertical(vecs_ver[face], (GRID_FACE)face);

                _grid_point_nums_hor[face] = vecs_hor[face].size() / 3;
                _grid_point_nums_ver[face] = vecs_ver[face].size() / 3;

                glGenVertexArrays(1, &_vao_ver[face]);
                glBindVertexArray(_vao_ver[face]);
                glGenBuffers(1, &_vbo_ver[face]);
                glBindBuffer(GL_ARRAY_BUFFER, _vbo_ver[face]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vecs_ver[face].size(), vecs_ver[face].data(), GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glEnableVertexAttribArray(0);

                glGenVertexArrays(1, &_vao_hor[face]);
                glBindVertexArray(_vao_hor[face]);
                glGenBuffers(1, &_vbo_hor[face]);
                glBindBuffer(GL_ARRAY_BUFFER, _vbo_hor[face]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vecs_hor[face].size(), vecs_hor[face].data(), GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glEnableVertexAttribArray(0);

                glBindVertexArray(0);
            }
        }
    }

    void draw_grid::vao_x() {
        std::vector<float> vecs_hor;
        std::vector<float> vecs_ver;

        _grid.get_grid_horizontal(vecs_hor, (float)TETRI_Z);
        _grid.get_grid_vertical(vecs_ver, (float)TETRI_Z);

        _grid.get_grid_horizontal(vecs_hor, (float)TETRI_DEPT);
        _grid.get_grid_vertical(vecs_ver, (float)TETRI_DEPT);

        _grid_point_nums_hor[GRID_FACE_X] = vecs_hor.size() / 3;
        _grid_point_nums_ver[GRID_FACE_X] = vecs_ver.size() / 3;

        glGenVertexArrays(1, &_vao_ver[GRID_FACE_X]);
        glBindVertexArray(_vao_ver[GRID_FACE_X]);
        glGenBuffers(1, &_vbo_ver[GRID_FACE_X]);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo_ver[GRID_FACE_X]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vecs_ver.size(), vecs_ver.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);

        glGenVertexArrays(1, &_vao_hor[GRID_FACE_X]);
        glBindVertexArray(_vao_hor[GRID_FACE_X]);
        glGenBuffers(1, &_vbo_hor[GRID_FACE_X]);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo_hor[GRID_FACE_X]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vecs_hor.size(), vecs_hor.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }


    void draw_grid::draw(const Matrix4f & proj, const Matrix4f &view, const Matrix4f &model) {
        draw_x(proj, view, model);
        //draw_xyz(proj, view, model);
    }
    void draw_grid::vao() {
        vao_x();
        //vao_xyz();
    }

    void draw_grid::init_sharde(const char* dir) {
        for (int face = GRID_FACE_X;
            face < GRID_FACE_NUMS;
            face++) {
            if (isdraw((GRID_FACE)face)) {
                if (nullptr == _gl_shardes_grid[face]){
                    _gl_shardes_grid[face] = new CShader;
                }
                _gl_shardes_grid[face]->loadshader(dir,
                                                   "grid.vs",
                                                   "grid.fs");
            }
        }

    }

    void draw_grid::init(const char* dir) {
        init_sharde(dir);
        vao();
    }

}
