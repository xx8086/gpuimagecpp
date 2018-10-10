#include "draw_tetri.h"
#include <assert.h>

namespace lh_gl {
    draw_tetri::draw_tetri(){
        _gl_tetri_shardes = new CShader;
    }


    draw_tetri::~draw_tetri(){
        release_gl_datas();
        if(nullptr != _gl_tetri_shardes){
            delete _gl_tetri_shardes;
            _gl_tetri_shardes = nullptr;
        }
    }

    void draw_tetri::release_gl_datas() {
        glDeleteVertexArrays(1, &_vao_tetri);
        glDeleteBuffers(1, &_vbo_tetri);
    }

    void draw_tetri::draw(const Matrix4f &proj, const Matrix4f &view, const Matrix4f &model, 
        const vec3& viewpos, bool uniformcolor) {
        _gl_tetri_shardes->use();
        
        _light_material.update_material(_gl_tetri_shardes, viewpos);

        _gl_tetri_shardes->setmat4("view", view);
        _gl_tetri_shardes->setmat4("projection", proj);
        _gl_tetri_shardes->setmat4("model", model);
        if (uniformcolor) {
            _gl_tetri_shardes->setvec3("light_color", _colors[_current_color][0], _colors[_current_color][1], _colors[_current_color][2]);
        }

        glBindVertexArray(_vao_tetri);
        glDrawArrays(GL_TRIANGLES, 0, _curr_counts);
        _gl_tetri_shardes->unuse();
    }

    void draw_tetri::init_vao() {
        glGenVertexArrays(1, &_vao_tetri);
        glGenBuffers(1, &_vbo_tetri);
    }

    bool draw_tetri::init_sharde(const char* dir, const char* strvs, const char* strfs) {
        return  GL_TRUE == _gl_tetri_shardes->loadshader(dir, strvs, strfs);
    }

    void draw_tetri::set_light_postion(vec3 postion) {
        _light_material.set_light_pos(postion);
    }

    unsigned int draw_tetri::get_curr_data_point_nums() {
        return _current_datas.size();
    }

    void draw_tetri::set_curr_counts(unsigned int nums) {
        _curr_counts = nums;
    }

    std::vector<float>& draw_tetri::get_datas() {
        return _current_datas;
    }

    void draw_tetri::update_gl_current_datas() {
        if (!_current_datas.empty()) {
            glBindVertexArray(_vao_tetri);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo_tetri);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*_current_datas.size(), _current_datas.data());
            glBindVertexArray(0);
        }
    }

    void draw_tetri::bind_datas(std::function<void(void)> bind_buffer_datas) {
        glBindVertexArray(_vao_tetri);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo_tetri);
        bind_buffer_datas();
        glBindVertexArray(0);
    }

    void draw_tetri::set_color(short color) {
        if (COLOR_0 < color &&
            color < COLOR_END) {
            _current_color = color;
        }
        else {
            assert(0);
        }
    }
}
