#include "score_info.h"

namespace lh_gl {
    score_info::score_info()
    {
        _score_value = 0;
    }

    score_info::~score_info()
    {
    }

    void score_info::game_over() {
        ;
    }

    void score_info::set_unity_score(int aline_score) {
        _unity_score_value = aline_score;
    }

    void score_info::add_score(short line_nums) {
        if (0 < line_nums) {
            _score_value += line_nums * _unity_score_value;
        }
    }
    int score_info::get_score() {
        return _score_value;
    }

    void score_info::draw() {
        ;
    }
    void score_info::init() {
        ;
    }
    void score_info::init_sharde() {
        ;
    }
    void score_info::init_vao() {
        ;
    }
    void score_info::bind() {
        ;
    }
}