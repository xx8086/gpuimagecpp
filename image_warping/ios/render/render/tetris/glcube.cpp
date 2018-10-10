#include "glcube.h"

namespace lh_gl {

    glcube::glcube()
    {
    }

    glcube::~glcube()
    {
    }

    void glcube::move_cube(std::vector<float>& vecs, 
        bool right, bool up, 
        float right_adv, float up_dev) {
        int len = vecs.size();
        if (right) {
            for (int i = 0; i < len; i += 5) {
                vecs[i] += right_adv;
            }
        }
        if (up) {
            for (int i = 1; i < len; i += 5) {
                vecs[i] += up_dev;
            }
        }
    }

    void glcube::get_cube(std::vector<float>& vecs) {
        for (int i = 0; i < FACE_NUMS; i++) {
            vecs.insert(vecs.end(), _cube[i], _cube[i] + _face_points);
        }
    }
    void glcube::get_left_cube(std::vector<float>& vecs) {
        for (int i = 0; i < FACE_NUMS; i++) {
            if (i == FACE_LEFT) {
                continue;
            }
            vecs.insert(vecs.end(), _cube[i], _cube[i] + _face_points);
        }
    }
    void glcube::get_right_cube(std::vector<float>& vecs) {
        for (int i = 0; i < FACE_NUMS; i++) {
            if (i == FACE_RIGHT) {
                continue;
            }
            vecs.insert(vecs.end(), _cube[i], _cube[i] + _face_points);
        }
    }

    void glcube::get_down_cube(std::vector<float>& vecs) {
        for (int i = 0; i < FACE_NUMS; i++) {
            if (i == FACE_DOWN) {
                continue;
            }
            vecs.insert(vecs.end(), _cube[i], _cube[i] + _face_points);
        }
    }
    void glcube::get_up_cube(std::vector<float>& vecs) {
        for (int i = 0; i < FACE_NUMS; i++) {
            if (i == FACE_UP) {
                continue;
            }
            vecs.insert(vecs.end(), _cube[i], _cube[i] + _face_points);
        }
    }

    void glcube::get_middle_lr_cube(std::vector<float>& vecs) {
        for (int i = 0; i < FACE_NUMS; i++) {
            if (i == FACE_RIGHT ||
                i == FACE_LEFT) {
                continue;
            }
            vecs.insert(vecs.end(), _cube[i], _cube[i] + _face_points);
        }
    }
    void glcube::get_middle_ud_cube(std::vector<float>& vecs) {
        for (int i = 0; i < FACE_NUMS; i++) {
            if (i == FACE_DOWN ||
                i == FACE_UP) {
                continue;
            }
            vecs.insert(vecs.end(), _cube[i], _cube[i] + _face_points);
        }
    }
    void glcube::get_middle_lr_ud_cube(std::vector<float>& vecs) {
        for (int i = 0; i < FACE_NUMS; i++) {
            if (i == FACE_DOWN ||
                i == FACE_UP ||
                i == FACE_RIGHT ||
                i == FACE_LEFT) {
                continue;
            }
            vecs.insert(vecs.end(), _cube[i], _cube[i] + _face_points);
        }
    }
    void glcube::get_middle_lr_u_cube(std::vector<float>& vecs) {
        for (int i = 0; i < FACE_NUMS; i++) {
            if (i == FACE_UP ||
                i == FACE_RIGHT ||
                i == FACE_LEFT) {
                continue;
            }
            vecs.insert(vecs.end(), _cube[i], _cube[i] + _face_points);
        }
    }
    void glcube::get_middle_lu_cube(std::vector<float>& vecs) {
        for (int i = 0; i < FACE_NUMS; i++) {
            if (i == FACE_UP ||
                i == FACE_LEFT) {
                continue;
            }
            vecs.insert(vecs.end(), _cube[i], _cube[i] + _face_points);
        }
    }

    void glcube::get_middle_ru_cube(std::vector<float>& vecs) {
        for (int i = 0; i < FACE_NUMS; i++) {
            if (i == FACE_UP ||
                i == FACE_RIGHT) {
                continue;
            }
            vecs.insert(vecs.end(), _cube[i], _cube[i] + _face_points);
        }
    }

    void glcube::get_middle_ld_cube(std::vector<float>& vecs) {
        for (int i = 0; i < FACE_NUMS; i++) {
            if (i == FACE_UP ||
                i == FACE_LEFT) {
                continue;
            }
            vecs.insert(vecs.end(), _cube[i], _cube[i] + _face_points);
        }
    }
    void glcube::get_middle_rd_cube(std::vector<float>& vecs) {
        for (int i = 0; i < FACE_NUMS; i++) {
            if (i == FACE_DOWN ||
                i == FACE_RIGHT) {
                continue;
            }
            vecs.insert(vecs.end(), _cube[i], _cube[i] + _face_points);
        }
    }

/*
            ____________
          /|                /| back
        /  |  up        /  |
      /___|_______/     |
left |    /           |    /rigth  
      |  /   down |  /
      |/__front__ |/

*/

    void glcube::getline(std::vector<float>& vecs) {
        std::vector<float> a;
        std::vector<float> b;
        std::vector<float> c;
        std::vector<float> d;
        //abcd
        get_left_cube(a);
        get_middle_lr_cube(b);
        get_middle_lr_cube(c);
        get_right_cube(d);
        
        move_cube(b, true, false, 1.0);
        move_cube(c, true, false, 2.0);
        move_cube(d, true, false, 3.0);

        vecs.insert(vecs.end(), a.begin(), a.end());
        vecs.insert(vecs.end(), b.begin(), b.end());
        vecs.insert(vecs.end(), c.begin(), c.end());
        vecs.insert(vecs.end(), d.begin(), d.end());
        
        
    }

    void glcube::getcube(std::vector<float>&vecs) {
        for (int i = 0; i < FACE_NUMS; i++) {
            vecs.insert(vecs.end(), _cube_c[i], _cube_c[i] + _face_points);
        }
    }

    void glcube::get_l(std::vector<float>&vecs) {
        std::vector<float> a;
        std::vector<float> b;
        std::vector<float> c;
        std::vector<float> d;
        //    d
        //abc
        get_right_cube(a);
        get_middle_lr_cube(b);
        get_middle_lu_cube(c);
        get_down_cube(d);

        move_cube(b, true, false, 1.0);
        move_cube(c, true, false, 2.0);
        move_cube(d, true, true, 2.0, 1.0);

        vecs.insert(vecs.end(), a.begin(), a.end());
        vecs.insert(vecs.end(), b.begin(), b.end());
        vecs.insert(vecs.end(), c.begin(), c.end());
        vecs.insert(vecs.end(), d.begin(), d.end());
    }
    void glcube::get_other_side_l(std::vector<float>&vecs) {
        std::vector<float> a;
        std::vector<float> b;
        std::vector<float> c;
        std::vector<float> d;
        //d   
        //abc
        get_middle_ru_cube(a);
        get_middle_lr_cube(b);
        get_left_cube(c);
        get_down_cube(d);

        vecs.insert(vecs.end(), a.begin(), a.end());

        move_cube(b, true, false, 1.0);
        vecs.insert(vecs.end(), b.begin(), b.end());
        move_cube(c, true, false, 2.0);
        vecs.insert(vecs.end(), c.begin(), c.end());
        move_cube(d, false, true, 1.0);
        vecs.insert(vecs.end(), d.begin(), d.end());
    }
    void glcube::get_z(std::vector<float>&vecs) {
        std::vector<float> a;
        std::vector<float> b;
        std::vector<float> d;
        std::vector<float> e;
        //ab
        //  de
        get_right_cube(a);
        get_middle_ld_cube(b);
        get_middle_ru_cube(d);
        get_left_cube(e);

        move_cube(a, false, true, 0.0, 1.0);
        move_cube(b, true, true, 1.0, 1.0);
        move_cube(d, true, false, 1.0);
        move_cube(e, true, false, 2.0);
        vecs.insert(vecs.end(), a.begin(), a.end());
        vecs.insert(vecs.end(), b.begin(), b.end());
        vecs.insert(vecs.end(), d.begin(), d.end());
        vecs.insert(vecs.end(), e.begin(), e.end());

        vecs.insert(vecs.end(), b.begin(), b.end());
    }
    void glcube::get_other_side_z(std::vector<float>&vecs) {
        std::vector<float> a;
        std::vector<float> b;
        std::vector<float> d;
        std::vector<float> e;
        //   de
        // ab
        get_right_cube(a);
        get_middle_lu_cube(b);
        get_middle_rd_cube(d);
        get_left_cube(e);

        move_cube(b, true, false, 1.0);
        move_cube(d, true, true, 1.0, 1.0);
        move_cube(e, true, true, 2.0, 1.0);

        vecs.insert(vecs.end(), a.begin(), a.end());
        vecs.insert(vecs.end(), b.begin(), b.end());
        vecs.insert(vecs.end(), d.begin(), d.end());
        vecs.insert(vecs.end(), e.begin(), e.end());
    }
    void glcube::get_t(std::vector<float>&vecs) {
        std::vector<float> a;
        std::vector<float> b;
        std::vector<float> c;
        std::vector<float> d;
        // d   
        //abc
        get_right_cube(a);
        get_middle_lr_u_cube(b);
        get_left_cube(c);
        get_down_cube(d);
        
        move_cube(b, true, false, 1.0);
        move_cube(c, true, false, 2.0);
        move_cube(d, true, true, 1.0, 1.0);

        vecs.insert(vecs.end(), a.begin(), a.end());
        vecs.insert(vecs.end(), b.begin(), b.end());
        vecs.insert(vecs.end(), c.begin(), c.end());
        vecs.insert(vecs.end(), d.begin(), d.end());
    }
}