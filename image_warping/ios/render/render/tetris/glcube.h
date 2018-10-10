#pragma once

#include <vector>
#include "tetri_type.h"

namespace lh_gl {
    class glcube
    {
    public:
        glcube();
        ~glcube();
    public:
        void getline(std::vector<float>&);
        void getcube(std::vector<float>&);
        void get_l(std::vector<float>&);
        void get_other_side_l(std::vector<float>&);
        void get_z(std::vector<float>&);
        void get_other_side_z(std::vector<float>&);
        void get_t(std::vector<float>&);
    private:
        void move_cube(std::vector<float>&, 
            bool right = false, bool up = false,
            float right_adv = 0.0f, float up_dev = 0.0f);
        void get_cube(std::vector<float>&);
        void get_left_cube(std::vector<float>&);
        void get_right_cube(std::vector<float>&);

        void get_down_cube(std::vector<float>&);
        void get_up_cube(std::vector<float>&);

        void get_middle_lr_cube(std::vector<float>&);
        void get_middle_ud_cube(std::vector<float>&);
        void get_middle_lr_ud_cube(std::vector<float>&);
        void get_middle_lr_u_cube(std::vector<float>&);
        void get_middle_lu_cube(std::vector<float>&);
        void get_middle_ru_cube(std::vector<float>&);
        void get_middle_rd_cube(std::vector<float>&);

        void get_middle_ld_cube(std::vector<float>&);

    private:
        int _face_points = 36;
        float _cube[FACE_NUMS][36] = {
            // positions          // noraml
           //back
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            //front
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

            //left
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            //right
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            //down
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            //up
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };

        float _cube_c[FACE_NUMS][36] = {
            //back
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
            1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
            1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
            1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,

            //front
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,

            //left
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,

            //right
            1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
            1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
            1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
            1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
            1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
            1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,

            //down
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
            1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
            1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
            1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,

            //up
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f
        };
    };
}

