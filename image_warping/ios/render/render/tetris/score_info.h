#pragma once

namespace lh_gl {
    class score_info
    {
    public:
        score_info();
        ~score_info();
    public:
        void draw();
        void init();
    public:
        void game_over();
        void set_unity_score(int);
        void add_score(short);
        int get_score();
    private:
        void init_sharde();
        void init_vao();
        void bind();
    private:
        int _score_value = 0;
        int _unity_score_value = 10;
    };
}

