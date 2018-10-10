#pragma once

#include "dropdetection.h"
#include "lh2dcube.h"
#include "draw_tetri.h"
#include "score_info.h"
#include "timer.hpp"

namespace lh_gl {
    struct BottommTeyriUnit {
        float* color = nullptr;
        float top = 0.0f;
        float bottom = 0.0f;
        float left = 0.0f;
        float right = 0.0f;
    };

    class manage_tetri//, protected dropdetection
    {
    public:
        manage_tetri() {};
        ~manage_tetri() {};
    public:
        bool can_draw();
        void add_cube_to_buttom();
        void reset_cube_to_buttom();
        void draw(const Matrix4f &proj, const Matrix4f &view, const Matrix4f &model, const vec3& viewpos);
        void init(const char* dir, vec3 light_postion);
        bool update_floor();
        void down();
        void left();
        void up();
        void right();
        void suspend();
        void rand_cube();
    private:
        void init_vao();
        bool init_sharde(const char* dir);
        void release_gl_datas();
        void add_gl_datas(std::vector<float> subdatas);
        void update_gl_datas();
        void update_current_gl_datas();
        void update_current_cube_counts();
        void update_floor_counts();
        void bind_buffer_datas();
        short update_degrees(short deg);
    private:
        score_info _info;
        dropdetection _tetri;
        lh2dcube _tetri_cube_generate;
        draw_tetri _current_cube;
        draw_tetri _floor;
        short _degrees = 0;
        Timer _timer;
        volatile bool _can_update = true;
        GAME_STATUS _game_status = GAME_GOON;
    };
}

