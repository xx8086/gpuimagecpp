#include "manage_tetri.h"
#include<stdlib.h>
#include <time.h>
#include <stdarg.h>
#include "tetri_type.h"

namespace lh_gl {

    bool manage_tetri::can_draw() {
        return _timer.count_time_loop();
    }

    void manage_tetri::draw(const Matrix4f &proj, const Matrix4f &view, const Matrix4f &model, const vec3& viewpos) {
        _floor.draw(proj, view, model, viewpos);
        _current_cube.draw(proj, view, model, viewpos, true);
    }

    void manage_tetri::init(const char* dir, vec3 light_postion) {
        init_sharde(dir);
        init_vao();
        bind_buffer_datas();
        rand_cube();
        _timer.set_count_time(500);
        _current_cube.set_light_postion(light_postion);
        _floor.set_light_postion(light_postion);
    }

    void manage_tetri::init_vao() {
        _floor.init_vao();
        _current_cube.init_vao();
    }

    bool manage_tetri::init_sharde(const char* dir) {
        return (GL_TRUE == _floor.init_sharde(dir, "bttom_tertri.vs", "bttom_tertri.fs")) &&
        (GL_TRUE == _current_cube.init_sharde(dir, "cube.vs", "cube.fs"));
        
    }

    void manage_tetri::release_gl_datas() {
        //glInvalidateBufferData(GL_ARRAY_BUFFER);
        //glClearBufferData(GL_ARRAY_BUFFER, );
    }

    void manage_tetri::add_gl_datas(std::vector<float> subdatas) {
        
    }

    void manage_tetri::bind_buffer_datas() {
        _current_cube.bind_datas([]() {
            unsigned int buffer_size = CUBE_ITEM_NUMS * 6 * 6 * 6 * sizeof(float);
            glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);//postion
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//normal
            glBindVertexArray(0);
        });

        _floor.bind_datas([]() {
            unsigned int max_buffer_size = TETRI_WIDTH *TETRI_HIGHT  * 6 * 6 * 9 * sizeof(float);
            glBufferData(GL_ARRAY_BUFFER, max_buffer_size, nullptr, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);//postion
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));//noramal
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));//color
            glBindVertexArray(0);
        });
    }

    void manage_tetri::update_current_cube_counts() {
        unsigned int curr_cube_point_nums = _current_cube.get_curr_data_point_nums();
        _current_cube.set_curr_counts(curr_cube_point_nums / 6);//pos,normal
        _current_cube.update_gl_current_datas();
    }

    void manage_tetri::update_floor_counts() {
        unsigned int curr_floor_point_nums = _floor.get_curr_data_point_nums();
        _floor.set_curr_counts(curr_floor_point_nums / 9);//pos,normal,color
        _floor.update_gl_current_datas();
    }

    void manage_tetri::update_gl_datas() {
        _floor.update_gl_current_datas();
        _current_cube.update_gl_current_datas();
    }

    void manage_tetri::up() {
        if (GAME_GOON != _game_status || !_can_update) {
            return;
        }

        _can_update = false;
        short next_deg = update_degrees(_degrees);
        TeTriUniti tetri_uniti;
        _tetri.get_current_cube(tetri_uniti);
        _tetri_cube_generate.get_roate(next_deg, tetri_uniti);
        UPDATE_OBJ updateobj = _tetri.up(tetri_uniti);
        if (UPDATE_CURRENT_OBJ == updateobj) {
            update_current_gl_datas();
            _degrees = next_deg;
        }
        else if (UPDATE_FLOOR == updateobj)
        {
            update_floor();
        }

        _can_update = true;
    }

    void manage_tetri::left() {
        if (GAME_GOON != _game_status || !_can_update) {
            return;
        }

        _can_update = false;
        UPDATE_OBJ updateobj = _tetri.left();
        if (UPDATE_CURRENT_OBJ == updateobj) {
            update_current_gl_datas();
        }
        else if(UPDATE_FLOOR == updateobj)
        {
            update_floor();
        }

        _can_update = true;
    }
    void manage_tetri::right() {
        if (GAME_GOON != _game_status || !_can_update) {
            return;
        }

        _can_update = false;
        UPDATE_OBJ updateobj = _tetri.right();
        if (UPDATE_CURRENT_OBJ == updateobj) {
            update_current_gl_datas();
        }
        else if (UPDATE_FLOOR == updateobj){
            update_floor();
        }

        _can_update = true;
    }

    void manage_tetri::down() {
        if (GAME_GOON != _game_status || !_can_update) {
            return;
        }

        _can_update = false;
        short down_line_nums = 0;
        if (UPDATE_CURRENT_OBJ == _tetri.down(down_line_nums)) {
            update_current_gl_datas();
        }
        else{
            update_floor();
            _info.add_score(down_line_nums);
        }

        _can_update = true;
    }

    bool manage_tetri::update_floor(){
        if (!_tetri.need_update_triangls()) {
            return false;
        }

        reset_cube_to_buttom();
        rand_cube();
        _tetri.update_triangle_complate();
        return true;
    }

    void manage_tetri::add_cube_to_buttom() {
        std::vector<float>& vecs = _floor.get_datas();
        _tetri.add_curent_on_floor(vecs);
        update_floor_counts();
    }

    void manage_tetri::reset_cube_to_buttom() {
        std::vector<float>& vecs = _floor.get_datas();
        _tetri.floor_gl_datas(vecs);
        update_floor_counts();
    }

    void manage_tetri::update_current_gl_datas() {
        std::vector<float>& vecs = _current_cube.get_datas();
        _tetri.current_tetris_to_triangle(vecs);
        update_current_cube_counts();
    }

    void manage_tetri::rand_cube() {
        _degrees = 0;
        TeTriUniti tetri_uniti;
        srand((unsigned)time(NULL));
        rand();
        CUBETYPE type = (CUBETYPE)(rand()% CUBE_TYPE_NUMS);
        tetri_uniti.color = rand() % COLOR_7 + 1;
        //printf("type=%d, color=%d\n", type, tetri_uniti.color);
        _current_cube.set_color(tetri_uniti.color);
        _tetri_cube_generate.get_tetri(type, tetri_uniti);
        if (_tetri.set_current_cube(tetri_uniti)) {
            update_current_gl_datas();
        }
        else {
            _game_status = GAME_OVER;
            _info.game_over();
        }
    }

    void manage_tetri::suspend() {
        if (GAME_GOON == _game_status) {
            _game_status = GAME_SUSPEND;
        }
        else if (GAME_SUSPEND == _game_status) {
            _game_status = GAME_GOON;
        }
    }

    short manage_tetri::update_degrees(short deg) {
        return deg < ROATE_DEGREES_270 ? deg + ROATE_DEGREES_90 : ROATE_DEGREES_0;
    }
}
